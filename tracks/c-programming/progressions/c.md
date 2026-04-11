# C Progression

Tracks C language concepts introduced per chapter. Each session builds on the last.
This is the map of what you know so far — reference it when tackling new problems.

---

<!-- New sessions append below this line -->

## Ch. 1 — A Tutorial Introduction

| Concept | One-liner | First used in |
|---------|-----------|---------------|
| `#include` | Pull in library declarations | Every program |
| `main()` | Entry point — where execution starts | Every program |
| `printf` format specifiers | `%d`, `%f`, `%c`, `%s`, `\n`, `\t` | ADC table |
| `int`, `float`, `char`, `long`, `double` | Core types — sizes are machine-dependent | All problems |
| Integer division truncation | `5/9` is `0`, not `0.555...` | ADC table |
| Type promotion | Mixing int/float promotes to float | ADC table |
| `while` loop | Test-then-execute loop | UART echo |
| `for` loop | Compact `while` with init/step | ADC table, power |
| `if` / `else if` / `else` | Branching | Byte classifier |
| `#define` | Preprocessor constant — text replacement, no semicolon | All problems |
| `getchar()` / `putchar()` | Read/write one byte — returns `int` for EOF | UART echo |
| `EOF` | End-of-file marker — an `int`, not a `char` | UART echo |
| Assignment-in-condition | `(c = getchar()) != EOF` | UART echo |
| Arrays | Fixed-size, zero-indexed, no bounds checking | Byte classifier |
| Character arithmetic | `c - '0'` gives digit value | Byte classifier |
| Function definition & prototype | Return type, name, params, body | Power utility |
| Call by value | C copies args — arrays pass by address | Power utility |
| `char` arrays / strings | `'\0'`-terminated, manual length tracking | Longest message |
| External variables | Declared outside functions, file-wide scope | Longest message |

## Session 1 — Getting Started (Modern C Ch 1–2)

| Concept | One-liner | First used in |
|---------|-----------|---------------|
| `size_t` | Unsigned type for sizes and array indices — use instead of `int` for loops | getting-started.c |
| Designated initializers | `[index] = value` — initialize specific array elements, rest default to 0 | getting-started.c |
| `EXIT_SUCCESS` | Portable success return value from `<stdlib.h>` | getting-started.c |
| `[[maybe_unused]]` | C23 attribute — suppress "unused variable" warnings | getting-started.c argv |
| `%zu` format specifier | printf format for `size_t` values | getting-started.c |
| Declaration vs definition | Declaration says what it is; definition creates it (with storage/body) | Program structure |
| Scope (block, file, for-loop) | Where an identifier is visible — blocks nest, for-vars stay in for | getting-started.c |
| Compiler diagnostics | Warnings/errors with line numbers — always compile with `-Wall -Wextra` | bad.c |

## Session mc02 — Control (Modern C Ch 3)

| Concept | One-liner | First used in |
|---------|-----------|---------------|
| `if / else` controlling expression | `0` = false, any nonzero = true — don't compare to `true`/`false` | All problems |
| `bool` / `false` / `true` | Built-in since C23; use `<stdbool.h>` for older targets | ISR flag pattern |
| `for (clause; cond; expr)` | Declare loop var inside `for`; use `size_t` for counts | ADC scan, state machine |
| `while (cond)` | Checks condition first — use for polling loops | I2C timeout, polling |
| `do { } while (cond)` | Body runs at least once; semicolon required | Init retry loops |
| `for (;;)` | Infinite loop — same as `while(true)`, firmware convention | Superloops |
| `break` | Exit innermost loop or switch immediately | Timeout exit, state machine |
| `continue` | Skip rest of loop body, re-evaluate condition | Skip disabled channels |
| `switch / case / default` | Multiple selection on integer; always `break`; always `default` | State machine dispatch |
| Fall-through | Without `break`, execution continues into next `case` — usually a bug | Grouped error handlers |
| `typedef enum` | Named integer constants for states/modes — use in `switch` | All state machines |
| Bitwise AND for flag check | `reg & (1U << N)` extracts a bit — nonzero means set | Register bit decoding |

## Session mc03 — Computations (Modern C Ch 4)

| Concept | One-liner | First used in |
|---------|-----------|---------------|
| Unsigned arithmetic always wraps | `SIZE_MAX + 1 == 0` — defined, never UB | Overflow demo |
| Signed overflow is UB | Compiler may optimize assuming it never happens | Overflow demo |
| `|=` set bits, `&= ~` clear, `^=` toggle, `&` read | The four register operations | gpio_sim |
| `1U << n` for bit masks | Always `U` suffix — `1 << 31` is UB | All register code |
| `&&` / `||` short-circuit | Second operand skipped if result already determined | Safe register checks |
| `?:` ternary | Expression form of if/else — evaluates only chosen branch | size_min |
| Compound assignment `@=` | `reg |= mask` is `reg = reg | mask` | All register code |
| `++i` vs `i++` | Pre vs post increment — same effect in statements | Loop counters |

## Session mc04 — Values and Data (Modern C Ch 5)

| Concept | One-liner | First used in |
|---------|-----------|---------------|
| Abstract state machine | Compiler preserves observable states, may optimize rest | volatile demo |
| `<stdint.h>` fixed-width types | `uint8_t` through `uint64_t` — exact sizes for hardware | type_audit |
| `volatile` | Forces re-read from memory every access — required for peripherals/ISR flags | volatile_demo |
| `const` at file scope | Stored in Flash on embedded — saves RAM | cal_table |
| `constexpr` (C23) | True compile-time constant — value checked at declaration | Named constants |
| Integer promotion | Narrow types promoted to `int` before arithmetic | Accumulator bugs |
| `sizeof` | Returns size in bytes as `size_t` — use `%zu` to print | type_audit |
| Float vs double on STM32 | `float` = hardware FPU; `double` = software emulation, 10× slower | ADC scaling |
| Designated initializers | `[index] = value` for arrays, `.field = value` for structs | All init code |
| `{ }` default initializer (C23) | Zero-initializes any type | Buffer init |
| `#define` vs `const` vs `enum` | Masks/addresses → define; tables → const; states/modes → enum | All driver code |

## Session mc05 — Derived Types (Modern C Ch 6)

| Concept | One-liner | First used in |
|---------|-----------|---------------|
| Arrays are contiguous, not pointers | `sizeof arr / sizeof arr[0]` gives length | DMA buffer |
| Array parameters lose size | Always pass length separately; don't sizeof array params | buf_max |
| `struct` groups different types | Members accessed with `.` (value) or `->` (pointer) | ADC_Config |
| Struct padding | Compiler inserts bytes for alignment — order fields largest-first | sizeof demo |
| `typedef struct` | Avoids writing `struct` keyword everywhere — HAL convention | GPIO_Config |
| Structs passed by value | Function gets a copy — pass by pointer to modify original | sys_update |
| `const` pointer parameter | `const T *p` — function promises not to modify | adc_print_config |
| Arrow notation `->` | Shorthand for `(*ptr).member` — used inside functions taking pointers | All HAL code |
| Union overlays same memory | Access as `uint32_t` word or as named bit-fields | uart_union |
| Bit-fields `: N` | Declare struct members with specific bit widths | UART_SR union |
| Pointers: valid, null, invalid | Always initialize; null = `nullptr`; invalid = UB | Pointer basics |
