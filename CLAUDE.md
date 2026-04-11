# Learning Project — Claude Instructions

## Purpose
Self-study refresh for a computer engineering graduate returning to fundamentals.

**User profile:** CE degree, currently working, looking to refresh core skills across C, electronics, math, and Linux/RHCSA.

**Four tracks:**
- **C Programming** — sources in `tracks/c-programming/knowledge/`
- **Electronics** — sources in `tracks/electronics/knowledge/`
- **Math** — Paul's Online Math Notes (web-based, no local PDF)
- **Linux** — sources in `tracks/linux/knowledge/`

Each track's `CLAUDE.md` lists its own books and materials.

---

## Directory Structure

```
tracks/
├── c-programming/
│   ├── knowledge/          — source PDFs + index
│   ├── material/           — lesson notes + problems per session
│   ├── projects/           — user codes here (Vim)
│   └── progressions/       — c.md, vim.md, gdb.md
├── electronics/
│   ├── knowledge/          — source PDF + index
│   ├── material/           — notes per chapter
│   ├── simulations/        — Falstad circuit exports
│   └── progressions/       — electronics.md
├── math/
│   ├── problem-sets/       — rewritten problems per section
│   └── progressions/       — math.md
└── linux/
    ├── knowledge/          — source PDF + index
    ├── material/           — summary, exercises, labs per chapter
    └── progressions/       — linux.md
```

---

## How to Start a Session

The user works from each track's directory (e.g., `tracks/c-programming/`).
Each track has its own `CLAUDE.md` that points back here.

1. Read `progress.md` — know where each track is.
2. User tells you which track (or ask if unclear).
3. Read the track's `CLAUDE.md` for that track's specific workflow.
4. **Enter plan mode** before writing any material for a new chapter/section.
5. Follow the workflow. Don't improvise the format.

---

## General Rules

- **One chapter/section at a time.** Don't get ahead of the user.
- **No over-engineering.** Create files only when a session actually happens.
- **Focus on concepts.** Why is this command sequence used? Where is this circuit used in real life? What uses this math equation? Ground every topic in understanding, not just procedure.
- **No filler.** Short sentences. Dense content. No padding.
- **Tracks are self-contained.** Track CLAUDE.md files should not reference or edit this main CLAUDE.md.
- At the end of every session, update `progress.md`.
- User views `.md` files with `glow` (paged). Keep formatting glow-friendly.

---

## Tools
- Circuit Simulator: Falstad CircuitJS1 (installed locally, `circuitjs1` command)
- Editor: Vim (user is learning — use it for all C coding sessions)
- Debugger: GDB (user is learning — use it for all C debugging sessions, always compile with `-g`)
- vimrc: lives at `~/.vimrc`, backup at `tracks/c-programming/vimrc.bak`. C-optimized. Update both when changes are made.
