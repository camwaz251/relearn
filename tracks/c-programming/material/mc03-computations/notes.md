# Session mc03 — Computations
**Modern C Ch 4 (book pp. 34–43) + Ch 5 §5.7.2–5.7.3 (pp. 66–68) | MES Ch 4 sidebar**

---

## What this chapter covers (Modern C p. 34)

- Performing arithmetic
- Modifying objects
- Working with booleans
- The ternary operator
- Setting the evaluation order

Plus, from Ch 5: bitwise operators and shift operators (the register manipulation toolkit).

---

## 1. Operands and Operators (p. 34)

The book provides three comprehensive operator tables:
- **Table 4.1** — Value operators (arithmetic, bitwise, comparison, logic)
- **Table 4.2** — Object operators (assignment, compound assignment, increment, decrement)
- **Table 4.3** — Type operators (sizeof, alignof, offsetof)

**`size_t` (Takeaway 4.1 #1, p. 34):** represents values in the range `[0, SIZE_MAX]`. It's the type for sizes and array indices. Always use it for loop counters over arrays.

---

## 2. Arithmetic — `+`, `-`, `*`, `/`, `%` (pp. 36–37)

```c
size_t a = 45;
size_t b = 7;
size_t c = (a - b) * 2;   // 76
size_t d = a - b * 2;     // 31 — * binds tighter than -
```

**Unsigned arithmetic is always well defined (Takeaway 4.2.1 #1, p. 36):**
As long as the mathematical result is in `[0, SIZE_MAX]`, the operations `+`, `-`, `*` give the mathematically correct result.

**Division and remainder (Takeaway 4.2.2 #1–#6, pp. 37):**
```c
size_t a = 45, b = 7;
// a == (a/b)*b + (a%b)   always holds for unsigned
// result of / and % is always smaller than operands
// Division by zero is forbidden
```

**Unsigned overflow wraps (Takeaway 4.2.2 #3–#4, p. 37):**
```c
// Arithmetic on size_t computes modulo SIZE_MAX + 1
// SIZE_MAX + 1 is 0, and 0 - 1 is SIZE_MAX
```

**Signed overflow is undefined behaviour** — the compiler can assume it never happens and optimize accordingly. Use unsigned types for register manipulation and counters.

**Embedded angle:** Integer division truncates — `7 / 2` is `3`, not `3.5`. You use this constantly for ADC scaling:
```c
#include <stdint.h>
#include <stdio.h>

// ADC count to millivolts: range 0–4095 maps to 0–3300 mV
uint32_t adc_to_mv(uint16_t raw) {
    return ((uint32_t)raw * 3300U) / 4095U;
}

int main(void) {
    uint16_t samples[] = {0, 1024, 2048, 3072, 4095};
    for (size_t i = 0; i < 5; ++i) {
        printf("ADC %4u -> %4u mV\n", samples[i], adc_to_mv(samples[i]));
    }
    return 0;
}
```
The cast `(uint32_t)raw` forces 32-bit multiplication. Without it, `raw * 3300` is `uint16_t * int` — promoted to `int` (fine on 32-bit platforms, but be explicit).

---

## 3. Operators That Modify Objects (p. 38)

**Assignment** `=` is an operator with a value on the right and an object on the left.

**Compound assignment** — the five arithmetic shortcuts:
```c
reg |= mask;     // reg = reg | mask    (set bits)
reg &= ~mask;    // reg = reg & ~mask   (clear bits)
reg ^= mask;     // reg = reg ^ mask    (toggle bits)
x += 5;          // x = x + 5
x >>= 1;         // x = x >> 1  (divide unsigned by 2)
```

**Operators must have all characters attached (Takeaway 4.3 #1, p. 38):**
```c
i += 7;    // correct
i + = 7;   // SYNTAX ERROR — space between + and =
```

**Increment and decrement** — `++i` is equivalent to `i += 1`:
```c
++i;    // pre-increment: increment, then use new value
i++;    // post-increment: use old value, then increment
```

**Side effects in value expressions are evil (Takeaway 4.3 #2, p. 38).** Never modify more than one object in a statement (Takeaway 4.3 #3).
```c
// DON'T:
a = b = c += ++d;    // confusing, error-prone
// DO:
++d;
c += d;
a = c;
b = c;
```

---

## 4. Boolean Context — Comparisons and Logic (pp. 38–40)

**Comparison operators return `false` or `true` (Takeaway 4.4.1 #1, p. 38):**
```c
size_t c = (a < b) + (a == b) + (a > b);   // always exactly 1
size_t d = (a <= b) + (a >= b) - (a == b);  // always exactly 1
```

**Logic operators `!`, `&&`, `||` return `false` or `true` (Takeaway 4.4.2 #1, p. 39):**

| `a` | `!a` |
|-----|------|
| false | true |
| true | false |

| `a and b` | false | true |
|-----------|-------|------|
| false | false | false |
| true | false | true |

**Short-circuit evaluation (p. 40):**
`&&` and `||` skip evaluating the second operand if the first determines the result:
```c
// This never divides by zero:
if (b != 0 && (a/b) > 1) { ++x; }

// Equivalent to:
if (b) {
    if (a/b > 1) { ++x; }
}
```

**Embedded angle:** Short-circuit is critical for safe register checks:
```c
// Only read data register if RXNE flag says data is available:
if ((USART1->SR & USART_SR_RXNE) && (USART1->DR < 128)) {
    // safe — DR only read when data is actually there
}
```

---

## 5. The Ternary Operator `? :` (p. 40)

```c
size_t size_min(size_t a, size_t b) {
    return (a < b) ? a : b;
}
```

Like `&&` and `||`, the ternary evaluates the condition first, then only the chosen branch.

**`&&`, `||`, `?:`, and `,` evaluate their first operand first (Takeaway 4.6 #1, p. 40).** All other operators evaluate operands in an unspecified order.

---

## 6. Bitwise Operators — The Register Toolkit (Ch 5, pp. 66–68)

The book introduces bitwise operators in Ch 5 §5.7.2 as operations on "bit sets" — unsigned values where each bit represents membership in a set.

**Three bitwise operators on bit sets:**

| Operator | Set operation | C | Example |
|----------|-------------|---|---------|
| `\|` | Union A ∪ B | `A \| B` | Set bits from either |
| `&` | Intersection A ∩ B | `A & B` | Keep only bits in both |
| `^` | Symmetric difference A△B | `A ^ B` | Toggle differing bits |

**Complement** `~A` inverts all bits. The result depends on the type's width.

**From the book (Table 5.6, p. 67)** — with A = 240 (bits 4–7) and B = 287 (bits 0–3, 4, 8):

| Op | Value | Hex | Set meaning |
|----|-------|-----|-------------|
| A | 240 | 0x00F0 | {4, 5, 6, 7} |
| B | 287 | 0x011F | {0, 1, 2, 3, 4, 8} |
| A\|B | 511 | 0x01FF | {0–8} — union |
| A&B | 16 | 0x0010 | {4} — intersection |
| A^B | 495 | 0x01EF | {0–3, 5–8} — symmetric diff |

**Do not confuse `&` with `&&`, or `|` with `||` (p. 68):**
- `&` operates on each bit independently
- `&&` evaluates truth values with short-circuit

**Shift operators (Ch 5 §5.7.3, p. 68):**
- Left shift `A << n` = multiply by 2^n (bits shifted out are lost)
- Right shift `A >> n` = divide by 2^n (for unsigned types)

**The second operand of a shift must be less than the precision (Takeaway 5.7.3 #1, p. 68).**
```c
// Shifting by 32 on a 32-bit type is undefined:
uint32_t bad = 1U << 32;   // UNDEFINED
uint32_t ok  = 1U << 31;   // fine — bit 31
```

**Primary use: specify powers of 2 for bit masks:**
```c
#define FLOCK_MAGPIE  (1U << magpie)
#define FLOCK_RAVEN   (1U << raven)
```

---

## 7. The Four Register Operations — Embedded Core Pattern

Every peripheral register operation is one of these four. This is how you read HAL source code and write bare-metal drivers:

```c
#include <stdint.h>
#include <stdio.h>

volatile uint32_t GPIO_ODR = 0x00000000;

#define PIN_5   (1U << 5)
#define PIN_12  (1U << 12)

// SET a bit (turn pin ON): OR with mask
void gpio_set(volatile uint32_t *reg, uint32_t mask) {
    *reg |= mask;
}

// CLEAR a bit (turn pin OFF): AND with inverted mask
void gpio_clear(volatile uint32_t *reg, uint32_t mask) {
    *reg &= ~mask;
}

// TOGGLE a bit: XOR with mask
void gpio_toggle(volatile uint32_t *reg, uint32_t mask) {
    *reg ^= mask;
}

// READ a bit: AND with mask, check non-zero
int gpio_read(volatile uint32_t *reg, uint32_t mask) {
    return (*reg & mask) != 0;
}

int main(void) {
    printf("ODR: 0x%08X\n", GPIO_ODR);

    gpio_set(&GPIO_ODR, PIN_5);
    printf("Set PIN_5:    0x%08X\n", GPIO_ODR);

    gpio_set(&GPIO_ODR, PIN_12);
    printf("Set PIN_12:   0x%08X\n", GPIO_ODR);

    gpio_toggle(&GPIO_ODR, PIN_5);
    printf("Toggle PIN_5: 0x%08X\n", GPIO_ODR);

    gpio_clear(&GPIO_ODR, PIN_12);
    printf("Clear PIN_12: 0x%08X\n", GPIO_ODR);

    printf("PIN_5 = %d\n", gpio_read(&GPIO_ODR, PIN_5));
    return 0;
}
```
Compile: `gcc -Wall -Wextra -g -std=c2x -o gpio_sim gpio_sim.c`

**Why `1U` not `1`?** `1 << 31` shifts a signed `int` into the sign bit — undefined behaviour. `1U << 31` is unsigned and always safe.

**Read-modify-write hazard:** `|=`, `&=`, `^=` are read-modify-write. On real hardware, an interrupt between the read and write can corrupt state. The STM32F407 GPIO has the BSRR register for atomic set/reset — you'll use it in ms06.

---

## Chapter 4 Summary (from book p. 43)

- Arithmetic operators do math. They operate on values.
- Assignment operators modify objects.
- Comparison operators compare values and return `0` or `1`.
- Function calls and most operators evaluate their operands in a nonspecific order. Only `&&`, `||`, and `?:` impose an ordering on their operands.

---

## MES Ch 4 Sidebar — Datasheet to C Translation

When a datasheet says:
```
USART_SR — Status Register (offset 0x00)
Bit 7: TXE  — Transmit data register empty
Bit 6: TC   — Transmission complete
Bit 5: RXNE — Read data register not empty
Bit 3: ORE  — Overrun error
```

You translate directly to C:
```c
#define USART_SR_TXE   (1U << 7)
#define USART_SR_TC    (1U << 6)
#define USART_SR_RXNE  (1U << 5)
#define USART_SR_ORE   (1U << 3)

// Check if TX ready:
if (USART1->SR & USART_SR_TXE) { /* send data */ }

// Wait for transmission complete:
while (!(USART1->SR & USART_SR_TC)) { }

// Clear overrun error:
USART1->SR &= ~USART_SR_ORE;
```

**Hex mental model** — keep this in your head:

| Hex | Binary | Bit position |
|-----|--------|-------------|
| 0x01 | 0000 0001 | bit 0 |
| 0x02 | 0000 0010 | bit 1 |
| 0x04 | 0000 0100 | bit 2 |
| 0x08 | 0000 1000 | bit 3 |
| 0x10 | 0001 0000 | bit 4 |
| 0x20 | 0010 0000 | bit 5 |
| 0x40 | 0100 0000 | bit 6 |
| 0x80 | 1000 0000 | bit 7 |
| 0xFF | 1111 1111 | bits 0–7 |

This is the full cycle: datasheet bit description → `#define` macro → bitwise operation → register read/write. Every peripheral driver follows this exact pattern.
