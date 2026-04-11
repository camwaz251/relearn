# GDB Progression

Tracks every GDB command introduced across C sessions — one layer at a time.
Each session adds 2–4 commands that are immediately useful for debugging that session's code.

Compile with `gcc -Wall -Wextra -g` to include debug symbols. Run with `gdb ./program`.

---

## Baseline (no prior GDB knowledge assumed)

*Nothing assumed — GDB is introduced from scratch starting Ch. 1.*

---

<!-- New sessions append below this line -->

## Ch. 1 — A Tutorial Introduction
*New this session:*

| Command | What it does | Example |
|---------|-------------|---------|
| `gdb ./program` | Launch GDB with your binary | `gdb ./adc_table` |
| `run` (or `r`) | Start (or restart) the program | Type `run` after setting breakpoints |
| `break main` (or `b main`) | Set a breakpoint at the start of main | Stop execution so you can step through |
| `next` (or `n`) | Execute current line, step *over* function calls | Walk through a `for` loop one iteration at a time |
| `print var` (or `p var`) | Print the current value of a variable | `p i` to check loop counter, `p voltage` to check a float |
| `quit` (or `q`) | Exit GDB | When you're done debugging |

*Workflow for this session:*
1. Compile: `gcc -Wall -Wextra -g -o program program.c`
2. Launch: `gdb ./program`
3. `break main` → `run` → `next` through your code, `print` variables to inspect state
4. `quit` when done

## Session 1 — Getting Started (Modern C Ch 1–2)
*New this session:*

| Command | What it does | Example |
|---------|-------------|---------|
| `step` (or `s`) | Step *into* a function call (vs `next` which steps over) | Step into a helper function to see its internals |
| `list` (or `l`) | Show source code around current execution point | See context without leaving GDB |
| `info locals` | Print all local variables in current scope | Check all variables at once instead of printing one by one |

*Workflow addition:*
- Use `list` to orient yourself when stepping through code
- Use `info locals` to dump all local variables at a breakpoint — faster than printing each one
- Use `step` when you want to go *inside* a function call (vs `next` which runs it and moves past)

## Session mc02 — Control (Modern C Ch 3)
*New this session:*

| Command | What it does | Example |
|---------|-------------|---------|
| `break <file>:<line>` | Set breakpoint at specific file and line | `break state_machine.c:42` — stop at a `case` handler |
| `watch <var>` | Break whenever a variable's value changes | `watch current_state` — catch unexpected state transitions |
| `display <var>` | Auto-print variable after every step | `display tick` — see tick count without typing `p tick` each time |

## Session mc03 — Computations (Modern C Ch 4)
*New this session:*

| Command | What it does | Example |
|---------|-------------|---------|
| `print/x var` | Print variable in hex | `p/x GPIO_ODR` — see register value in hex |
| `print/t var` | Print variable in binary | `p/t mask` — see which bits are set |

## Session mc04 — Values and Data (Modern C Ch 5)
*New this session:*

| Command | What it does | Example |
|---------|-------------|---------|
| `ptype var` | Show the type of a variable | `ptype adc_raw` — verify it's `uint16_t` not `int` |
| `x/4xw &var` | Examine 4 words of memory at address | `x/4xw &adc_buf` — see raw memory layout |

## Session mc05 — Derived Types (Modern C Ch 6)
*New this session:*

| Command | What it does | Example |
|---------|-------------|---------|
| `print cfg` | Print entire struct | `p led_cfg` — see all fields at once |
| `print cfg.pin` | Print a single struct member | `p cfg.pin` — check one field |
| `print *ptr` | Dereference and print pointed-to struct | `p *cfg_ptr` — when function takes pointer |
