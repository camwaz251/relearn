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

---

### Problem 2: Overflow Accumulator Bug

**Context:** Summing multiple ADC readings to average them is a classic firmware pattern — and a classic source of silent overflow bugs when the wrong integer type is used.

**Thought process:**
1. What am I showing? That summing 16 × 12-bit ADC values (max 4095 each) overflows `uint16_t` (max 65535) when values are large, but fits fine in `uint32_t`.
2. What are the numbers? 16 samples × 4095 max = 65520. That is just under `uint16_t` max of 65535 — so it barely fits but is dangerously close. Use values that DO overflow to show the bug clearly.
3. How to show the bug? Sum into `uint16_t`, print the wrong result. Then sum into `uint32_t`, print the correct result. Then divide by 16 for the average.
4. Gotchas: Promotion rules mean `uint16_t + uint16_t` promotes to `int` anyway — the bug manifests on assignment back to `uint16_t`. Make this explicit.

**Task:** Write `accumulator.c` with:
- `uint16_t samples[16]` initialized with all values = 4090 (so sum = 65440 — near the edge)
- Show the sum computed into `uint16_t` (may or may not overflow — try values that do)
- Show the same sum into `uint32_t` — correct result
- Print both sums and the correct average
- Then try samples all = 4095 and show the overflow clearly
- Compile: `gcc -Wall -Wextra -g -std=c2x -o accumulator accumulator.c`

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
- `main` that prints a table: raw value, millivolts, percent — for 9 evenly spaced values from 0 to 4095
- Output should be neatly column-aligned using `%5u` format
- Compile: `gcc -Wall -Wextra -g -std=c2x -o adc_scale adc_scale.c`

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
