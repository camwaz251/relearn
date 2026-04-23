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

### Step 1 — Plan
1. User says which chapter.
2. **Enter plan mode first.** Read the chapter ToC from the PDF, identify all top-level sections (e.g., 2.1, 2.2, 2.3). Present the section breakdown and confirm with user before writing anything.

### Step 2 — Create structure
3. Create `material/chXX-<name>/` with one subfolder per top-level section, plus `exercises/` and `review/`.
4. PDF page offset: find it by reading a known page (e.g., the ToC) and comparing book page number to PDF page number. Record it — all agents need it.

### Step 3 — Write notes (one agent per section, all in parallel)
5. **Launch one background agent per section.** Each agent must:
   - Read its assigned PDF pages (book page + offset = PDF page)
   - Write `notes.md` based strictly on what those pages say — not from memory
   - Cover every numbered subsection
   - Follow the notes format below
   - Include embedded/firmware tie-ins where relevant
6. Do NOT write notes from memory or prior knowledge. Every agent reads the source.

### Step 4 — Write problems stubs
7. For each section, create `problems.md` — stub all in-chapter exercises found in the PDF with **Problem:** (from book text), **My work:**, **Answer:** fields.
8. Create `exercises/problems.md` — stub all Additional Exercises at chapter end.

### Step 5 — Review and finalize
9. Create `review/notes.md` — condensed one-page summary of the whole chapter.
10. Append new concepts to `progressions/electronics.md`.
11. Commit and push.

### During sessions (working exercises)
12. User reads section notes instead of the dense book.
13. User works exercises; fill in **My work** and **Answer** as they complete each one.
14. User builds circuits in Falstad, exports .txt to `simulations/`.
15. Update `../../progress.md` after each session.

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
