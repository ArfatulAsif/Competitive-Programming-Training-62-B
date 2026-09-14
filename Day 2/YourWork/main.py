"""Main REPL for the coder bot.

Run:
    python main.py                          # default settings from .env
    python main.py --provider local         # start in local (Ollama) mode
    python main.py --model <name>           # override the active model
    python main.py --root <path>            # override project root
    python main.py --auto                   # start in auto mode (no confirmations)
    python main.py --reset-history          # wipe the history file before starting
"""
from __future__ import annotations

import argparse
import json
import os
import sys
import traceback
from dataclasses import replace
from datetime import datetime
from pathlib import Path
from typing import Any, Callable, Dict, List, Optional

from openai import OpenAI

from agent import CODER_SYSTEM_PROMPT, run_turn
from config import BASE_URLS, Settings
from voice_utils import (
    listen,
    mic_available,
    speak,
    stt_available,
    tts_available,
)


# --------------------------------------------------------------------------- #
# Debug + error helpers
# --------------------------------------------------------------------------- #

#: Set CODER_BOT_DEBUG=1 to print full tracebacks for every caught error.
#: Default off so the REPL stays clean for normal use.
DEBUG: bool = os.getenv("CODER_BOT_DEBUG", "").strip() in {"1", "true", "yes", "on"}


def _debug_exc(label: str, exc: BaseException) -> None:
    """Print a short `[label] error: ...` line and (if DEBUG) the full traceback.

    Centralised so every catch site reports failures consistently instead of
    either swallowing them or letting them kill the REPL silently.
    """
    print(f"[{label}] error: {type(exc).__name__}: {exc}")
    if DEBUG:
        traceback.print_exc()


def _stt_self_check() -> bool:
    """If STT is supposed to be on, prove the mic actually works.

    Returns True iff voice input should stay enabled for this session.
    Prints a clear warning (not an exception) when it isn't usable, and
    tells the user exactly how to fall back to text.
    """
    if not stt_available():
        print("[warning] speech_recognition is not installed; "
              "voice input disabled. Type `voice` after installing "
              "speech_recognition + PyAudio to enable it.")
        return False
    if not mic_available():
        print("[warning] microphone/STT unavailable (permission denied, "
              "no mic, or PortAudio missing); falling back to text input.")
        print("          You can still type `voice` later to retry.")
        return False
    print("[ok] microphone + STT ready. Type `voice` per-turn to speak.")
    return True


def _maybe_speak(state: Dict[str, Any], text: str) -> None:
    """Speak `text` only if TTS output is enabled this session.

    The bot used to read every reply aloud automatically, which made the
    REPL feel chatty. Now `speak()` is gated behind `state['output_voice']`,
    which is initialised from `CODER_TTS` and toggled at runtime with
    `say on` / `say off`. Failures are logged but never crash the REPL.
    """
    if not text or not state.get("output_voice", False):
        return
    try:
        speak(text)
    except Exception as exc:
        _debug_exc("tts", exc)


# --------------------------------------------------------------------------- #
# History persistence
# --------------------------------------------------------------------------- #

def load_history(path: Path) -> List[Dict[str, Any]]:
    if not path.exists():
        return []
    try:
        data = json.loads(path.read_text(encoding="utf-8"))
        if isinstance(data, list):
            return data
    except Exception as e:
        print(f"[warn] could not parse history ({path}): {e}")
    return []


def save_history(path: Path, messages: List[Dict[str, Any]]) -> None:
    try:
        # Strip non-serialisable bits (we don't expect any, but be safe).
        clean = []
        for m in messages:
            m2 = {k: v for k, v in m.items()
                  if k in {"role", "content", "name", "tool_calls", "tool_call_id"}}
            clean.append(m2)
        path.write_text(
            json.dumps(clean, indent=2, ensure_ascii=False),
            encoding="utf-8",
        )
    except OSError as e:
        print(f"[warn] could not save history ({path}): {e}")


# --------------------------------------------------------------------------- #
# Client construction
# --------------------------------------------------------------------------- #

def build_client(settings: Settings) -> OpenAI:
    """Build an OpenAI-compatible client for the active provider.

    For "local" we use a dummy key because the OpenAI SDK refuses empty
    strings, but Ollama ignores whatever you pass.
    """
    return OpenAI(api_key=settings.api_key, base_url=settings.base_url)


# --------------------------------------------------------------------------- #
# Banner
# --------------------------------------------------------------------------- #

def print_banner(settings: Settings) -> None:
    provider_tag = {
        "cloud": "OpenRouter",
        "local": "Ollama (local)",
    }.get(settings.provider, settings.provider)
    print("─" * 60)
    print(f" coder bot  ({provider_tag}, sandboxed)")
    print(f"  provider  : {settings.provider}  ({settings.base_url})")
    print(f"  model     : {settings.model}")
    if settings.provider == "cloud":
        print(f"  fallback  : local={settings.local_model!r} "
              f"(try `use local` if the API is down)")
    else:
        print(f"  fallback  : cloud={settings.cloud_model!r} "
              f"(try `use cloud` if Ollama is slow)")
    print(f"  root      : {settings.project_root}")
    print(f"  mode      : {settings.mode}")
    print(f"  history   : {settings.history_file}")
    # NOTE: stt/tts here reflect library availability, not runtime health.
    # The startup self-check in main() actually pokes the microphone.
    print(f"  stt/tts   : {stt_available()}/{tts_available()}")
    print("  type 'help' for commands, 'exit' to quit, 'voice' for STT, 'say on' for TTS")
    print("─" * 60)


# --------------------------------------------------------------------------- #
# CLI arg parsing
# --------------------------------------------------------------------------- #

def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(
        description="Local agentic coding bot (OpenRouter or Ollama)."
    )
    p.add_argument("--provider",
                   choices=("cloud", "local"),
                   help="Override PROVIDER (cloud=OpenRouter, local=Ollama).")
    p.add_argument("--model",
                   help="Override the active model for the chosen provider.")
    p.add_argument("--root", help="Override project root (sandbox).")
    p.add_argument("--auto", action="store_true",
                   help="Start in auto mode (no confirmations).")
    p.add_argument("--reset-history", action="store_true",
                   help="Delete the history file before starting.")
    return p.parse_args()


# --------------------------------------------------------------------------- #
# Slash-commands
# --------------------------------------------------------------------------- #

HELP_TEXT = """\
Commands:
  voice                toggle STT (voice input) for this turn
  say                  show current TTS (voice output) state
  say on | say off     turn automatic speech-of-replies on/off
  say <text>           speak the given text right now (one-off)
  mode                 show current ask/auto mode
  auto mode            switch to auto (no confirmations)
  ask mode             switch to ask (confirm every write/delete/command)
  provider             show current provider + model
  use cloud            switch to OpenRouter (rebuilds client)
  use local            switch to local Ollama (rebuilds client)
  use model <id>       override the active model for the current provider
  root <path>          change the project sandbox root
  history [N]          show last N turns (default 10)
  clear                reset conversation history
  help                 show this help
  exit | quit          leave the bot
"""


def _switch_provider(state: Dict[str, Any],
                     new_provider: str,
                     new_model: Optional[str] = None) -> bool:
    """Rebuild the client for `new_provider`. Returns False on failure."""
    if new_provider not in BASE_URLS:
        print(f"[error] unknown provider {new_provider!r}")
        return False

    # Build the new Settings. Start from the current one.
    s: Settings = state["settings"]

    # Pick the right model field.
    chosen_model = new_model or (
        s.cloud_model if new_provider == "cloud" else s.local_model
    )

    # Build a fresh Settings so validation (incl. API key) re-runs.
    overrides: Dict[str, Any] = {
        "provider": new_provider,
        "model": chosen_model,
        "base_url": BASE_URLS[new_provider],
        "api_key": _key_for(new_provider),
    }
    try:
        new_settings = replace(s, **overrides)
    except Exception as e:
        print(f"[error] could not switch: {e}")
        return False

    # Rebuild the client.
    state["client"] = OpenAI(api_key=new_settings.api_key,
                             base_url=new_settings.base_url)
    state["settings"] = new_settings
    print(f"→ switched to provider={new_settings.provider} "
          f"model={new_settings.model!r}")
    print_banner(new_settings)
    return True


def _key_for(provider: str) -> str:
    """Look up the right API key (real or dummy) for a provider."""
    if provider == "cloud":
        key = os.getenv("OPENROUTER_API_KEY", "")
        if not key:
            # Should already have been caught at startup; re-raise via Settings.
            raise RuntimeError(
                "OPENROUTER_API_KEY is not set; cannot switch to cloud."
            )
        return key
    # Local: dummy.
    return os.getenv("OLLAMA_API_KEY", "ollama") or "ollama"


def handle_command(line: str, *, state: Dict[str, Any]) -> bool:
    """Return True if the line was a slash-command (and was handled)."""
    cmd = line.strip().lower()
    if cmd in {"exit", "quit", ":q"}:
        state["should_exit"] = True
        return True

    if cmd in {"help", "/help", "?"}:
        print(HELP_TEXT)
        return True

    if cmd == "mode":
        print(
            f"mode: {state['mode']}  "
            f"({'no confirmations' if state['mode'] == 'auto' else 'confirm every write/delete/command'})"
        )
        return True

    if cmd in {"auto mode", "auto"}:
        state["mode"] = "auto"
        print("→ auto mode (no confirmations). Dangerous ops are still blocked.")
        return True

    if cmd in {"ask mode", "ask"}:
        state["mode"] = "ask"
        print("→ ask mode (confirm each write/delete/command).")
        return True

    if cmd == "provider":
        s = state["settings"]
        print(f"provider : {s.provider}  ({s.base_url})")
        print(f"model    : {s.model}")
        print(f"cloud    : {s.cloud_model}")
        print(f"local    : {s.local_model}")
        return True

    if cmd == "use cloud":
        return _switch_provider(state, "cloud")
    if cmd == "use local":
        return _switch_provider(state, "local")

    # `use model <id>` overrides the active model.
    if cmd.startswith("use model "):
        new_model = line.strip()[len("use model "):].strip()
        s = state["settings"]
        return _switch_provider(state, s.provider, new_model=new_model)

    if cmd.startswith("root "):
        new_root = cmd[5:].strip().strip('"').strip("'")
        new_path = Path(new_root).expanduser().resolve()
        if not new_path.exists():
            print(f"[error] {new_path} does not exist")
            return True
        state["project_root"] = new_path
        state["history_file"] = new_path / ".coder_history.json"
        state["settings"] = replace(state["settings"],
                                    project_root=new_path,
                                    history_file=state["history_file"])
        state["messages"] = []  # new sandbox = fresh context
        print(f"→ project root is now {new_path}")
        print("→ history reset for the new sandbox")
        return True

    if cmd.startswith("history"):
        parts = cmd.split()
        n = 10
        if len(parts) >= 2 and parts[1].isdigit():
            n = int(parts[1])
        msgs = state["messages"]
        shown = [m for m in msgs
                 if m.get("role") in {"user", "assistant"} and m.get("content")][-n:]
        if not shown:
            print("(no history)")
        else:
            print(f"─── last {len(shown)} turns ───")
            for m in shown:
                tag = "you" if m["role"] == "user" else "bot"
                content = m["content"]
                if len(content) > 400:
                    content = content[:400] + "...(truncated)"
                print(f"[{tag}] {content}")
        return True

    if cmd == "clear":
        state["messages"] = []
        print("→ history cleared (current session only; file is saved on exit)")
        return True

    # Voice toggle — explicit user opt-in. STT stays OFF unless the user
    # runs `voice` (and the startup self-check passed).
    if cmd in {"voice", "/voice"}:
        if not state.get("stt_usable", False):
            print("[voice] STT not available this session "
                  "(see startup warning). Voice toggle ignored.")
            return True
        state["voice"] = not state["voice"]
        print(f"→ voice input: {'on' if state['voice'] else 'off'}")
        return True

    # TTS output toggle — controls whether the bot SPEAKS replies aloud.
    #   say         → show current state
    #   say on|off  → flip the auto-speak behaviour
    #   say <text>  → speak the text right now (works even when off)
    if cmd == "say" or cmd.startswith("say "):
        parts = line.strip().split(maxsplit=1)
        arg = parts[1].strip().lower() if len(parts) > 1 else ""
        if arg in {"on", "off"}:
            state["output_voice"] = (arg == "on")
            print(f"→ voice output (TTS): {arg}")
            return True
        if arg == "":
            on = state.get("output_voice", False)
            print(f"voice output (TTS): {'on' if on else 'off'}  "
                  f"(use `say on` / `say off` to toggle)")
            return True
        # `say <text>` — one-off utterance, independent of the toggle.
        try:
            speak(arg)
            print(f"[tts] said: {arg}")
        except Exception as exc:
            _debug_exc("tts", exc)
        return True

    return False


# --------------------------------------------------------------------------- #
# Main loop
# --------------------------------------------------------------------------- #

def main() -> int:
    args = parse_args()
    settings = Settings.load()

    # --- CLI overrides -----------------------------------------------------
    # We rebuild a single Settings object honouring --provider, --model,
    # --root, --auto before constructing the client.
    overrides: Dict[str, Any] = {}

    if args.provider:
        overrides["provider"] = args.provider
        overrides["base_url"] = BASE_URLS[args.provider]
        overrides["api_key"] = _key_for(args.provider)
        # --model applies to the chosen provider if both were given.
        if args.model:
            overrides["model"] = args.model
    elif args.model:
        # --model without --provider just tweaks the active provider's model.
        overrides["model"] = args.model

    if args.root:
        overrides["project_root"] = Path(args.root).expanduser().resolve()
    if args.auto:
        overrides["mode"] = "auto"

    if overrides:
        settings = replace(settings, **overrides)
        if "project_root" in overrides:
            settings = replace(
                settings,
                history_file=settings.project_root / ".coder_history.json",
            )

    if args.reset_history and settings.history_file.exists():
        settings.history_file.unlink()
        print(f"[reset] removed {settings.history_file}")

    # --- Client + state ----------------------------------------------------
    client = build_client(settings)

    state: Dict[str, Any] = {
        "mode": settings.mode,
        "project_root": settings.project_root,
        "history_file": settings.history_file,
        "messages": load_history(settings.history_file),
        "should_exit": False,
        # STT (input) — OFF by default; user types `voice` to enable.
        "voice": False,
        # TTS (output) — seeded from CODER_TTS, toggle at runtime with `say on/off`.
        "output_voice": bool(getattr(settings, "output_voice_enabled", False)),
        # `stt_usable` is set by the startup self-check below. When False,
        # the `voice` command refuses to enable voice input at all.
        "stt_usable": False,
        "settings": settings,
        "client": client,
    }

    # Seed system prompt if history is empty.
    if not state["messages"]:
        state["messages"].append({"role": "system", "content": CODER_SYSTEM_PROMPT})

    print_banner(settings)

    # --- Startup self-check --------------------------------------------------
    # If the user enabled voice in .env (CODER_VOICE=1), prove the mic works
    # RIGHT NOW — don't wait for the first /voice to fail deep in the loop.
    if getattr(settings, "voice_enabled", False):
        state["stt_usable"] = _stt_self_check()
    else:
        # Default-off path: just note that voice is opt-in, and run the
        # check silently so the `voice` command has accurate info to use.
        state["stt_usable"] = (
            stt_available() and mic_available()
        )
        if state["stt_usable"]:
            print("[info] voice input available — type `voice` to enable per turn.")

    # Greeting shortcuts (kept from the original code).
    print()
    print("Quick greetings:")
    for g in ("hi", "hello", "hey", "good morning", "good afternoon", "good evening"):
        print(f"  {g}! → friendly reply + project listing")
    print()

    while not state["should_exit"]:
        try:
            line = input(
                f"[{state['project_root'].name}/{state['mode']}/"
                f"{state['settings'].provider}:{state['settings'].model}] > "
            ).strip()
        except EOFError as exc:
            # EOF on stdin — usually Ctrl+D, or stdin is closed (this is
            # exactly the "silent exit after banner" symptom). Print a
            # clear message instead of falling through to `bye 👋`.
            _debug_exc("input", exc)
            print("[input] end of input (EOF). Type Ctrl+D again or `exit` to quit.")
            break
        except KeyboardInterrupt as exc:
            # Ctrl+C — treat as "abort current line", NOT as quit, so we
            # can keep using the bot. Print a newline and continue.
            _debug_exc("input", exc)
            print("\n[input] interrupted (Ctrl+C). Ready for next prompt.")
            continue
        except Exception as exc:
            # Any other failure (UnicodeError, OSError, ...) used to kill
            # the REPL silently. Now we log it and keep going.
            _debug_exc("input", exc)
            print("[input error] could not read from stdin — falling back.")
            continue

        if not line:
            continue

        # Greeting shortcuts.
        lower = line.lower().strip("!., ")
        if lower in {"hi", "hello", "hey",
                     "good morning", "good afternoon", "good evening"}:
            hour = datetime.now().hour
            tod = ("morning" if 5 <= hour < 12
                   else "afternoon" if 12 <= hour < 18
                   else "evening")
            try:
                reply = (
                    f"Good {tod}! I'm your coder bot. "
                    f"Provider: {state['settings'].provider} "
                    f"({state['settings'].model}). "
                    f"Mode: {state['mode']}. What would you like to build?"
                )
                print(reply)
                _maybe_speak(state, reply)
            except Exception as exc:
                _debug_exc("greeting", exc)
            continue

        # Voice input is only ever active when (a) the user explicitly
        # typed `voice` to toggle it on AND (b) the startup self-check
        # confirmed the mic is usable. Otherwise stay on text.
        if state["voice"] and not line.startswith("/"):
            try:
                spoken = listen()
            except Exception as exc:
                # listen() already swallows everything internally; this
                # branch is a belt-and-braces guard.
                _debug_exc("voice", exc)
                spoken = None
            if spoken:
                line = spoken
                print(f"(voice) > {line}")
            else:
                print("(voice) nothing captured, please type instead.")
                continue

        # Slash / builtin commands.
        if handle_command(line, state=state):
            continue

        # Normal chat turn — any failure here is reported, not silent.
        state["messages"].append({"role": "user", "content": line})

        def on_summary(round_idx: int, counts: Dict[str, int]) -> None:
            parts = []
            for name, n in counts.items():
                plural = "" if n == 1 else "s"
                parts.append(f"{n} {name}{plural}")
            print(f"─── round {round_idx}: " + ", ".join(parts) + " ───")

        try:
            # Pass a NO-OP speak into agent.py. agent.py used to call
            # speak("Cancelled.") / speak("API call failed.") directly,
            # which bypassed the output_voice toggle. Now it stays silent
            # unless the caller (us) decides otherwise below.
            turn = run_turn(
                client=state["client"],
                settings=state["settings"],
                messages=state["messages"],
                get_mode=lambda: state["mode"],
                speak=None,
                on_round_summary=on_summary,
            )
        except Exception as exc:
            _debug_exc("turn", exc)
            print("[turn error] the model call failed; ready for next prompt.")
            continue

        # Speak the final answer only when output_voice is enabled.
        if turn.final_text:
            _maybe_speak(state, turn.final_text)

        # Persist after every turn so crashes don't lose work.
        save_history(state["history_file"], state["messages"])

    print("bye 👋")
    save_history(state["history_file"], state["messages"])
    return 0


if __name__ == "__main__":
    sys.exit(main())