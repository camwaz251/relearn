# C Programming Track — Claude Instructions

The repo-root `CLAUDE.md` loads automatically alongside this file — it holds the
general project rules. Also update `../../progress.md` after every session.

## Sources

### Primary — Pace-Setter
**Mastering STM32** (Noviello, 2022, 2nd ed) — `knowledge/Mastering STM32.pdf`
28 chapters across 3 parts. HAL peripheral sessions (msXX) follow this book chapter-by-chapter.
User is reading this at work — session pace is set by their work progress.

### C Refreshers (ad hoc, pulled in as prerequisites)
- **Modern C** (Gustedt, 2025, C23) — `knowledge/modernC.pdf`
  Role: C language fundamentals. mcXX sessions are drawn from this book. Each msXX session lists which mcXX sessions are prerequisites.
- **Making Embedded Systems** (White, 2024, 2nd ed) — `knowledge/Making Embedded Systems.pdf`
  Role: embedded design patterns, system thinking. Referenced as sidebars in mcXX sessions.

### Reference
- **K&R** "The C Programming Language" (1988, C89) — `knowledge/The_C_Programming_Language.pdf`
  Role: exercises, classic idioms, historical reference. Not the lesson source.
- **The Definitive Guide to ARM Cortex-M3/M4** (Yiu, 2014) — `knowledge/TheDefinitiveGuideToARMCortexM3AndM4.pdf`
  Role: ARM architecture reference.
- **MISRA C** — embedded C coding standard for safety-critical systems (automotive, medical, aerospace). MES references it. Key rules relevant to this track: always initialize variables, use `stdint.h` types (`uint8_t` etc.), cast explicitly, prototype every function before use.

**Session naming:** mcXX = Modern C sessions (mc = source book prefix). msXX = Mastering STM32 sessions (ms = source book prefix). Each prefix maps directly to its source book.

## Background
User has a CE degree. C and C++ are rusty — relearning C first, then building toward embedded.
User knows basic Vim and is actively sharpening it. Treat Vim as a parallel skill built alongside C.
User is also learning GDB alongside C. Treat GDB as a parallel skill like Vim — introduce commands incrementally each session.
STM32F407G-DISC1 board is on a separate offline machine (not this one). Blink LED flashed 2026-03-30. This machine is online — used for C refresher sessions and notes. msXX sessions (on-hardware) happen on the offline machine.

## Embedded Framing
Every C concept should be tied to circuits, firmware, signals, or hardware where possible. This is the core framing for this track — make C feel like an embedded tool, not an abstract language.

---

## Directory Structure

```
knowledge/          — source PDFs + index.md (chapter status tracker)
material/           — lesson content per session (notes.md, problems.md)
projects/           — one project dir per session (user codes here in Vim)
progressions/       — skill progression tracking (c.md, vim.md, gdb.md)
```

---

## Learning Phases

### Phase 1: C Fundamentals (Modern C Levels 0–1, sessions 1–8)
*Get the language back under your fingers.*

| Session | Modern C | Topics | Embedded Sidebar |
|---------|----------|--------|-----------------|
| 1 | Ch 1–2 | Getting started, program structure | MES Ch1: What embedded systems are |
| 2 | Ch 3 | Control (if/else, loops, switch) | MES Ch2 intro: System architecture thinking |
| 3 | Ch 4 | Computations (operators, arithmetic, eval order) | MES Ch4 intro: Binary math, bitwise ops for registers |
| 4 | Ch 5 | Values and data (types, binary repr, stdint.h) | MES Ch4: Register handling, hex math |
| 5 | Ch 6 | Derived types (arrays, structs, pointers, typedef) | MES Ch2: Encapsulation, module design |
| 6 | Ch 7 | Functions (main, recursion) | MES Ch2: Driver interfaces (open/close/read/write) |
| 7 | Ch 8 | C library (stdio, string, math, assertions) | MES Ch3 intro: Datasheets, schematics |
| 8 | — | **Phase 1 project:** Simulated sensor data logger | — |

### Phase 2: Deeper C + Embedded Design (Modern C Level 2, sessions 9–16)
*Pointers, memory model, organization — the core of embedded C.*

| Session | Modern C | Topics | Embedded Source |
|---------|----------|--------|----------------|
| 9 | Ch 9–10 | Style, organization, headers, linking | MES Ch2: Layering, adapter pattern |
| 10 | Ch 11 | Pointer ops, pointers+arrays, function pointers | MES Ch4: Memory-mapped I/O |
| 11 | Ch 12 | Unions, alignment, void*, casts | Yiu Ch4: ARM memory map intro |
| 12 | Ch 13 | malloc, stack vs heap, lifetime, static | MES Ch11: Managing RAM, removing malloc |
| 13 | Ch 14 | Text processing, binary streams | MES Ch7: Serial comms (UART, SPI, I2C) |
| 14 | Ch 15 | Error handling, assertions, cleanup | MES Ch9: Debugging, hard faults |
| 15 | — | **Phase 2 project:** Ring buffer + simulated UART parser | MES Ch7: Circular buffers |
| 16 | — | **Phase 2 project continued:** Error handling, GDB testing | MES Ch3: Testing methodology |

### Phase 3: Advanced C + ARM Architecture (Modern C Level 3, sessions 17–24)
*Performance, concurrency, and real hardware thinking.*

| Session | Modern C | Topics | Embedded Source |
|---------|----------|--------|----------------|
| 17 | Ch 16 | inline, restrict, measurement | MES Ch11: Code space, optimization |
| 18 | Ch 17 | Function-like macros, varargs, X-macros | MES Ch11: Macros vs functions tradeoffs |
| 19 | Ch 18 | _Generic, type inference | Yiu Ch1–2: ARM Cortex-M architecture overview |
| 20 | Ch 19 | setjmp/longjmp, signal handlers | MES Ch5: Interrupts, ISRs, vector tables |
| 21 | Ch 20 | Threads, mutexes, condition variables | MES Ch6: Scheduling, state machines, RTOS basics |
| 22 | Ch 21 | _Atomic, memory consistency | MES Ch6: Race conditions, critical sections |
| 23 | — | **Phase 3 project:** State machine firmware simulator | MES Ch6: State machine patterns |
| 24 | — | **Capstone:** QEMU Cortex-M blinky | Yiu + MES combined |

### Phase 4: On Hardware (when STM32 board is connected)
*Not scheduled — starts when user has board access on local machine.*
- Yiu becomes primary alongside MES
- Startup code, linker scripts, NVIC, SysTick, GPIO from registers
- Real peripheral drivers: UART, SPI, I2C, timers, DMA

---

## Workflow Per Session

1. User says which session/chapter.
2. **Enter plan mode first.** Read the relevant Modern C chapter(s) from `knowledge/modernC.pdf`, plus the embedded sidebar source. Present a plan: concepts, notes structure, problems, Vim/GDB commands. User confirms or adjusts before writing anything.
3. Write `material/mcXX-<name>/notes.md` — lessons with code examples, embedded framing, and detailed explanations. Primary content from Modern C. K&R exercises/idioms referenced where relevant. Embedded sidebar from MES/Yiu as noted in the phase table.
4. Write `material/mcXX-<name>/problems.md` — practice problems with thought process scaffolding.
5. Append new Vim commands to `progressions/vim.md`.
6. Append new GDB commands to `progressions/gdb.md`.
7. Append new C concepts to `progressions/c.md`.
8. User codes solutions in `projects/mcXX-<name>/` using Vim.
9. User compiles with `gcc -Wall -Wextra -g` (always include `-g` for debug symbols). Explain any warnings.
10. Help as needed — reference your notes and their code.

---

## Notes Format (`material/mcXX-<name>/notes.md`)

These are **actual lessons**, not just reference cards. For each concept:
- Explain what it does with a **real code example** the user can read and type
- Show the embedded/firmware angle (from MES/Yiu sidebar for that session)
- Call out gotchas, especially things that differ from C++
- Note Modern C (C23) features that didn't exist in K&R/C89 where relevant
- Code examples should be complete enough to compile or clearly marked as snippets

Keep it dense but not terse — the user hasn't coded in a while and needs enough detail to re-learn, then enough problems to solidify.

---

## Problems Format (`material/mcXX-<name>/problems.md`)

- 4–6 problems per session.
- Mix: Modern C exercises, K&R classic exercises where relevant, embedded-contextualized problems.
- No worked solutions in the file. User asks if stuck.

Each problem has two sections — thought process first, then the problem:

```
### Problem N
**Context:** <one sentence on where this appears in embedded>

**Thought process:**
1. <What am I actually being asked to produce?>
2. <What do I know / what are the inputs and constraints?>
3. <What C mechanism or pattern fits here? Why?>
4. <Edge cases or gotchas to think about before writing a line>

<problem statement>
```

The thought process is a scaffold, not a solution. It should teach the user how to approach
C problems systematically — especially the habit of thinking before typing.

---

## Projects

- One project dir per session: `projects/mcXX-<name>/`
- Projects should feel like real embedded tools: data loggers, register maps, protocol parsers, state machines, etc.
- Each project builds on or connects to the previous one where possible.
- Phase project sessions (8, 15–16, 23–24) are larger integration projects.

---

## Progressions (`progressions/`)

Three files tracking incremental skill buildup:

### `vim.md`
- 3–5 new commands per session, immediately useful for that session's code
- Never re-introduce already-covered commands
- Read before each session to see what's been taught

### `gdb.md`
- 2–4 new commands per session, useful for debugging that session's code
- Never re-introduce already-covered commands
- Read before each session to see what's been taught

### `c.md`
- Tracks C concepts introduced per session
- Quick reference so user knows what tools they have so far

Format for vim.md and gdb.md (appended each session):

```
## Session X — <Topic>
*New this session:*

| Command | What it does | Example |
|---------|-------------|---------|
| `cmd`   | Description | Context example |
```

---

## Rules
- Read `memory/` directory files at session start for behavioral preferences.
- Do NOT skip ahead. No advanced topics before prior concept is demonstrated.
- Always compile with `gcc -Wall -Wextra -g`.
- Use Vim for editing. Don't suggest other editors.
- Update `../../progress.md` after each session.
- Update `knowledge/index.md` — mark the session done.
- Append Vim commands to `progressions/vim.md` every session — no exceptions.
- Append GDB commands to `progressions/gdb.md` every session — no exceptions.
- Append C concepts to `progressions/c.md` every session — no exceptions.
- Existing K&R-based material in `material/ch01-tutorial-intro/` is superseded but kept as reference.
- **Never edit the user's code files.** Point out issues and ask leading questions — let them fix it.
- **Never create shell scripts.** Print the command so the user sees and types it — this is part of the learning.
- **Socratic debugging.** When the user hits a bug, ask what they know, what the error says, what they'd check next. Don't give the answer first.
- **Always cite the source.** When introducing a concept, point to the relevant chapter/section (e.g. "Modern C §5.2", "MES Ch4"). Make the books feel useful, not decorative.
- **Stay in the current chapter.** Teach professional style, but hold off techniques (pointer parameters, stdint types, function prototypes, etc.) until their scheduled session. Introducing them early causes the user to waste time on unfamiliar mechanics instead of focusing on the current concept. When in doubt, check the phase table and only use what's been covered.
