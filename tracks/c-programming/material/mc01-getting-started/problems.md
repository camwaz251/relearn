# Session 1 — Problems
**Modern C Ch 1–2 | MES Ch 1 Sidebar**

---

### Problem 1: Fix the Bad Program

**Context:** Compiler diagnostics are your first debugging tool. On embedded, the compiler may be all you have before flashing — there's no "run it and see" when your target is a bare-metal MCU.

**Thought process:**
1. What am I being asked to do? Fix `bad.c` so it compiles without warnings under `-Wall -Wextra -std=c2x`.
2. What tools do I have? The compiler diagnostics — each warning tells me the file, line number, and what's wrong.
3. Strategy: Fix one warning at a time, starting from the first. Recompile after each fix. The first error can cause cascading warnings, so fixing it may resolve others.
4. Gotchas: There are at least three differences from `getting-started.c`. One is a missing `#include`, one is a wrong return type, and there may be a subtler third issue (think about types and format specifiers).

**Task:** Start with the `bad.c` file from the notes. Compile with `gcc10-gcc -Wall -Wextra -g -std=c2x -o bad bad.c -lm`. Fix the first warning, recompile. Repeat until zero warnings. Your final program should produce the same output as `getting-started.c`.

---

### Problem 2: Sensor Calibration Table

**Context:** Embedded devices store calibration constants — offset and gain values for ADC channels, temperature compensation coefficients. These are typically stored as arrays indexed by sensor channel. Designated initializers make the mapping from channel number to calibration value explicit and readable.

**Thought process:**
1. What am I producing? A program that declares a calibration table (array of doubles), initializes specific channels using designated initializers, and prints each channel's value.
2. What are the inputs/constraints? Say 8 ADC channels (indices 0–7). Only channels 0, 2, 5, and 7 have sensors connected. The rest should default to `0.0`.
3. What C mechanism fits? Designated initializers: `[channel] = value`. Loop with `size_t` to iterate. `%zu` and `%g` for printing.
4. Edge cases: Uninitialized channels should print `0` (the default). Use `EXIT_SUCCESS`.

**Task:** Write a program `calibration.c` that:
- Declares `double cal_table[8]` using designated initializers for channels 0, 2, 5, and 7 (pick realistic-looking values like `1.023`, `0.998`, `1.105`, `0.972`)
- Loops over all 8 channels using `size_t`
- Prints: `channel N: cal = V` using `%zu` and `%g`
- Returns `EXIT_SUCCESS`
- Compiles clean with `gcc10-gcc -Wall -Wextra -g -std=c2x`

---

### Problem 3: Scope Detective

**Context:** In firmware, accidental variable shadowing between an interrupt service routine (ISR) and the main loop can cause subtle, intermittent bugs. Understanding exactly which variable is visible at each point in the code is a survival skill.

**Thought process:**
1. What am I being asked? Read code and determine which variable `x` refers to at each marked point.
2. What do I know? Block scope hides outer declarations. For-loop variables are scoped to the loop. Inner blocks see outer variables unless they redeclare the same name.
3. How do I approach this? Trace each `x` outward from its use — find the nearest enclosing declaration.
4. Gotchas: Same name, different scope. The `x` inside a block is not the same `x` as outside.

**Task:** Without compiling, predict the output of this program. Then compile and verify.

```c
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int x = 10;
    printf("A: x = %d\n", x);

    {
        int x = 20;
        printf("B: x = %d\n", x);
    }

    printf("C: x = %d\n", x);

    for (int x = 0; x < 3; ++x) {
        printf("D: x = %d\n", x);
    }

    printf("E: x = %d\n", x);

    return EXIT_SUCCESS;
}
```

For each labeled print (A through E), write down which `x` it refers to and its value.

---

### Problem 4: Modernize a K&R Program

**Context:** Porting legacy firmware from C89 to modern C is a real embedded engineering task. Codebases written in the 1990s and 2000s are still running in production — medical devices, industrial controllers, avionics. When you touch that code, you should modernize it incrementally.

**Thought process:**
1. What am I producing? A modern C version of a K&R-style program.
2. What needs to change? `return 0` → `EXIT_SUCCESS`. `int i` → `size_t i`. Add designated initializers. Add `[[maybe_unused]]` where appropriate. Use `%zu` for `size_t`. Include the right headers.
3. What stays the same? The logic, the algorithm, the output.
4. Gotchas: Don't break the program while modernizing. The output should be identical before and after.

**Task:** Here's a K&R-style program. Rewrite it as Modern C (C23):

```c
#include <stdio.h>

main()
{
    float temps[5];
    int i;

    temps[0] = 72.0;
    temps[1] = 68.5;
    temps[2] = 75.2;
    temps[3] = 69.1;
    temps[4] = 71.8;

    for (i = 0; i < 5; ++i)
        printf("Sensor %d: %.1f F\n", i, temps[i]);

    return 0;
}
```

Your modernized version should:
- Use `int main(int argc, [[maybe_unused]] char* argv[argc+1])`
- Use designated initializers for the `temps` array
- Use `size_t` for the loop counter
- Use `%zu` for printing the index
- Return `EXIT_SUCCESS`
- Include all necessary headers
- Compile clean with `gcc10-gcc -Wall -Wextra -g -std=c2x`

---

### Problem 5: Resource Constraints — Thought Exercise

**Context:** Before writing any embedded code, you need to analyze what constraints matter most for your product. This shapes every design decision — language features, data structures, algorithms, sleep modes.

**Thought process:**
1. What am I being asked? Analyze a product scenario and rank which of the five MES constraints (RAM, ROM/flash, cycles, power, peripherals) are most critical.
2. What do I know? The five constraints from MES Ch 1. They're tradeable — saving one often costs another.
3. How do I approach this? Consider the product's environment, lifetime, power source, and real-time requirements.
4. What makes a good answer? Concrete reasoning, not just listing constraints. *Why* does power matter more than cycles for this product?

**Task:** For each scenario below, rank the top 2 most critical constraints and explain why in 2–3 sentences. No code — just thinking.

**Scenario A:** A battery-powered wildlife tracker attached to a migratory bird. Must run for 6 months on a coin cell. Logs GPS coordinates every 15 minutes, transmits via satellite once per day.

**Scenario B:** An engine control unit (ECU) in a car that manages fuel injection timing. Must respond to sensor inputs within microseconds. Runs off the car's alternator (unlimited power). Needs to handle dozens of sensor channels simultaneously.

**Scenario C:** A smart thermostat with an LCD display, WiFi, and a temperature sensor. Runs on wall power. Firmware updates delivered over WiFi. Needs to be responsive to user button presses.
