# Electronics Track — Claude Instructions

## Parent Context
This track lives inside a larger project. Also read:
- `../../CLAUDE.md` — top-level rules, general workflow, sync instructions
- `../../progress.md` — current chapter per track, update after every session

## Source
"The Art of Electronics" — `knowledge/The Art of Electronics 3rd ed [2015].pdf`.

## Background
User has a CE degree. This is a refresh. Goal: understand the "why" better, not just the formulas.

---

## Directory Structure

```
knowledge/          — source PDF + index.md (chapter status tracker)
material/           — lesson content per chapter (notes.md)
simulations/        — Falstad circuit exports (.txt)
progressions/       — skill/concept progression tracking
```

---

## Workflow Per Chapter

1. User says which chapter.
2. **Enter plan mode first.** Read the chapter from Art of Electronics, then present a plan: what concepts/circuits will be covered, how the notes will be structured, and key takeaways. User confirms or adjusts before you write anything.
3. Write `material/chXX-<name>/notes.md` — clear summary of circuits/components, the math, the intuition.
4. Append new concepts to `progressions/electronics.md`.
5. User reads your notes instead of the dense book.
6. User works through the book's existing example problems (using the book).
7. User builds circuits in Falstad, exports the .txt to `simulations/`.

---

## Notes Format (`material/chXX-<name>/notes.md`)

For each concept/circuit:
```
### <Circuit or Concept Name>
**What it is:** ...
**The math:** ...
**Intuition:** ...
**Where you see it in real hardware:** ...
```

Prioritize intuition. The math should serve the intuition, not replace it.
Tie to embedded/firmware where relevant (e.g., ADC input protection, pull-up resistors, bypassing).

---

## Simulations

- User builds in Falstad (CircuitJS1 installed locally, or https://www.falstad.com/circuit/)
- User exports circuit as text (File → Export as Text) and saves to `simulations/`.
- Filename: `chXX-<circuit-name>.txt`
- You do NOT need to parse these files. They're the user's lab work artifact.

---

## Progressions (`progressions/`)

### `electronics.md`
- Tracks concepts/circuits introduced per chapter
- Quick reference so user knows what building blocks they have so far
- Append each session, never re-list already-covered concepts

Format (appended each session):
```
## Ch. X — <Chapter Name>
*New this session:*
- <concept/circuit> — one-line description
```

---

## Rules
- One chapter at a time. Chapters in order.
- Don't skip foundational material — Ch. 1 basics matter.
- Tie electronics concepts to C/embedded whenever relevant.
- Update `../../progress.md` after each session.
- Update `knowledge/index.md` — mark the chapter done.
- Append concepts to `progressions/electronics.md` every session — no exceptions.
