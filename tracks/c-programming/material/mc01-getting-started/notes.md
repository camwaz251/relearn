# Session 1 — Getting Started + Program Structure
**Modern C Ch 1–2 | MES Ch 1 Sidebar**

---

## 1. C is Not C++ (and Not K&R C Either)

Modern C's first takeaway:

> **Takeaway #1:** *C and C++ are different: don't mix them, and don't mix them up.*

You know C++. That's useful background, but C is its own language — not a subset of C++. They diverged from a common ancestor 30+ years ago and have evolved separately since.

### C has evolved: the standards

| Standard | Year | Key additions |
|----------|------|---------------|
| K&R C | 1978 | The original book |
| C89/C90 | 1989 | First ISO standard, function prototypes |
| C99 | 1999 | `//` comments, `for`-loop declarations, `<stdint.h>`, `<stdbool.h>` |
| C11 | 2011 | `_Static_assert`, `_Generic`, threads, atomics |
| C17 | 2018 | Bug fixes to C11 (no new features) |
| C23 | 2024 | `[[attributes]]`, `constexpr`, `#embed`, `typeof`, `nullptr` |

This course teaches **C23** (using `-std=c2x` flag until compilers catch up). Your K&R ch1 session used plain C — now we upgrade.

### Things Modern C has that K&R didn't
- **Designated initializers:** `[0] = 9.0, [4] = 3.E+25` — assign specific array indices
- **`size_t`** for indexing — not `int`
- **`bool`** as a first-class type (from `<stdbool.h>`, built-in in C23)
- **`_Static_assert`** — compile-time checks
- **`<stdint.h>`** — exact-width types like `uint32_t`
- **`[[maybe_unused]]`** — C23 attribute to suppress warnings
- **`EXIT_SUCCESS`** from `<stdlib.h>` — portable return value

### Things C doesn't have vs C++
No classes. No references (`&`). No function overloading. No templates. No exceptions. No namespaces. No `new`/`delete`. No RAII.

**Embedded angle:** C dominates embedded *because* of these missing features. No hidden allocations from constructors. No vtable indirection. No exception unwinding overhead. Every byte of RAM and every CPU cycle is accounted for. When your microcontroller has 16 KB of flash and 4 KB of RAM, you need that predictability.

---

## 2. Your First Modern C Program

This is Listing 1.1 from Modern C — the book's `getting-started.c`. Type this into Vim exactly.

```c
/* This may look like nonsense, but really is -*- mode: C -*- */
#include <stdlib.h>
#include <stdio.h>

/* The main thing that this program does. */
int main(int argc, [[maybe_unused]] char* argv[argc+1]) {
    // Declarations
    double A[5] = {
        [0] = 9.0,
        [1] = 2.9,
        [4] = 3.E+25,
        [3] = .00007,
    };

    // Doing some work
    for (size_t i = 0; i < 5; ++i) {
        printf("element %zu is %g, \tits square is %g\n",
               i,
               A[i],
               A[i]*A[i]);
    }

    return EXIT_SUCCESS;
}
```

### What's new here vs your K&R ch1 code

**`#include <stdlib.h>`** — needed for `EXIT_SUCCESS`. In K&R style you'd just `return 0;`. `EXIT_SUCCESS` is portable — on some platforms success might not be 0.

**`int main(int argc, [[maybe_unused]] char* argv[argc+1])`** — Let's break this apart:
- `int main(...)` — main *must* return `int`. The book's bad.c uses `void main()` to show what happens when you get this wrong.
- `[[maybe_unused]]` — a C23 *attribute*. Tells the compiler "I know `argv` is unused, don't warn me." Placed in double square brackets. This is new in C23 — older C had no standard way to do this (GCC used `__attribute__((unused))`).
- `char* argv[argc+1]` — variable-length array (VLA) declaration for argv. The `argc+1` size includes the null terminator. This is valid Modern C (VLAs in parameter lists are fine).

**Designated initializers:**
```c
double A[5] = {
    [0] = 9.0,
    [1] = 2.9,
    [4] = 3.E+25,
    [3] = .00007,
};
```
The `[index] = value` syntax lets you initialize specific array positions in any order. Elements you skip default to `0.0`. Here, `A[2]` is never mentioned, so it's `0.0`. The trailing comma after the last element is legal and good practice — makes adding elements easier.

Compare to K&R style: `double A[5] = {9.0, 2.9, 0.0, .00007, 3.E+25};` — you'd have to count positions manually and couldn't reorder.

**`size_t i`** — the correct type for array indexing and sizes. It's an unsigned integer type from `<stdlib.h>` (also `<stddef.h>`). On a 64-bit system it's typically `unsigned long` (8 bytes). On a 32-bit embedded target it might be 4 bytes. Using `int` for loop counters over arrays is technically wrong because `int` can be negative and might be too small.

**`%zu`** — the format specifier for `size_t`. Not `%d` (that's for `int`), not `%u` (that's for `unsigned int`). Using the wrong specifier is undefined behavior.

**`%g`** — format specifier for `double` that chooses the shorter of `%f` and `%e` notation. Prints `9` instead of `9.000000` and `3e+25` instead of a wall of digits.

**`return EXIT_SUCCESS;`** — instead of `return 0;`. Both work, but `EXIT_SUCCESS` is self-documenting and portable.

### Expected output

```
element 0 is 9,        its square is 81
element 1 is 2.9,      its square is 8.41
element 2 is 0,        its square is 0
element 3 is 7e-05,    its square is 4.9e-09
element 4 is 3e+25,    its square is 9e+50
```

Notice element 2 is `0` — we never initialized it. The designated initializer for `[3]` and `[4]` didn't fill `[2]`.

---

## 3. Compiling and Running

### The command

```bash
gcc10-gcc -Wall -Wextra -g -std=c2x -o getting-started getting-started.c -lm
```

**Note:** We use `gcc10-gcc` (GCC 10.5) instead of the system `gcc` (7.3). GCC 7 doesn't support `-std=c2x` or C23 features like `[[maybe_unused]]`. You installed GCC 10 via `sudo yum install -y gcc10`.

| Flag | Purpose |
|------|---------|
| `-Wall` | Enable most common warnings |
| `-Wextra` | Enable additional warnings beyond `-Wall` |
| `-g` | Include debug symbols (for GDB) |
| `-std=c2x` | Use C23 standard (the "c2x" name predates the final standard) |
| `-o getting-started` | Name the output executable |
| `-lm` | Link the math library (needed for `math.h` functions; good habit) |

You already know `-Wall -Wextra -g` from your K&R ch1 session. The new flag is **`-std=c2x`** which enables C23 features like `[[maybe_unused]]`. Without it, gcc uses its default standard and may warn about or reject C23 syntax.

### The bad program (Listing 1.2)

Now type this into `bad.c` — it has **three deliberate flaws**:

```c
/* This may look like nonsense, but really is -*- mode: C -*- */

/* The main thing that this program does. */
void main() {
    // Declarations
    int i;
    double A[5] = {
        9.0,
        2.9,
        3.E+25,
        .00007,
    };

    // Doing some work
    for (i = 0; i < 5; ++i) {
        printf("element %d is %g, \tits square is %g\n",
               i,
               A[i],
               A[i]*A[i]);
    }

    return 0;
}
```

Compile it and **read the diagnostics carefully**:

```bash
gcc10-gcc -Wall -Wextra -g -std=c2x -o bad bad.c -lm
```

You'll see warnings like:

1. **`-Wmain`: return type of 'main' is not 'int'`** — `void main()` is wrong. The C standard requires `int main(...)`. Some compilers (especially embedded ones) accept `void main()` but it's non-conforming.

2. **`-Wimplicit-function-declaration`: implicit declaration of function 'printf'`** — Missing `#include <stdio.h>`. Without it, the compiler doesn't know what `printf` is. It guesses — and guesses wrong.

3. **`-Wreturn-type`: 'return' with a value, in function returning void`** — `return 0;` doesn't make sense when main returns `void`. The compiler catches the contradiction.

**The three differences from getting-started.c:**
1. Missing `#include <stdio.h>` and `#include <stdlib.h>`
2. `void main()` instead of `int main(int argc, ...)`
3. No designated initializers, `int i` instead of `size_t i`, `%d` instead of `%zu`

The book's takeaway:

> **Takeaway 1.2 #3:** *A C program should compile cleanly without warnings.*

On embedded, this matters even more. Your cross-compiler might be stricter or more lenient than your desktop gcc. Code that "works with warnings" on your PC might fail to compile — or worse, silently misbehave — on the target.

---

## 4. Program Structure: Declarations, Definitions, Statements

Modern C Ch 2 introduces the three semantic categories of a C program. This is the backbone of understanding how C code is organized.

### Declarations

A **declaration** tells the compiler what an identifier is — its type and name — without necessarily creating it.

```c
int main(int, char*[]);      // declares main as a function returning int
int argc;                     // declares argc as an int
double A[5];                  // declares A as an array of 5 doubles
size_t i;                     // declares i as a size_t
```

Key identifiers in getting-started.c and where their declarations come from:

| Identifier | Type | Declared by |
|------------|------|-------------|
| `main` | function returning `int` | you write it |
| `argc`, `argv` | `int`, `char*[]` | parameters of main |
| `A` | `double[5]` | your code |
| `i` | `size_t` | your code |
| `printf` | function | `<stdio.h>` |
| `size_t` | type alias | `<stdlib.h>` / `<stddef.h>` |
| `EXIT_SUCCESS` | constant | `<stdlib.h>` |

> **Takeaway 2.2 #1:** *All identifiers in a program have to be declared.*

This is why missing `#include <stdio.h>` causes "implicit declaration" — the compiler has no declaration for `printf`.

### Definitions

A **definition** provides the actual object or function body. A declaration with an initializer is a definition:

```c
size_t i = 0;                 // declaration + initializer = definition
double A[5] = { [0] = 9.0 }; // definition with designated initializer
```

For functions, the definition includes the body:

```c
int main(int argc, [[maybe_unused]] char* argv[argc+1]) {
    // ... body ...
}
```

> **Takeaway 2.3 #1:** *Declarations specify identifiers, whereas definitions specify objects.*

> **Takeaway 2.3 #5:** *Each object or function must have exactly one definition.*

**Embedded angle:** In firmware, you declare interfaces in **header files** (`.h`) and define implementations in **source files** (`.c`). A driver header might declare `void uart_init(uint32_t baud);` and the source file defines the function body. This separation is the foundation of modular embedded design — you'll dig into this in Session 9.

### Statements

**Statements** are instructions — they tell the compiler what to do:

- **Iterations:** `for (size_t i = 0; i < 5; ++i) { ... }` — repeat a block
- **Function calls:** `printf(...)` — delegate work to another function
- **Returns:** `return EXIT_SUCCESS;` — exit the function with a value

The `for` statement has four parts:
1. **Initialization:** `size_t i = 0` — runs once before the loop
2. **Condition:** `i < 5` — checked before each iteration
3. **Increment:** `++i` — runs after each iteration
4. **Body:** `{ ... }` — the code that repeats

> **Takeaway 2.4.1 #2:** *The loop variable should be defined in the initial part of a `for`.*

Don't pre-declare `int i;` at the top of the function like bad.c does. Define it in the `for` — this limits its scope and makes the code clearer.

---

## 5. Scope and Blocks

**Scope** determines where an identifier is visible. Modern C has three levels:

### File scope (globals)
Identifiers declared outside any `{ }` block. Visible from their declaration to the end of the file. `main` itself has file scope — any code below its declaration can reference it.

### Block scope
Identifiers declared inside `{ }`. Visible only within that block. The array `A` and everything inside `main`'s braces has block scope.

### For-loop scope
The loop variable `i` in `for (size_t i = 0; ...)` is scoped to the `for` construct — both the `(...)` part and the `{ }` body. Once the loop ends, `i` is gone.

```c
int main(int argc, [[maybe_unused]] char* argv[argc+1]) {
    // argc, argv visible here (block scope of main)
    double A[5] = { ... };  // A visible from here to end of main

    for (size_t i = 0; i < 5; ++i) {
        // i visible here (for-loop scope)
        printf("element %zu is %g\n", i, A[i]);  // A still visible
    }
    // i is NOT visible here — it went out of scope

    return EXIT_SUCCESS;
}
```

Blocks **nest**: main's block contains the for-loop's block. The inner block can see identifiers from the outer block (`A` is visible inside the loop), but not vice versa.

> **Takeaway 2.2 #3:** *Declarations are bound to the scope in which they appear.*

**Embedded angle:** Scope discipline prevents name collisions across translation units. When three engineers each write a driver module (UART, SPI, I2C), proper scoping ensures their internal variables don't clash. File-scope `static` variables (covered later) are the C equivalent of "private" — visible only in their source file.

---

## 6. Embedded Sidebar: What Is an Embedded System? (MES Ch 1)

### Definition

> *An embedded system is a computerized system that is purpose-built for its application.*

Your phone, your car's engine controller, a thermostat, a pacemaker, a satellite — all embedded systems. They're not general-purpose computers. They do one job (or a small set of jobs) and they do it under constraints.

### How it differs from desktop/server development

| Desktop | Embedded |
|---------|----------|
| Compile and run on same machine | **Cross-compile** on PC, run on target |
| GDB runs locally | **Cross-debugger** via JTAG/SWD interface |
| Gigabytes of RAM | Kilobytes of RAM (4 KB – 256 KB typical) |
| Disk-backed virtual memory | No disk. No virtual memory. |
| OS handles scheduling, memory | Often **bare metal** — no OS at all |
| Crash → restart the program | Crash → device is bricked in the field |
| `printf` always available | `printf` may not exist or changes timing |

### The five resource constraints

Every embedded design decision traces back to these:

1. **RAM** — working memory for variables, stack, heap. A Cortex-M0 might have 8 KB total. Your desktop has 16 GB.
2. **ROM/Flash** — where your compiled code lives. Code space is fixed at manufacturing. A typical MCU: 64 KB – 1 MB.
3. **Processor cycles** — CPU speed. Some MCUs run at 8 MHz (not GHz). Every wasted instruction matters.
4. **Power** — battery-powered devices must minimize energy. Deep sleep modes, clock gating, peripheral shutdown.
5. **Peripherals** — GPIO pins, UART ports, SPI buses, ADC channels. You get what the chip has. No adding more.

These constraints are **tradeable**: you can spend code space to save cycles (lookup tables vs computation), or spend cycles to save RAM (recompute vs cache). Knowing the constraints shapes every design decision.

### The cross-compilation toolchain

```
Source.c  -->  [Cross-compiler + linker]  -->  Image file
                    (on your PC)                   |
                                                   v
              [Cross-debugger] <--- JTAG/SWD ---> [Target processor]
                    (on your PC)                   (your embedded board)
```

You never run `gcc` targeting your own machine when doing embedded work. Instead: `arm-none-eabi-gcc` targets ARM Cortex-M. The output is a `.bin` or `.elf` file that gets flashed onto the microcontroller.

### Principles from MES Ch 1

- **Modularity:** Separate functionality into subsystems. A sensor module shouldn't know about the display module.
- **Encapsulation:** Hide internal data behind interfaces. Other modules call `sensor_read()`, they don't touch the sensor's internal registers directly.
- **Test early:** Bugs caught early are cheap. Bugs found in the field (a deployed satellite, an implanted pacemaker) may be unfixable.
- **Document intent, not mechanics:** Comments should say *what the code does*, not restate the code. `t++; // increment t` is useless. `t++; // advance to next sample window` tells you why.

### What happens before `main()`?

On your desktop, the OS loads your program and calls `main()`. On embedded, there's a whole startup sequence first:

1. Power-on reset — processor starts at the **reset vector** (an address in the vector table)
2. **Startup code** (`crt0.s` or `startup.s`) runs — written in assembly
3. Initializes the **stack pointer** (SP)
4. Copies initialized data from flash to RAM (`.data` section)
5. Zeros the BSS section (uninitialized globals)
6. Optionally initializes hardware (clocks, critical peripherals)
7. *Then* calls `main()`

This is invisible on your desktop but critical on embedded. You'll see this in detail when we reach Phase 4 (on-hardware with QEMU). For now, just know: `main()` is not the beginning. Something had to set up the world first.

### Why C for embedded?

- Maps directly to hardware — no hidden runtime costs
- Predictable memory layout — you know exactly where every variable lives
- No garbage collector — you control allocation and deallocation
- Compiles to efficient machine code — critical when you have 64 KB of flash
- Runs on every architecture — ARM, RISC-V, AVR, PIC, MSP430, x86
- Mature toolchains — `arm-none-eabi-gcc` has decades of optimization work

C++ is gaining ground in embedded (especially on larger Cortex-M4/M7 chips), but C remains the default for resource-constrained targets. The language you're learning here is the lingua franca of firmware.
