---
name: No automation scripts — print commands instead
description: User prefers to see and type commands manually rather than have scripts automate them
type: feedback
---

Do not create shell scripts to automate commands. When the user asks how to run checks, lint, compile, etc., print the command so they can run it themselves and learn what it does.

**Why:** User wants to remember commands and understand what is being run — automation hides that.

**How to apply:** Always print the raw command (gcc, cppcheck, gdb, etc.) instead of wrapping it in a script.
