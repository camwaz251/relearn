# Session mc04 — Values and Data
**Modern C Ch 5 (book pp. 44–76) | MES Ch 4 sidebar**

---

## What this chapter covers (Modern C p. 44)

- Understanding the abstract state machine
- Working with types and values
- Initializing variables
- Using named constants
- Binary representations of types

---

## 1. The Abstract State Machine (pp. 44–48)

A C program is a machine that manipulates **values** and **data**. The book makes a key distinction:

- **Values** exist abstractly — the number 42 is a mathematical entity
- **Data** is the assembled values of all objects at a given moment
- **State** = the executable + current execution point + data + outside intervention

**C programs primarily reason about values and not about their representation (Takeaway 5 #1, p. 44).** The compiler handles translation between values and their binary form.

**All values are numbers or translate to numbers (Takeaway 5.1.1 #1, p. 46).** Characters, truth values, measures — C treats them all as numbers.

**All values have a type that is statically determined (Takeaway 5.1.2 #1, p. 46).** The type determines what operations are possible and what their results are.

**Optimization (Takeaway 5.1.4 #1, p. 48):** Type determines optimization opportunities. The compiler can reorder or combine operations as long as the observable result is the same (the "as-if" rule, Takeaway 5.1.3 #3).

**Embedded angle:** On an STM32, the compiler aggressively optimizes at `-O2`. Without `volatile`, it may eliminate what looks like essential code. The abstract state machine model explains why — the compiler only preserves *observable* states.

---

## 2. Basic Types (pp. 48–50)

The book lists 18 base types in Table 5.1 (p. 49), organized by class:

| Class | Types |
|-------|-------|
| Unsigned integers | `bool`, `unsigned char`, `unsigned short`, `unsigned` (`unsigned int`), `unsigned long`, `unsigned long long` |
| Signed integers | `char`, `signed char`, `signed short`, `signed` (`int`), `signed long`, `signed long long` |
| Real floating point | `float`, `double`, `long double` |

Six of these are **narrow types** (promoted before arithmetic): `bool`, `unsigned char`, `signed char`, `unsigned short`, `signed short`, `char`.

**Before arithmetic, narrow integers are promoted to `signed int` (Takeaway 5.2 #1, p. 49):**
```c
uint8_t a = 200;
uint8_t b = 100;
// a + b promotes both to int → result is 300 (int)
// assigned back to uint8_t → truncates to 44
uint8_t result = a + b;   // 44
```

**Type choice rules from the book (Takeaways 5.2 #3–#7, p. 50):**
- Use `size_t` for sizes, cardinalities, ordinal numbers
- Use `unsigned` for small quantities that can't be negative
- Use `signed` for small quantities that bear a sign
- Use `double` for floating-point calculations

**Embedded override:** On STM32, use `<stdint.h>` fixed-width types for anything that maps to hardware. The standard types (`int`, `long`) have platform-dependent sizes. `uint32_t` is always exactly 32 bits.

---

## 3. Why `int` Is Not Good Enough on Embedded

The C standard only guarantees `int` is **at least 16 bits**. On an 8-bit AVR, `int` is 16 bits. On a 32-bit Cortex-M4, it's 32 bits. Code that uses bare `int` for register values is not portable.

**The fix: `<stdint.h>` fixed-width types (Ch 5 §5.7.6, p. 72):**

```c
#include <stdint.h>

uint8_t   a;   // exactly 8 bits, unsigned
uint16_t  b;   // exactly 16 bits, unsigned
uint32_t  c;   // exactly 32 bits, unsigned
uint64_t  d;   // exactly 64 bits, unsigned
int8_t    e;   // exactly 8 bits, signed
int32_t   f;   // exactly 32 bits, signed
```

**If the type `uintN_t` is provided, it is an unsigned integer type with exactly N bits of width and precision (Takeaway 5.7.6 #1, p. 72).**

**For any fixed-width type, width `_WIDTH`, minimum `_MIN` (signed only), maximum `_MAX`, and literals `_C` macros are provided (Takeaway 5.7.6 #4, p. 72).**

```c
#include <stdint.h>
#include <stdio.h>

int main(void) {
    printf("uint8_t:  %zu bytes, max = %u\n",    sizeof(uint8_t),  UINT8_MAX);
    printf("uint16_t: %zu bytes, max = %u\n",    sizeof(uint16_t), UINT16_MAX);
    printf("uint32_t: %zu bytes, max = %u\n",    sizeof(uint32_t), UINT32_MAX);
    printf("int32_t:  %zu bytes, range [%d, %d]\n",
           sizeof(int32_t), INT32_MIN, INT32_MAX);
    printf("pointer:  %zu bytes\n", sizeof(void *));
    return 0;
}
```
Compile: `gcc -Wall -Wextra -g -std=c2x -o type_audit type_audit.c`

**Rule:** For any variable that maps to hardware (register value, buffer, counter, bitmask), use `<stdint.h>` types. Use `int` only for general-purpose local variables where size doesn't matter.

---

## 4. `volatile` — The Most Important Embedded Keyword

Without `volatile`, the compiler can optimize away reads and writes it considers redundant. This is the abstract state machine in action — if a value isn't *observable*, the compiler may eliminate it.

```c
// Without volatile — compiler may cache in register
uint32_t *status_reg = (uint32_t *)0x40013800;
while (*status_reg & 0x80) { }   // may become infinite loop at -O2

// With volatile — compiler re-reads from memory every iteration
volatile uint32_t *status_reg = (volatile uint32_t *)0x40013800;
while (*status_reg & 0x80) { }   // reads hardware every time
```

**Demo — see the difference:**
```c
#include <stdint.h>
#include <stdio.h>

uint32_t          fake_reg_bad  = 1;
volatile uint32_t fake_reg_good = 1;

void poll_bad(void)  { while (fake_reg_bad)  { } }
void poll_good(void) { while (fake_reg_good) { } }
```

Compile with `-O2 -S` and look at the assembly. The non-volatile version will likely become an infinite loop (load once, test forever). The volatile version will load from memory each iteration.

**Rule:** Every variable modified outside the current thread of execution — peripheral registers, ISR-shared flags, DMA buffers — must be `volatile`.

---

## 5. `const` — Read-Only Data in Flash (pp. 59–60)

On embedded, `const` variables at file scope are stored in **Flash**, not RAM. RAM is precious (STM32F407: 192 KB). Flash is larger (1 MB). Put lookup tables and calibration data in Flash.

**An object of `const`-qualified type is read-only (Takeaway 5.6.1 #1, p. 60):**
```c
const float adc_cal[4] = { 1.023f, 0.998f, 1.015f, 0.972f };
const float offsets[4]  = { -2.1f,  0.5f,  1.3f, -0.8f };

float calibrate(uint8_t ch, uint16_t raw,
                const float *gains, const float *offsets) {
    return (float)raw * gains[ch] + offsets[ch];
}
```

**`const` does NOT mean compile-time constant in C** (unlike `constexpr` in C++). It means "this variable should not be modified after initialization." The compiler will error if you try.

**C23 `constexpr` (Takeaway 5.6.5 #1, p. 65):** C23 introduces `constexpr` for true compile-time constants. The initializer must fit exactly:
```c
constexpr double pi = 3.141'592'653'589'793'238'46;
constexpr unsigned pi_flat = 3.14;  // ERROR — loses precision
```

---

## 6. Specifying Values — Literals (pp. 51–54)

| Literal form | Type | Example |
|-------------|------|---------|
| `123` | `signed int` (first fit) | Decimal integer |
| `077` | Octal (avoid) | Rarely used |
| `0xBEAF` | Hex — unsigned if needed | Register values |
| `0b1010` | Binary (C23) | Bit patterns |
| `1.7E-13` | `double` | Floating point |
| `0.2F` | `float` | Single-precision |
| `'a'` | Integer character literal | ASCII code |
| `"hello"` | String literal | Char array + `\0` |

**Numerical literals are never negative (Takeaway 5.3 #2, p. 52).** `-34` is the negation operator applied to `34`.

**Decimal integer literals are signed (Takeaway 5.3 #3, p. 52).** Hex/octal/binary can be unsigned if the value doesn't fit in signed.

**Don't use binary, octal, or hex literals for negative values (Takeaway 5.3 #6, p. 53).** Use decimal for negative values (Takeaway 5.3 #7).

**Suffixes (Table 5.4, p. 53):**
| Suffix | Force type |
|--------|-----------|
| `U` or `u` | unsigned |
| `L` or `l` | at least `long` |
| `LL` or `ll` | `long long` |

Always use `U` suffix for bit masks: `1U << 5`, not `1 << 5`.

---

## 7. Initializers (pp. 57–58)

**All variables should be initialized (Takeaway 5.5 #1, p. 57).**

**Use designated initializers for all aggregate data types (Takeaway 5.5 #2, p. 58):**
```c
double A[] = { 7.8, };                       // 1 element
double B[3] = { 2 * A[0], 7, 33, };         // 3 elements
double C[] = { [0] = 6, [3] = 1, };         // 4 elements, rest 0
```

**`{ }` is a valid initializer for all objects (Takeaway 5.5 #3, p. 58).** This is new in C23 (previously `{0}`):
```c
uint32_t reg = { };     // initialized to 0
double arr[16] = { };   // all zeros
```

---

## 8. Named Constants — `#define` vs `const` vs `enum` (pp. 59–63)

**All constants with a particular meaning must be named (Takeaway 5.6 #1, p. 59).**

### When to use what (embedded practical guide):

```c
// #define — no type, no scope, preprocessor text substitution
// Use for: bit masks, register addresses, hardware constants
#define GPIOA_BASE   0x40020000U
#define PIN_5        (1U << 5)
#define SYSCLK_HZ    168000000U

// const — typed, scoped, read-only
// Use for: calibration tables, lookup tables, string constants
const uint16_t pwm_table[256] = { /* ... */ };
const char *device_name = "STM32F407-DISC1";

// enum — named integer constants, compiler checks usage
// Use for: states, modes, error codes, peripheral config options
typedef enum {
    ADC_RES_12BIT = 0,
    ADC_RES_10BIT = 1,
    ADC_RES_8BIT  = 2,
    ADC_RES_6BIT  = 3,
} ADC_Resolution;
```

**Macros (Takeaway 5.6.3 #1, p. 63):** Macro names are in ALL CAPS.

**Enumeration constants have either an explicit or positional value (Takeaway 5.6.2 #1, p. 61).** Values start from 0 unless explicitly assigned.

---

## 9. Binary Representations (pp. 65–71)

### Unsigned integers (§5.7.1, p. 66)

Binary digits b₀, b₁, ..., b_{p-1} where p is the precision. Value = Σ bᵢ × 2ⁱ.

**The maximum value of any integer type is 2^p − 1 (Takeaway 5.7.1 #1, p. 66).**

### Signed integers — two's complement (§5.7.5, p. 69)

C23 mandates two's complement. The sign bit is the highest-order bit: 0 = positive, 1 = negative.

**Signed overflow is undefined (Takeaway 5.7.5 #2–#3, p. 70):**
```c
for (unsigned i = 1; i; ++i) do_something();  // wraps to 0 eventually — defined
for (signed   i = 1; i; ++i) do_something();  // undefined — compiler may make infinite
```

**Use unsigned types for bit operations (Takeaway 5.7.5 #8, p. 71).**

### Floating point (§5.7.8, p. 74)

**Floating-point operations are neither associative, commutative, nor distributive (Takeaway 5.7.8 #1, p. 74).** `(a + b) + c` may differ from `a + (b + c)`.

**Never compare floating-point values for equality (Takeaway 5.7.8 #2, p. 75).**

**Embedded angle — float on STM32F407:**
```c
float  x = 3.14f;    // 32-bit — hardware FPU handles this
double y = 3.14;     // 64-bit — NO FPU support, software emulation, ~10× slower
```
Rule: Use `float` freely (hardware FPU). Avoid `double` in time-critical code. Avoid float in ISRs (FPU context save adds latency).

---

## 10. `sizeof` and Struct Padding (p. 48, referenced for later sessions)

`sizeof` returns the size of a type or object in bytes as a `size_t`:
```c
printf("uint8_t:  %zu\n", sizeof(uint8_t));    // 1
printf("uint16_t: %zu\n", sizeof(uint16_t));   // 2
printf("uint32_t: %zu\n", sizeof(uint32_t));   // 4
printf("float:    %zu\n", sizeof(float));       // 4
printf("double:   %zu\n", sizeof(double));      // 8
printf("pointer:  %zu\n", sizeof(void *));      // 8 on 64-bit, 4 on ARM
```

Struct padding is covered in mc05 (Derived Types).

---

## Chapter Summary (from book p. 76)

- C programs run in an abstract state machine mostly independent of the platform
- All basic types are kinds of numbers, but not all can be used directly for arithmetic
- Values have a type and a binary representation
- Types of values are implicitly converted to fit where they are used
- Variables must be explicitly initialized before first use
- Integer computations give exact values as long as there is no overflow
- Floating-point computations only give approximated results

---

## MES Ch 4 Sidebar — Reading Datasheets for Register Values

When a datasheet says:
```
ADC_CR1 — ADC control register 1 (offset 0x04)
Bits 25:24 RES[1:0]: Resolution
  00: 12-bit
  01: 10-bit
  10: 8-bit
  11: 6-bit
Bit 8 SCAN: Scan mode
  0: disabled
  1: enabled
```

You translate directly:
```c
#define ADC_CR1_RES_12BIT   (0x00U << 24)
#define ADC_CR1_RES_10BIT   (0x01U << 24)
#define ADC_CR1_RES_8BIT    (0x02U << 24)
#define ADC_CR1_RES_6BIT    (0x03U << 24)
#define ADC_CR1_SCAN_EN     (1U << 8)

// Set 12-bit resolution and enable scan mode:
ADC1->CR1 |= ADC_CR1_RES_12BIT | ADC_CR1_SCAN_EN;
```

This is the full cycle: datasheet bit field → `#define` macro → bitwise operation → register write.
