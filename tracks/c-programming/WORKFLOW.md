# C Programming Track — Workflow

**Pace-setter:** Mastering STM32 (Noviello) — chapters you're reading at work
**C refreshers:** Modern C (Gustedt) — pulled in when an STM32 chapter needs those fundamentals
**Embedded patterns:** Making Embedded Systems (White) — sidebars in each session

All three PDFs are in `knowledge/`.

---

## Where You Are Now

**Current position:** mc02 → mc03 → mc04 → mc05 → ms06

Do mc02–mc05 first (C refreshers), then ms06 (GPIO HAL). These four sessions give you
the C you need to read and write HAL code: control flow, bitwise ops, fixed-width types,
and structs/typedef/enum.

```
mc02  Modern C Ch3  — Control (if/else, switch, loops)
mc03  Modern C Ch4  — Computations (bitwise, shifts, masks, register ops)
mc04  Modern C Ch5  — Values and Data (stdint.h, volatile, const, float)
mc05  Modern C Ch6  — Derived Types (structs, typedef, enum, arrays, pointers)
─────────────────────────────────────────────────────────────────
ms06  Mastering STM32 Ch6 — GPIO (HAL_GPIO_Init, modes, Discovery LEDs)
```

See `knowledge/index.md` for the full session map.

---

## Workflow: C Refresher Session (mcXX)

### Step 1 — Read the lesson
```
cat material/mcXX-<name>/notes.md
```
Notes cite which Modern C pages the concept comes from. If you want the full treatment,
open `knowledge/modernC.pdf` to that chapter.

### Step 2 — Read the problems
```
cat material/mcXX-<name>/problems.md
```
Each problem has a **Thought process** scaffold. Read it before writing any code.

### Step 3 — Create your project directory
```
mkdir -p projects/mcXX-<name>
cd projects/mcXX-<name>
```

### Step 4 — Write each problem in Vim
```
vim <problem_name>.c
```
Write from scratch. Do not copy from notes — type the code and understand each line.

### Step 5 — Compile
```
gcc -Wall -Wextra -g -std=c2x -o <name> <name>.c
```
Always use all four flags. `-g` enables GDB. `-Wall -Wextra` catches real bugs.
Fix every warning before moving on.

### Step 6 — Run and verify
```
./<name>
```
Compare output to what you expected. If it's wrong, add a `printf` to see intermediate
values, or go to GDB.

### Step 7 — Debug with GDB (if needed)
```
gdb ./<name>
(gdb) break main
(gdb) run
(gdb) next          # step one line
(gdb) print var     # inspect a variable
(gdb) info locals   # dump all locals
(gdb) quit
```
See `progressions/gdb.md` for the full command list introduced so far.

### Step 8 — Mark done
Edit `knowledge/index.md`, change the session status from `ready` to `done`.

---

## Workflow: STM32 HAL Session (msXX)

### Step 1 — Read the lesson
```
cat material/msXX-<name>/notes.md
```
Notes cite which Mastering STM32 pages and which HAL functions are covered.

### Step 2 — Open the book alongside
Open `knowledge/Mastering STM32.pdf` to the chapter. The notes are a guide, not a
replacement — read the book sections for full context.

### Step 3 — Set up a CubeMX project (if required)
Problems specify whether to use CubeMX or write HAL calls directly. Follow the problem
statement — do not add features not asked for.

### Step 4 — Write the firmware in STM32CubeIDE
Code goes in `projects/msXX-<name>/`. Flash to STM32F407G-DISC1.

### Step 5 — Verify on hardware
Each problem specifies what the expected behavior is (LED blink, UART output, ADC reading).
Verify before marking done.

### Step 6 — Mark done
Edit `knowledge/index.md`, change the session status to `done`.

---

## Compile Reference

```bash
# Standard compile (all C refresher sessions):
gcc -Wall -Wextra -g -std=c2x -o <name> <name>.c

# Check assembly (volatile demo, optimization questions):
gcc -Wall -Wextra -O2 -std=c2x -S <name>.c   # produces <name>.s

# Run under GDB:
gdb ./<name>
```

---

## Vim Quick Reference (commands introduced so far)

From `progressions/vim.md` — full list with context examples in that file.

| Command | What it does |
|---------|-------------|
| `o` / `O` | New line below / above, enter insert mode |
| `A` | Append at end of current line |
| `dw` | Delete word under cursor |
| `0` / `$` | Jump to line start / end |
| `gg` / `G` | Jump to file top / bottom |
| `%` | Jump to matching `{}` / `()` / `[]` |
| `ci"` | Change text inside quotes |
| `ci(` | Change text inside parentheses |
| `:set number` | Show line numbers |

---

## GDB Quick Reference (commands introduced so far)

From `progressions/gdb.md` — full list with workflow notes in that file.

| Command | What it does |
|---------|-------------|
| `gdb ./program` | Launch GDB |
| `break main` | Breakpoint at start of main |
| `run` | Start the program |
| `next` | Step over one line |
| `step` | Step into a function call |
| `print var` | Print one variable |
| `info locals` | Print all locals in current scope |
| `list` | Show source around current line |
| `quit` | Exit GDB |

---

## Progress Tracking

After each session:
1. `vim knowledge/index.md` — change status to `done`
2. Confirm the next session's prereqs are met before starting it
3. If you got stuck on something, note it at the bottom of `projects/mcXX-<name>/` as a `notes.txt`

The session map in `knowledge/index.md` shows which C refreshers are needed before each
STM32 HAL session. Never skip a refresher if you're unsure of the C — the HAL code will
not make sense without it.
