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
- For signed integer types: print both min and max — use `%lld` for both (cast the macro to `long long`)
- For unsigned integer types: min is always 0, print max only — use `%llu` (cast to `unsigned long long`)
- For `float`/`double` and `void *`: print size only — no min/max row needed
- Example row formats:
  - Signed:   `%-16s %2zu bytes   min=%-20lld max=%lld`
  - Unsigned: `%-16s %2zu bytes   max=%llu`
- Compile: `gcc -Wall -Wextra -g -std=c2x -o type_audit type_audit.c`

**Man pages:** `man 3 printf` (`%zu` for `size_t`, `%lld` for signed 64-bit, `%llu` for unsigned 64-bit, length modifiers `l`/`ll`/`hh`), `man 0p stdint.h` (`UINT8_MAX`, `INT32_MIN`, etc.), `man 0p limits.h` (`INT_MAX`, `LONG_MIN`, etc.). Cast macros explicitly — `(long long)INT32_MIN` and `(unsigned long long)UINT32_MAX` — so the format specifier and the value always match.

**Vim workflow:** Long table of near-identical `printf` calls — write one row, `yy` then `p` to duplicate, then `r` on a single character of the type name to flip `int` → `long` or `8` → `16`. When you realize halfway through that you'd rather use `uint32_t` everywhere instead of `unsigned int`, the new mc04 command `:%s/unsigned int/uint32_t/gc` lets you swap interactively with confirmation. `gd` on a `UINT8_MAX` jumps to its declaration in the header (handy when you want to verify what a macro actually expands to).

**GDB workflow:** This is the problem `ptype` was made for. Compile with `-g`, `gdb ./type_audit`, `b main`, `run`. Once stopped, `ptype` any local you stored a limit in — it confirms whether you got the declared type you intended (`int`, `long`, `uint32_t`, etc.). `info locals` dumps everything at once. If you stored sizes into an array, `x/4xw &your_array` examines four 32-bit words of memory at a time so you can see the raw byte layout — useful for confirming `sizeof` results match what's stored.

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

**Man pages:** `man gcc` (search `/-O0`, `/-O2`, `/-S` for what each flag does), `man 1 objdump` (optional — `objdump -d` disassembles a binary if you'd rather inspect machine code than compiler-emitted `.s`).

**Vim workflow:** Two near-identical functions — write `poll_bad`, `yy` the body lines, `p` below, then add `volatile` to the type. After running `gcc -S` and getting `volatile_demo.s`, `:e volatile_demo.s` opens it in the same Vim session — `/poll_bad` to jump to that function's assembly, `/poll_good` for the other, then compare side-by-side mentally. `gd` on a register variable jumps back to its declaration so you can confirm where you put `volatile`.

**GDB workflow:** This problem's interesting at runtime *and* in the assembly. Compile both `-O0` and `-O2` versions. `gdb ./demo_O2` for the optimized one, `b main`, `run`, then try to step through `poll_bad` with `next` — at `-O2` the loop will likely have collapsed and you won't see iterations the way you expect. **`ptype reg_bad`** confirms it's `uint32_t` (without `volatile`); `ptype reg_good` confirms `volatile uint32_t`. The whole point: GDB shows you that the *declared* type carries `volatile` as part of itself — it's not a separate annotation, it's part of the type identity. `x/1xw &reg_bad` reads the raw memory regardless of what the optimizer did to register caching.

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

**Man pages:** `man 3 printf` (`%f` for floats, precision specifier `%.4f` for four decimal places, width specifier `%8.4f` to align), `man 7 ascii` (only if you go fancy with table borders).

**Vim workflow:** Two short `const` arrays at the top, the `calibrate` function below, `main` at the bottom — `gg`/`G` to bounce ends, `]]`/`[[` between functions. `*` on a `gains` use shows you every spot the table is read — handy when verifying you remembered `const`-correctness on every reader. After commenting out the deliberate-modification line, `'.` jumps back to where you last edited so you can quickly compare the error message you got with the line that produced it. If you want to swap `gains` for a longer name like `channel_gains`, `:%s/gains/channel_gains/gc` does it interactively (be careful — also matches `offsets` if there's overlap; the `c` flag lets you say no on the false positives).

**GDB workflow:** Compile with `-g`, `gdb ./cal_table`, `b calibrate`, `run`. The headline command is **`ptype gains`** — it should show `const float *` for the parameter and `const float [4]` for the file-scope array, proving the const-ness made it through. `p gains[0]` reads the value (works fine — const just means *you* can't modify it). `x/4fw gains` examines four floats of memory in float format, showing the calibration table laid out in memory. Useful as a sanity check that the linker put the table where you'd expect (in a real embedded build, in Flash/`.rodata`).

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

**Man pages:** `man 3 printf` (basic format specifiers), `man gcc` (search `/-Wenum-conversion` and `/-Wint-conversion` to understand which warning flags catch which mistakes).

**Vim workflow:** Three parallel constant declarations at the top — write one, `yy`/`p` to duplicate, `r` on the suffix character (`E` → `C` to swap `_DEFINE` to `_CONST`). `*` on the enum tag `ADC_Res` shows every place the type is used — useful to confirm you used the typed enum where you should have. `gd` on `ADC_RES_12` jumps to wherever it was defined (works for the `const` and `enum` versions; `#define`s still appear as text replacements). Mass rename a constant family with `:%s/ADC_RES/ADC_RESOLUTION/gc` if you decide a longer name is clearer.

**GDB workflow:** This problem teaches you what GDB sees in each constant mechanism — and `ptype` is the headline. Compile with `-g`, `gdb ./const_compare`, `b set_resolution`, `run`. **`ptype res`** confirms the parameter type — for the enum case it shows the enum tag and members (a real type), for the int parameter version it shows just `int`. `p res` prints the value; for an enum, GDB also shows the symbolic name (`ADC_RES_12`) alongside the integer — that's the kind of debugger-friendliness `enum` buys you over `#define`. `info args` lists the function parameters with their values at entry. The pattern: GDB *knows* about `enum` and `const` but `#define`s vanish before it ever sees them — you can't `p ADC_RES_12_DEFINE` because by the time GDB exists, that name is gone.
