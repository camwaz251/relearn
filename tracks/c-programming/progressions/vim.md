# Vim Progression

Tracks every Vim command introduced across C sessions — one layer at a time, like vimtutor.
Each session adds 3–5 commands that are immediately useful for the code being written.

---

## Baseline (already known before sessions started)

*User knows basic Vim going in. Commands below are assumed — do NOT re-introduce these.*

| Command | What it does |
|---------|-------------|
| `i` / `a` | Insert mode before / after cursor |
| `ESC` | Return to normal mode |
| `h j k l` | Move left / down / up / right |
| `w` / `b` | Jump forward / backward by word |
| `x` | Delete character under cursor |
| `dd` | Delete (cut) current line |
| `yy` | Yank (copy) current line |
| `p` | Paste below current line |
| `u` | Undo |
| `Ctrl-r` | Redo |
| `:w` | Save |
| `:q` / `:q!` | Quit / force quit |
| `:wq` | Save and quit |
| `/pattern` | Search forward |
| `n` / `N` | Next / previous search result |

---

<!-- New sessions append below this line -->

## Ch. 1 — A Tutorial Introduction
*New this session:*

| Command | What it does | Example |
|---------|-------------|---------|
| `o` / `O` | Open new line below / above and enter insert mode | After a `printf`, press `o` to add the next statement |
| `A` | Append at end of line | Jump to end of a line to add a missing semicolon |
| `dw` | Delete word | Remove a variable name to retype it |
| `0` / `$` | Jump to beginning / end of line | Navigate to the start of a `#define` line |
| `gg` / `G` | Jump to top / bottom of file | Go to top to add `#include`, bottom to add a function |

## Session 1 — Getting Started (Modern C Ch 1–2)
*New this session:*

| Command | What it does | Example |
|---------|-------------|---------|
| `%` | Jump to matching bracket `{}`/`()`/`[]` | Navigate from opening `{` of main to its closing `}` |
| `ci"` | Change inside quotes | Fix a format string: cursor on `"`, `ci"` replaces contents |
| `ci(` | Change inside parentheses | Rewrite printf arguments: cursor inside `()`, `ci(` |
| `:set number` / `:set nu` | Show line numbers | Match compiler error "line 17" to your code |

## Session mc02 — Control (Modern C Ch 3)
*New this session:*

| Command | What it does | Example |
|---------|-------------|---------|
| `V` | Select entire line in visual mode | Select a `case` block to indent it |
| `>` / `<` | Indent / unindent selected lines | Fix switch case indentation after pasting |
| `=` | Auto-indent selected lines | Reformat a misaligned `if/else` block |
| `]]` / `[[` | Jump to next / previous `{` at column 0 | Navigate between top-level functions |
| `*` | Search forward for word under cursor | Find all uses of a state enum value |

## Session mc03 — Computations (Modern C Ch 4)
*New this session:*

| Command | What it does | Example |
|---------|-------------|---------|
| `r<char>` | Replace single character under cursor | Fix `&` to `|` in a bitwise expression |
| `J` | Join current line with the next | Merge a split `#define` back onto one line |
| `Ctrl-a` / `Ctrl-x` | Increment / decrement number under cursor | Change `(1U << 5)` to `(1U << 6)` |

## Session mc04 — Values and Data (Modern C Ch 5)
*New this session:*

| Command | What it does | Example |
|---------|-------------|---------|
| `gd` | Go to local declaration of variable | Jump to where `adc_raw` was declared |
| `'.` | Jump to last edit location | Return to where you last made a change |
| `:%s/old/new/g` | Replace all occurrences in file | Rename `int` to `uint32_t` everywhere |

## Session mc05 — Derived Types (Modern C Ch 6)
*New this session:*

| Command | What it does | Example |
|---------|-------------|---------|
| `va{` | Visual-select inside `{}` block (including braces) | Select an entire struct body |
| `di{` | Delete contents inside `{}` | Clear struct fields to rewrite |
| `f<char>` / `F<char>` | Find character forward / backward on line | Jump to `.` in `cfg.pin` |
| `zz` | Center screen on current line | Keep your struct definition in view |
