# Electronics Track — Claude Instructions

The repo-root `CLAUDE.md` loads automatically alongside this file — it holds the
general project rules. Also update `../../progress.md` after every session.

## Source
"The Art of Electronics" — `knowledge/The Art of Electronics 3rd ed [2015].pdf`.

## Background
User has a CE degree. This is a refresh. Goal: understand the "why" better, not just the formulas.

---

## Directory Structure

```
knowledge/          — source PDF + index.md (chapter status tracker)
material/           — lesson content per chapter, structured as:
  chXX-<name>/
    sX.Y-<name>/    — one subfolder per top-level section
      notes.md      — concept notes for that section
      problems.md   — in-chapter exercises for that section
    exercises/
      problems.md   — Additional Exercises block at end of chapter
    review/
      notes.md      — Review of Chapter summary
simulations/        — Falstad circuit exports (.txt)
progressions/       — skill/concept progression tracking
```

---

## Workflow Per Chapter

1. User says which chapter.
2. **Enter plan mode first.** Read the chapter ToC from Art of Electronics, plan the section breakdown, confirm with user before writing anything.
3. For each top-level section (e.g., 1.2, 1.3), write `material/chXX-<name>/sX.Y-<name>/notes.md`.
4. For each section, create `problems.md` — stub all in-chapter exercises for that section with **Problem:**, **My work:**, **Answer:** fields.
5. Create `exercises/problems.md` — stub all Additional Exercises at the end of the chapter.
6. Create `review/notes.md` — condensed one-page summary of the whole chapter.
7. Append new concepts to `progressions/electronics.md`.
8. User reads section notes instead of the dense book.
9. User works exercises; fill in **My work** and **Answer** as they complete each one.
10. User builds circuits in Falstad, exports .txt to `simulations/`.

---

## Notes Format (`sX.Y-<name>/notes.md`)

Header:
```
# Ch. X.Y — <Section Name>
*Art of Electronics, pp. X–Y (§X.Y.1–X.Y.Z)*
```

For each subsection concept:
```
### <Subsection or Concept Name>

**What it is:** ...
**The math:** ...
**Intuition:** ...
**Where you see it in real hardware:** ...
```

Narrower scope per file = more subsection detail. Cover every numbered subsection.
Prioritize intuition. Math serves intuition, not the other way around.
Tie to embedded/firmware where relevant.

---

## Problems Format (`problems.md`)

```
# Problems — Ch. X.Y (<Section Name>)
*Art of Electronics, §X.Y in-chapter exercises*

## Exercise X.N
**Problem:** <statement from book>

**My work:**

**Answer:**
```

Fill in **Problem:** from the book text when creating the file.
Leave **My work:** and **Answer:** blank — user fills these in during session.
Do not reveal answers until user has attempted the problem.

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
- Update `knowledge/index.md` — mark the chapter done when all sections complete.
- Append concepts to `progressions/electronics.md` every session — no exceptions.
- Do not reveal exercise answers until the user has attempted the problem.
