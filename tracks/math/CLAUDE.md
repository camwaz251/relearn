# Math Track — Claude Instructions

The repo-root `CLAUDE.md` loads automatically alongside this file — it holds the
general project rules. Also update `../../progress.md` after every session.

## Source
Paul's Online Math Notes — https://tutorial.math.lamar.edu/
User navigates the site directly. Solutions are on the website. No local PDF.

## Background
User has a CE degree. Wants to conceptualize better. Main gap: real-world framing.

---

## Directory Structure

```
problem-sets/       — problem set files per section
progressions/       — concept progression tracking
```

---

## Order
Algebra/Trig Review → Calc I → Calc II → Calc III

---

## Workflow Per Section

1. User sends a Paul's section URL (or names the section).
2. **Enter plan mode first.** Look at the section, then present a plan: what concepts are covered, how many problems you'll write. User confirms or adjusts before you write anything.
3. Write a problem set file in `problem-sets/`:
   - Filename: `<subject>-s<NN>-<topic>.md` (e.g., `algebra-trig-s01-exponents.md`)
4. Append new concepts to `progressions/math.md`.
5. User does the problems — solutions are on Paul's site.

---

## Problem Set Format

```markdown
# <Section Name> — Problem Set

**Source:** <Paul's URL>

---

**When you'd use this:** <short note on when these problems/equations come up — not just engineering, any real context>

### Problem 1
<problem rewritten in plain English/sentence form>

### Problem 2
<problem rewritten in plain English/sentence form>

...
```

- Group similar problems together under a shared section.
- Each group gets a "When you'd use this" note above it.
- Rewrite each problem in sentence/English form so the user can conceptualize what's being asked.
- No worked solutions in the file — they're on the website.
- That's it. Keep it simple.

---

## Progressions (`progressions/`)

### `math.md`
- Tracks math concepts introduced per section
- Minimal — just concept name and one-line description
- Append each session, never re-list already-covered concepts

Format (appended each session):
```
## <Subject> — <Section Name>
*New this session:*
- <concept> — one-line description
```

---

## Rules
- Keep it simple. Problem sets are just rewritten problems with context notes.
- Update `../../progress.md` after each session with the Paul's section covered.
- Append concepts to `progressions/math.md` every session — no exceptions.
