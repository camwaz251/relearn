# Session mc02 — Problems
**Modern C Ch 3 (pp. 23–33) | MES Ch 5 sidebar**

---

### Problem 1: LED Blink State Machine

**Context:** Every LED driver in production firmware runs a state machine — bare `HAL_GPIO_TogglePin` in a `while(1)` loop is only acceptable for blinky demos, and you've already graduated from those.

**Thought process:**
1. What am I producing? A program that cycles an LED through four states (OFF, ON, FADE_UP, FADE_DOWN) using a `switch` to dispatch behavior and a `typedef enum` to name the states. Output is `printf` simulating what would be GPIO/TIM register writes on the STM32.
2. What structure do I need? A `typedef enum` for the four states. A `switch` in a `process_state()` function that prints the current behavior. A `next_state()` function that returns the next state given the current one — also a `switch`. A `for` loop in `main` to drive the machine for N ticks.
3. What are the invariants? The `default` case in every `switch` must print an error — never silently ignore an unknown state. Every `case` must `break`. The enum and switch cases must be kept in sync (if you add a state to the enum, it must appear in both switches).
4. Gotchas: Don't use raw integers like `0`, `1`, `2` — use the enum names everywhere. If you cast or assign an out-of-range integer to the enum, the `default` case is your safety net. Test that the sequence wraps correctly: FADE_DOWN → OFF → ON → ...

**Task:** Write `led_state_machine.c` that:
- Defines a `typedef enum` with four states: `LED_OFF`, `LED_ON`, `LED_FADE_UP`, `LED_FADE_DOWN`
- Implements `LedState next_state(LedState current)` using `switch` — returns the next state in circular order: OFF → ON → FADE_UP → FADE_DOWN → OFF
- Implements `void process_state(LedState state)` using `switch` — prints a descriptive line for each state (e.g., `[LED] OFF`, `[LED] ON (full brightness)`, etc.)
- Runs the state machine for exactly 12 ticks in `main` using a `for` loop, printing the tick number and calling `process_state` then `next_state` each iteration
- Returns `EXIT_SUCCESS`
- Compiles clean with `gcc -Wall -Wextra -g -std=c2x`

---

### Problem 2: Button Debounce Polling Loop

**Context:** Raw GPIO reads on a mechanical button are noisy — a single press produces dozens of rapid 0/1 transitions as the contacts bounce, and firmware that reacts to each transition will miscount button presses.

**Thought process:**
1. What am I producing? A program that simulates reading a button GPIO and only registers a press after the signal has been stable (consistently 1) for a minimum number of consecutive samples. This is the software debounce pattern used in virtually every STM32 GPIO driver.
2. What data do I need? A simulated stream of button readings (an array of `uint8_t` values, 0 or 1). A stable-count threshold (e.g., 5 consecutive highs). A counter that resets to 0 any time the signal drops back to 0.
3. What loop structure? An outer `for` to iterate over all readings (simulating a polling tick). Inside, a `while` is the wrong choice here — we process one sample per tick. Use `if/else` inside the `for` to either increment the stable counter or reset it. When the counter reaches the threshold, register a press and reset the counter.
4. Gotchas: After registering a press, reset the counter so you don't double-count. The bounce pattern at the start of the array should NOT register a press. Only a sustained run of 1s long enough to meet the threshold counts. Print each tick's raw reading and counter value so you can verify the logic is working step by step.

**Task:** Write `debounce.c` that:
- Defines `uint8_t button_samples[]` with at least 20 entries simulating a bouncy press: several alternating 0/1 values, then a sustained run of 1s long enough to exceed the threshold, then 0s again
- Defines `#define DEBOUNCE_THRESHOLD 5`
- Loops over all samples with a `for`, maintaining a `stable_count` variable
- On each tick, prints: `tick N: raw=V stable_count=C` (where V is 0 or 1)
- When `stable_count` reaches `DEBOUNCE_THRESHOLD`, prints `*** BUTTON PRESS REGISTERED ***` and resets the counter
- Compiles clean with `gcc -Wall -Wextra -g -std=c2x`

---

### Problem 3: Register Bit Decoder

**Context:** On the STM32F407, diagnosing a peripheral fault means reading a status register and decoding which flag bits are set — the reference manual lists what each bit means, and you check them one by one with bitwise AND.

**Thought process:**
1. What am I producing? A program that takes a simulated 32-bit status register value and uses `if/else if/else` with bitmask checks (`& operator`) to decode and print which flags are active. This is the exact pattern in any STM32 HAL error handler.
2. What bitmask pattern to use? Define each flag as a macro using `(1U << N)` for bit position N. Apply `reg & MASK` in each `if` condition — if nonzero, the flag is set. Some flags may be set simultaneously — use separate `if` statements (not `else if`) for independent flags, and `else if` for mutually exclusive ones.
3. What's the input? Define at least five bit flags (give them plausible names like `SR_BUSY`, `SR_RX_FULL`, `SR_TX_EMPTY`, `SR_PARITY_ERR`, `SR_FRAME_ERR`). In `main`, declare `uint32_t status_reg` with a hardcoded value that sets at least three of the five flags simultaneously.
4. Gotchas: `&` vs `&&` — bitwise AND extracts the bit; logical AND would require a boolean. `1 << 31` is undefined behavior (shifting into the sign bit of a signed int) — always use `1U << N` or `UINT32_C(1) << N`. Test with at least two different register values and verify the output changes correctly.

**Task:** Write `reg_decoder.c` that:
- Defines at least five flag macros using `(1U << N)` for distinct bit positions
- In `main`, declares `uint32_t status_reg` and assigns a value that sets at least three flags
- Uses separate `if` blocks (not `else if`) to check and print each flag independently — e.g., `"[SR_BUSY] Peripheral is busy\n"` — since multiple flags can coexist
- After decoding, prints a summary line: `"Decoded register: 0x%08X\n"` using `%X` format
- Runs the decode on a second register value (different bits set) to show the decoder working on different input
- Compiles clean with `gcc -Wall -Wextra -g -std=c2x`

---

### Problem 4: ADC Channel Scanner (Embedded FizzBuzz)

**Context:** After a DMA transfer fills a buffer with all 16 ADC channel readings, firmware classifies each reading — values above a threshold may indicate a sensor fault (overvoltage), values below a threshold may indicate a disconnected sensor (open circuit), and values in range are normal.

**Thought process:**
1. What am I producing? A program that iterates over a 16-element array of simulated ADC readings (`uint16_t`, range 0–4095 for a 12-bit ADC) and for each channel prints `OVER`, `UNDER`, or `OK` based on threshold comparisons. The thresholds: OVER if > 3000, UNDER if < 100, OK otherwise.
2. What loop structure? A `for` over all 16 channels using `size_t`. Inside, `if / else if / else` for the three classification cases. Print channel number, raw value, and classification on one line per channel.
3. What data? Initialize `uint16_t adc[16]` using designated initializers. Include at least: one OVER value (> 3000), one UNDER value (< 100), several OK values, one at exactly the boundary (100 or 3000) — think about whether boundary values are OVER, UNDER, or OK and make sure your conditions match.
4. Gotchas: `uint16_t` max is 4095 for a 12-bit ADC (STM32 ADC is 12-bit). Don't use `int` for ADC readings — the type should reflect hardware. After the channel-by-channel output, add a summary: count how many channels are OVER, UNDER, and OK, and print totals. Use `size_t` counters for the totals.

**Task:** Write `adc_scan.c` that:
- Defines `#define ADC_CHANNELS 16u` and `#define ADC_OVER_THRESHOLD 3000u` and `#define ADC_UNDER_THRESHOLD 100u`
- Declares `uint16_t adc[ADC_CHANNELS]` with designated initializers, populating all 16 entries with a mix of OVER, UNDER, and OK values (use `[index] = value` syntax; uninitialized entries are 0 and will be UNDER)
- Iterates with `for (size_t ch = 0; ch < ADC_CHANNELS; ++ch)` and for each channel prints: `ADC[NN]: VVVV  ->  STATUS` (align columns with format width specifiers)
- Accumulates `size_t over_count`, `size_t under_count`, `size_t ok_count` during the loop
- After the loop prints: `Summary: %zu OVER, %zu UNDER, %zu OK\n`
- Compiles clean with `gcc -Wall -Wextra -g -std=c2x`
