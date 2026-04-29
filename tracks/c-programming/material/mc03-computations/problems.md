# Session mc03 — Problems
**Modern C Ch 4 (pp. 34–43) + Ch 5 §5.7 (pp. 66–68) | MES Ch 4 sidebar**

---

### Problem 1: The Four Register Operations

**Context:** GPIO manipulation is the first thing you do on any new MCU — you need to set, clear, toggle, and read pins before anything else works.

**Thought process:**
1. What am I producing? Four functions operating on a simulated `uint32_t` register using only bitwise operators.
2. What are my constraints? No arithmetic — only `|`, `&`, `^`, `~`, `<<`. Use `1U << n` for masks.
3. What's the pattern? Set = OR with mask. Clear = AND with inverted mask. Toggle = XOR. Read = AND then compare to zero.
4. Gotchas: Always use `1U` not `1`. Pass register by pointer so the function modifies the actual value. Test all four on the same register and print state after each op.

**Task:** Write `registers.c` with:
- `#define` macros for pins 0, 4, 7, 15 using `1U << n`
- Four functions: `reg_set`, `reg_clear`, `reg_toggle`, `reg_read` — each takes `volatile uint32_t *reg` and `uint32_t mask`
- `main` that runs a sequence of operations and prints the register value in hex after each one (`0x%08X`)
- Compile: `gcc -Wall -Wextra -g -std=c2x -o registers registers.c`

**Man pages:** `man 3 printf` (for `%08X` width/padding), `man 7 operator` (precedence of `&` vs `==` — this one bites everyone).

**Vim workflow:** Four near-identical small functions plus pin-mask `#define`s up top — `gg` to jump up to tweak a mask, `G` or `]]` to get back to the function you were editing. When you swap a bitwise operator in the middle of an expression, `r|` or `r&` on the character under the cursor is faster than deleting and retyping. If a pin number changes, `Ctrl-a` / `Ctrl-x` nudges the shift amount in `(1U << n)` without retyping. `*` on a `PIN_` macro name shows you every place it's used before you rename it.

**GDB workflow:** The whole point is to *see* bits change, so run in hex and binary. Compile with `-g`, `gdb ./registers`, `break main`, `run`, then `next` through your test sequence. After each operation, `p/x reg` confirms the hex (matches your `printf`) and `p/t reg` shows the binary so you can visually check exactly which bit flipped. `watch reg` is useful if a clear or toggle is producing the wrong value — GDB will stop the instant `reg` changes, and you can compare before/after in `/t` format.

---

### Problem 2: Overflow Accumulator Bug

**Context:** Summing multiple ADC readings to average them is a classic firmware pattern — and a classic source of silent overflow bugs when the wrong integer type is used.

**Thought process:**
1. What am I showing? That summing 32 × 12-bit ADC values (max 4095 each) overflows `uint16_t` (max 65535), but fits fine in `uint32_t`. 32-sample oversampling is a realistic ADC noise-reduction pattern.
2. What are the numbers? 32 samples × 4095 max = 131,040. That is ~2× `uint16_t` max (65,535), so it wraps clearly: 131,040 mod 65,536 = 65,504. With samples at 4000, sum = 128,000 → wraps to 62,464. Obvious, not borderline.
3. Why not 16 samples? 16 × 4095 = 65,520, which fits in `uint16_t` (barely). It wouldn't actually demonstrate the bug. Need enough samples that the true sum exceeds 65,535.
4. How to show the bug? Sum into `uint16_t`, print the wrong result. Then sum into `uint32_t`, print the correct result. Then divide by 32 for the average.
5. Gotchas: Promotion rules mean `uint16_t + uint16_t` promotes to `int` anyway — the bug manifests on assignment back to `uint16_t`. Make this explicit.

**Task:** Write `accumulator.c` with:
- `uint16_t samples[32]` initialized with all values = 4000 (so true sum = 128,000)
- Show the sum computed into `uint16_t` — demonstrates the overflow/wrap
- Show the same sum into `uint32_t` — correct result
- Print both sums and the correct average (divide by 32)
- Then try samples all = 4095 (true sum = 131,040) and show the overflow is even larger
- Compile: `gcc -Wall -Wextra -g -std=c2x -o accumulator accumulator.c`

**Man pages:** `man 3 printf` (`%u` vs `%lu` — width matters for wide sums), `man 3type uint16_t` (confirm the exact width of each type on your machine).

**Vim workflow:** Two parallel loops (one summing into `uint16_t`, one into `uint32_t`) — once you've written the first, `V` + `y` to yank the block and `p` to paste, then retype only the type and variable name. `:set nu` helps when the compiler warns about truncation so you can find the offending line fast. If you want to sweep the sample count or value everywhere, `:%s/4000/4095/g`-style replacement is tempting but not yet introduced — stick with `*` to locate occurrences and edit them in place.

**GDB workflow:** The bug is silent, so you need to *see* the wrap happen. Compile with `-g`, `gdb ./accumulator`, `break` at the `uint16_t` accumulating line, `run`. `display sum16` auto-prints the narrow sum after every step, and `p/t sum16` in binary makes the wrap obvious the moment the 17th bit would have been set. Compare against `sum32` with `p sum32` at the same iteration. `info locals` inside the loop gives you everything — counter, both sums, current sample — in one shot.

---

### Problem 3: ADC to Millivolts (Integer Scaling)

**Context:** Every ADC driver needs a raw-count-to-engineering-units conversion — this is the function that appears in virtually every sensor driver you will ever write.

**Thought process:**
1. What am I producing? A function `uint32_t adc_to_mv(uint16_t raw)` that converts a 12-bit ADC count to millivolts.
2. What are the numbers? 0 → 0 mV, 4095 → 3300 mV. Formula: `mv = (raw * 3300) / 4095`.
3. Overflow check: `4095 * 3300 = 13,513,500`. Fits in `uint32_t` (max ~4.3 billion). Must cast `raw` to `uint32_t` before multiplying.
4. Gotchas: If you forget the cast, `raw * 3300` is computed as `uint16_t * int` — promoted to `int` which is 32-bit on most platforms so it works, but is relying on platform behavior. Be explicit.

**Task:** Write `adc_scale.c` with:
- `adc_to_mv()` function using integer-only math
- A second function `adc_to_mv_percent(uint16_t raw)` returning 0–100 as `uint8_t`
- `main` that prints a table: raw value, millivolts, percent — loop `for (uint16_t raw = 0; raw < 4095; raw += 512)` and then print one final row for `raw = 4095`. This gives clean power-of-two steps across the 12-bit range (0, 512, 1024, …, 3584) plus the endpoint.
- Output should be neatly column-aligned using `%5u` format
- Compile: `gcc -Wall -Wextra -g -std=c2x -o adc_scale adc_scale.c`

**Man pages:** `man 3 printf` (`%5u` width specifier and why it matters for column alignment), `man 7 operator` (confirms `*` binds tighter than `/`, so `raw * 3300 / 4095` evaluates as expected).

**Vim workflow:** Two small conversion functions on top of a `main` that prints a table — `]]` to jump between them, `A` to append to the end of a format string when tweaking column widths. When you want to see the whole table-generating loop in context, `V%` (line-select then jump to matching brace) selects the whole `for` body at once. `r` on a single digit of a format width is faster than retyping the whole specifier.

**GDB workflow:** The bug you're defending against is silent integer truncation from missing the `(uint32_t)` cast. Compile with `-g`, `gdb ./adc_scale`, `break adc_to_mv`, `run`. `step` into the function, then `p raw` and `p/x raw * 3300` — if the intermediate is the right width, you'll see a big number; if promotion went sideways, the hex will look suspiciously short. `ptype` on the intermediate expression would tell you the type directly, but that's an mc04 command — for now, comparing hex widths is the tell. `display raw` while stepping through the table lets you sanity-check each row without re-typing.

---

### Problem 4: Status Register Decoder

**Context:** Every time you call a HAL function and it returns an error, somewhere inside it read a peripheral status register and checked flags exactly like this.

**Thought process:**
1. What am I producing? A function that takes a `uint32_t` status register value and prints which flags are set.
2. What's the register? Simulate a UART status register with these bits: bit 7 = TXE, bit 6 = TC, bit 5 = RXNE, bit 3 = ORE, bit 0 = PE (parity error).
3. How to check flags? Independent `if` blocks (not `else if`) — multiple flags can be set simultaneously. Each check: `if (sr & FLAG_MASK)`.
4. Gotchas: Use named `#define` macros for each flag, not magic numbers. Test with at least 3 different register values including one with multiple flags set simultaneously.

**Task:** Write `status_decode.c` with:
- `#define` for each flag bit using `1U << n`
- `void decode_uart_sr(uint32_t sr)` that prints each set flag by name
- `main` that calls it with at least these test values:
  - `0x00000080` — only TXE
  - `0x00000028` — TC + RXNE
  - `0x000000E9` — TXE + TC + RXNE + PE (all upper bits + PE)
  - `0x00000000` — no flags (print "no flags set")
- Compile: `gcc -Wall -Wextra -g -std=c2x -o status_decode status_decode.c`

**Man pages:** `man 3 printf` (`%08X` for the register dump line), `man 7 operator` (reminder that `&` has *lower* precedence than `==`, so `sr & FLAG == 0` parses wrong — parenthesize).

**Vim workflow:** Stack of flag `#define`s at the top and a decoder function that's mostly a list of `if` blocks — `gg` / `G` to bounce between them while keeping masks and checks in sync. `*` on a flag macro (e.g. on `TXE`) jumps through every use, so if you rename one you can catch them all. `Ctrl-a` / `Ctrl-x` on the shift amount in `(1U << n)` nudges a bit position without retyping the expression.

**GDB workflow:** The whole function is about which bits of a value are set, so debug in bit form. Compile with `-g`, `gdb ./status_decode`, `break decode_uart_sr`, `run`. At the breakpoint, `p/t sr` prints the register in binary so you can *see* which flags should fire before you step through the `if`s. `p/x sr & TXE` (or whichever mask) confirms the AND result — zero or not. `next` through each `if` and watch which branches you actually enter; if one fires when it shouldn't, that's your precedence/parenthesization bug. `info locals` at the end tells you whether any "matched at least one flag" tracking variable ended up where you expected.
