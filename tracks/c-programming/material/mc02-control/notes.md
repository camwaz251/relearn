# Session mc02 — Control
**Modern C Ch 3 (book pp. 23–33) | MES Ch 5 intro sidebar**

---

## What this chapter covers (Modern C p. 23)

- Conditional execution with `if`
- Iterating over domains (`for`, `while`, `do`)
- Making multiple selections (`switch`)

C has five conditional control statements: `if`, `for`, `do`, `while`, and `switch`.
`if` introduces conditional execution depending on a Boolean expression.
`for`, `do`, and `while` are forms of iteration.
`switch` is a multiple selection based on an integer value.

---

## 1. `if` — Conditional Execution (pp. 23–26)

```c
if (i > 25) {
    j = i - 25;
}
```

General form with `else`:
```c
if (condition) secondary-block0
else secondary-block1
```

The controlling expression (`condition`) determines which secondary block runs. If no `else` is present, nothing happens when condition is false.

**Truth values (Takeaway 3.1 #1–#2, p. 24):**
- `0` represents logical **false**
- Any value different from `0` represents logical **true**

```c
// These three are equivalent:
if (i != 0) { ... }
if (i)      { ... }   // preferred style in C
if (!!i)    { ... }   // double negation — forces 0 or 1
```

**Don't compare to 0, false, or true (Takeaway 3.1 #3, p. 26):**
```c
// Redundant and wrong idiom:
if ((b != false) == true) { ... }

// Correct:
if (b)  { ... }
if (!b) { ... }
```

**All scalars have a truth value (Takeaway 3.1 #4, p. 26):**
`size_t`, `bool`, `int`, `unsigned`, and pointer types all work as conditions.

**`bool` type:** `false` is value `0`, `true` is value `1`. Since C23 (`-std=c2x`) these are keywords with no header needed. For C99/C11 you need `#include <stdbool.h>`.

**Embedded angle:** HAL status codes use this pattern directly:
```c
#include <stdint.h>
#include <stdio.h>

// Simulated HAL return — 0 = OK, nonzero = error
typedef enum { HAL_OK = 0, HAL_ERROR = 1, HAL_TIMEOUT = 2 } HAL_Status;

HAL_Status uart_transmit(uint8_t *buf, size_t len) {
    // ... hardware transmit ...
    return HAL_OK;
}

int main(void) {
    uint8_t msg[] = "hello\n";
    HAL_Status s = uart_transmit(msg, 6);
    if (s != HAL_OK) {
        printf("UART error: %d\n", (int)s);
    }
    return 0;
}
```
The `if (s != HAL_OK)` pattern — comparing against the zero-valued success code — is in every HAL function call in production STM32 firmware.

---

## 2. Iterations — `for`, `while`, `do` (pp. 26–29)

### `for` loop (p. 26)

General form from the book:
```c
for (clause1; condition2; expression3) secondary-block
```

- `clause1`: initializes the iteration variable. **Best practice: declare the variable here** so its scope is limited to the loop.
- `condition2`: checked before each iteration; loop exits when false.
- `expression3`: update, executed at the end of each iteration.

Examples from the book (p. 27):
```c
// Count down from 10 to 1:
for (size_t i = 10; i; --i) { something(i); }

// Compute upper_bound once, capture in stop:
for (size_t i = 0, stop = upper_bound(); i < stop; ++i) {
    something_else(i);
}
```

**Prefer `size_t` for loop counters when iterating over arrays or counts.** Use `int` only for general-purpose counters where the value can be negative.

**Embedded angle — scanning ADC channels:**
```c
#include <stdint.h>
#include <stdio.h>

#define NUM_CHANNELS 16u

uint16_t adc_buf[NUM_CHANNELS] = {
    [0] = 1024, [1] = 3950, [7] = 4095, [15] = 80,
};

int main(void) {
    for (size_t ch = 0; ch < NUM_CHANNELS; ++ch) {
        printf("ADC[%2zu] = %4u (%.3f V)\n",
               ch, adc_buf[ch],
               adc_buf[ch] * 3.3f / 4095.0f);
    }
    return 0;
}
```
Compile: `gcc -Wall -Wextra -g -std=c2x -o adc_scan adc_scan.c`

---

### `while` loop (p. 27)

```c
while (condition) secondary-block
```

Checks condition first — if false immediately, body never runs. Use `while` for polling: waiting until a hardware flag changes.

**Heron's approximation example from the book (p. 27):**
```c
#include <tgmath.h>

constexpr double eps = 1E-9;
double a = 34.0;
double x = 0.5;
while (fabs(1.0 - a*x) >= eps) {
    x *= (2.0 - a*x);       // converges to 1/a
}
```

**Embedded polling pattern:**
```c
// Poll UART transmit-complete flag (STM32 pattern):
// while (!(USART2->SR & USART_SR_TC)) { }
```

---

### `do`...`while` loop (p. 27)

```c
do {
    secondary-block
} while (condition);    // NOTE: semicolon required here
```

Body runs **at least once**, then condition is checked. The do-while needs a semicolon after the closing `while(condition)` — this is a syntactic difference from `while` and `for`. `while(true)` + `break` is equivalent and sometimes clearer.

---

### `break` and `continue` (p. 28)

**`break`** stops the loop without re-evaluating the condition:
```c
while (true) {
    double prod = a * x;
    if (fabs(1.0 - prod) < eps) {
        break;               // done — exit loop
    }
    x *= (2.0 - prod);
}
```

**`for (;;)` is equivalent to `while (true)` (p. 28):**
```c
for (;;) {
    // infinite loop — C tradition, used in firmware superloops
}
```
This is historical convention. In firmware, `while (true)` is more readable; both are correct.

**`continue`** skips the rest of the body and re-evaluates the condition:
```c
for (size_t i = 0; i < max_iterations; ++i) {
    if (x > 1.0) {
        x = 1.0 / x;
        continue;       // restart loop — skip Heron step
    }
    double prod = a * x;
    if (fabs(1.0 - prod) < eps) { break; }
    x *= (2.0 - prod);
}
```

**Embedded angle — polling with timeout:**
```c
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define I2C_SR_BUSY     (1U << 1)
#define TIMEOUT_CYCLES  1000u

int main(void) {
    uint32_t i2c_sr = I2C_SR_BUSY;
    bool timeout = false;

    for (uint32_t t = 0; t < TIMEOUT_CYCLES; ++t) {
        if (!(i2c_sr & I2C_SR_BUSY)) break;   // bus free — done
        if (t == 50) i2c_sr &= ~I2C_SR_BUSY;  // simulate hardware clearing it
        if (t == TIMEOUT_CYCLES - 1) timeout = true;
    }

    if (timeout) {
        printf("I2C bus timeout — hardware not responding\n");
    } else {
        printf("I2C bus free\n");
    }
    return 0;
}
```
Compile: `gcc -Wall -Wextra -g -std=c2x -o i2c_poll i2c_poll.c`

This `for` + `break` pattern for polling with timeout appears in every HAL driver's blocking mode.

---

## 3. `switch` — Multiple Selection (pp. 30–31)

When `if-else` chains test the same variable against many values, `switch` is cleaner:

```c
// Long if-else:
if (arg == 'm')      puts("magpie");
else if (arg == 'r') puts("raven");
else if (arg == 'j') puts("jay");
else                 puts("unknown");

// With switch (from book p. 30):
switch (arg) {
    case 'm': puts("magpie"); break;
    case 'r': puts("raven");  break;
    case 'j': puts("jay");    break;
    default:  puts("unknown");
}
```

**Rules (Takeaways 3.3 #1–#3, p. 31):**
- `case` values must be **integer constant expressions** — literal integers, enum values, `#define` macros (not variables)
- `case` values must be **unique** within a `switch`
- `case` labels must not jump beyond a variable definition (skipping an initializer is a bug)

**Fall-through (book p. 31):**
Without `break`, execution continues into the next `case`. The book shows this as a "triangle" pattern:
```c
switch (count) {
    default: puts("++++.....++++");
    case 4:  puts("++++");
    case 3:  puts("+++");
    case 2:  puts("++");
    case 1:  puts("+");
    case 0:
}
```
When `count == 3`: jumps to `case 3`, then falls through cases 2, 1, 0 — prints three lines.

In practice: **always add `break`** unless fall-through is intentional and commented.

**Embedded angle — state machine:**
```c
#include <stdint.h>
#include <stdio.h>

typedef enum {
    STATE_IDLE       = 0,
    STATE_SAMPLING   = 1,
    STATE_PROCESSING = 2,
    STATE_TX         = 3,
    STATE_ERROR      = 4,
} SysState;

SysState run_one_tick(SysState current, uint32_t tick) {
    switch (current) {
        case STATE_IDLE:
            printf("tick %u: IDLE — waiting\n", tick);
            return STATE_SAMPLING;

        case STATE_SAMPLING:
            printf("tick %u: SAMPLING — reading ADC\n", tick);
            return STATE_PROCESSING;

        case STATE_PROCESSING:
            printf("tick %u: PROCESSING — converting\n", tick);
            return STATE_TX;

        case STATE_TX:
            printf("tick %u: TX — sending over ETH\n", tick);
            return STATE_IDLE;

        case STATE_ERROR:
            printf("tick %u: ERROR — halted\n", tick);
            return STATE_ERROR;

        default:
            printf("tick %u: FATAL: unknown state\n", tick);
            return STATE_ERROR;
    }
}

int main(void) {
    SysState s = STATE_IDLE;
    for (uint32_t t = 0; t < 8; ++t) {
        s = run_one_tick(s, t);
    }
    return 0;
}
```
Compile: `gcc -Wall -Wextra -g -std=c2x -o state_machine state_machine.c`

This is the architecture of your ETH+ADC firmware. Every peripheral driver you write will have this shape. `switch` on a state enum, driven by a `for`-loop tick.

---

## Chapter Summary (from book p. 33)

- Numerical values can be used directly as conditions for `if`; `0` is false, all other values are true
- Three iteration statements: `for`, `do`, `while`. `for` is the preferred tool for domain iterations
- A `switch` performs multiple selections. One `case` runs into the next if not terminated by `break`

---

## MES Ch 5 Sidebar — Why Interrupts Need Clean Control Flow

An ISR (interrupt service routine) is called asynchronously by hardware. The CPU stops what it's doing, saves state, runs the ISR, then returns. ISRs must be short and cannot block.

The standard pattern (from MES Ch 5):
```c
volatile bool data_ready = false;   // written by ISR, read by main

// ISR — called by hardware when timer fires:
void TIM2_IRQHandler(void) {
    data_ready = true;              // set flag only — fast, no processing
}

// Main loop:
int main(void) {
    while (true) {
        if (data_ready) {           // check flag with if
            data_ready = false;
            // process data
        }
    }
}
```

The `if` checking the flag is control flow from this chapter. The `while (true)` main loop is iteration. The `switch` inside the processing block handles state. You're learning the building blocks of this exact pattern now — before the hardware makes it harder to debug.

**Why `volatile`?** Without it, the compiler may cache `data_ready` in a register and never re-read it from memory. The ISR writes to memory but the compiler doesn't know the ISR exists. `volatile` is covered in mc04 — flag it for now.
