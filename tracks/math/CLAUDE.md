# Math Track — Claude Instructions

The repo-root `CLAUDE.md` loads automatically alongside this file — it holds the
general project rules. Also update `../../progress.md` after every session.

## Source
Paul's Online Math Notes — https://tutorial.math.lamar.edu/
User navigates the site directly for section-level reading and solutions.
Local PDFs are in `knowledge/` for reference.

## Local Knowledge (`knowledge/`)

All PDFs downloaded from Paul's Online Math Notes.

### Algebra/Trig Review (`knowledge/algebra-trig-review/`)
Paul's Calc I prerequisite review — separate from the main Algebra class.
| File | Contents |
|------|----------|
| `notes.pdf` | Complete Algebra/Trig Review notes (948 KB) |
| `practice-problems.pdf` | Practice problems only (528 KB) |

### Cheat Sheets (`knowledge/cheat-sheets/`)
| File | Contents |
|------|----------|
| `algebra-cheat-sheet.pdf` | Algebra facts, properties, formulas, common errors (4 pp) |
| `trig-cheat-sheet.pdf` | Trig identities, unit circle, formulas (4 pp) |
| `calculus-complete-cheat-sheet.pdf` | Limits, derivatives, integrals — full reference (11 pp) |
| `common-derivatives-integrals.pdf` | Frequently-used derivatives & integrals quick-ref (4 pp) |
| `laplace-transforms-table.pdf` | Common Laplace transform pairs (2 pp) |

### Algebra (`knowledge/algebra/`)
| File | Contents |
|------|----------|
| `notes.pdf` | Complete Algebra lecture notes |
| `practice-problems.pdf` | Practice problems only (no solutions) |
| `practice-solutions.pdf` | Practice problems with full solutions |
| `assignment-problems.pdf` | Assignment/extra problems |

### Calculus (`knowledge/calculus/`)
Combined Calc I + II + III book.
| File | Contents |
|------|----------|
| `notes.pdf` | Complete Calculus lecture notes (Calc I/II/III, 9.4 MB) |
| `practice-problems.pdf` | Practice problems only |
| `practice-solutions.pdf` | Practice problems with full solutions (16 MB) |
| `assignment-problems.pdf` | Assignment/extra problems |

### Differential Equations (`knowledge/differential-equations/`)
| File | Contents |
|------|----------|
| `notes.pdf` | Complete Differential Equations lecture notes |

## Background
User has a CE degree. Wants to conceptualize better. Main gap: real-world framing.

---

## Directory Structure

```
knowledge/
├── cheat-sheets/   — algebra, trig, calculus, common deriv/integrals, laplace PDFs
├── algebra/        — notes, practice problems, solutions, assignments
├── calculus/       — combined Calc I/II/III: notes, practice, solutions, assignments
└── differential-equations/ — notes
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
