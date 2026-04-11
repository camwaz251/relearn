# Session mc04 — Problems
**Modern C Ch 5 (pp. 44–76) | MES Ch 4 sidebar**

---

### Problem 1: Type Size Audit

**Context:** Before writing any driver, a firmware engineer needs to know exactly what types they're working with on their target — surprises here cause bugs that take days to find.

**Thought process:**
1. What am I producing? A program that prints the size of every relevant type on this platform.
2. What types matter? `char`, `short`, `int`, `long`, `long long`, `uint8_t` through `uint64_t`, `float`, `double`, `void *`.
3. How to print sizes? `sizeof` returns `size_t` — print with `%zu`. Never use `%d` for `sizeof`.
4. What to look for? `int` = 4 on this platform. `long` = 8 on Linux 64-bit (but 4 on bare-metal ARM). `double` = 8. Pointer = 8 on 64-bit host. On the STM32F407 target, pointer will be 4.

**Task:** Write `type_audit.c` that:
- Prints a neat table of type name, size in bytes, and min/max values using `<limits.h>` and `<stdint.h>` macros (`UINT8_MAX`, `INT32_MIN`, `INT32_MAX`, etc.)
- Includes: `char`, `unsigned char`, `short`, `int`, `long`, `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t`, `int32_t`, `float`, `double`, `void *`
- Format: `%-12s %2zu bytes   max=%llu` (right-pad name, show size, show max where applicable)
- Compile: `gcc -Wall -Wextra -g -std=c2x -o type_audit type_audit.c`

---

### Problem 2: `volatile` vs Non-Volatile at -O2

**Context:** Understanding why `volatile` exists is critical before you ever touch a peripheral register — without it your polling loops silently break at higher optimisation levels.

**Thought process:**
1. What am I showing? The difference in generated code between a volatile and non-volatile polling loop.
2. How to see it? Compile with `-O2 -S` to get assembly output. Look at whether the variable is loaded from memory each loop iteration or cached in a register.
3. What's the expected result? Non-volatile: compiler caches value in register, loop may become infinite or be eliminated. Volatile: memory load every iteration.
4. Gotcha: On the host machine the non-volatile version may still work because the compiler isn't that aggressive. The behaviour is undefined, not "guaranteed to break." The exercise is about the assembly, not the runtime result.

**Task:** Write `volatile_demo.c` with:
- `uint32_t reg_bad = 1` (no volatile)
- `volatile uint32_t reg_good = 1`
- Two functions `poll_bad()` and `poll_good()` that loop while the register is non-zero
- `main` that sets both to 0 after 100 iterations of a counter, calls both functions, prints "done"
- Compile twice: `gcc -Wall -Wextra -g -std=c2x` and `gcc -Wall -Wextra -O2 -std=c2x`
- Then compile with `-S` flag and compare the assembly for both functions: `gcc -O2 -S -std=c2x volatile_demo.c`
- In comments in your source, note what you observed in the assembly

---

### Problem 3: `const` Calibration Table

**Context:** Sensor calibration coefficients are determined at manufacturing time and never change during runtime — they belong in Flash as `const`, not wasting RAM.

**Thought process:**
1. What am I producing? A `const` array of calibration gains for 4 ADC channels, plus a function that applies the calibration.
2. What happens if I try to modify a `const`? Compiler error (or warning depending on how accessed). Try it and observe the error message.
3. How is the function structured? Takes channel number and raw ADC count, returns calibrated float value.
4. Gotchas: The function takes a `const float *` pointer to the table — match the const-ness. Print results with 4 decimal places.

**Task:** Write `cal_table.c` with:
- `const float gains[4]` with values around 1.0 (e.g., 1.023f, 0.998f, 1.015f, 0.972f)
- `const float offsets[4]` with small offset corrections (e.g., -2.1f, 0.5f, 1.3f, -0.8f)
- `float calibrate(uint8_t ch, uint16_t raw, const float *gains, const float *offsets)`
- An intentional modification attempt (`gains[0] = 2.0f`) — comment it out after seeing the error
- `main` that prints a table of raw=1000,2000,3000 for all 4 channels showing calibrated values
- Compile: `gcc -Wall -Wextra -g -std=c2x -o cal_table cal_table.c`

---

### Problem 4: `#define` vs `const` vs `enum` Comparison

**Context:** Choosing the wrong constant mechanism in a driver means the compiler silently accepts bugs that would be caught with the right choice.

**Thought process:**
1. What am I showing? Three ways to define the same set of constants and what each one catches at compile time.
2. The constants: ADC resolution options (6, 8, 10, 12 bit) — same values, three mechanisms.
3. What does each catch? `#define` — nothing, it's text. `const int` — type mismatch on assignment. `enum` — type mismatch, and trying to use an out-of-range value.
4. Test: Write a function that takes an ADC resolution parameter. Try passing `42` with each mechanism. Show what the compiler says.

**Task:** Write `const_compare.c` with:
- `#define` versions: `ADC_RES_12_DEFINE 3`
- `const uint8_t` versions: `ADC_RES_12_CONST`
- `typedef enum { ADC_RES_6=3, ADC_RES_8=2, ADC_RES_10=1, ADC_RES_12=0 } ADC_Res`
- A function `void set_resolution(ADC_Res res)` that prints the resolution
- Call it correctly with all three mechanisms
- Attempt to call with `set_resolution(42)` — note what each mechanism does (with enum you get a warning, with define/const you get nothing)
- Comment in your source which mechanism you'd use for real driver code and why
- Compile: `gcc -Wall -Wextra -g -std=c2x -o const_compare const_compare.c`
