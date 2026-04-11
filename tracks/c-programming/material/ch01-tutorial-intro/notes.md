# Ch. 1 — A Tutorial Introduction

K&R's opening move: the entire language in one pass. You know C++ — this chapter is about seeing what C *doesn't* have and why that matters on bare metal.

---

### 1. Program Structure & Compilation

Every C program starts at `main()`. There's no class, no namespace — just functions and a starting point.

```c
#include <stdio.h>

int main(void)
{
    printf("hello, world\n");
    return 0;
}
```

`#include <stdio.h>` tells the preprocessor to paste in the standard I/O declarations — function prototypes for `printf`, `getchar`, etc. Without it, the compiler doesn't know what `printf` is.

`main` returns `int`. The `return 0` tells the OS (or bootloader, on embedded) that the program exited normally. On bare metal, `main` often never returns — it runs a `while(1)` loop forever.

**Compiling:**

```
gcc -Wall -Wextra -g -o hello hello.c
```

- `-Wall -Wextra` — turn on warnings. Treat these as errors in practice.
- `-g` — include debug symbols so GDB can show you source lines.
- `-o hello` — name the output binary.

The build pipeline: **preprocess** (`#include` expansion, `#define` replacement) → **compile** (C to assembly) → **assemble** (assembly to object code) → **link** (combine objects into a binary). On embedded, you'll eventually write linker scripts and startup files that control this pipeline directly.

---

### 2. Variables, Types & Declarations

C requires you to declare variables before use. In C89 (K&R style), declarations go at the top of a block.

```c
int main(void)
{
    int fahr, celsius;       /* integer types */
    float voltage;           /* floating point */
    char c;                  /* single byte */
    long count;              /* at least 32 bits */
    double precise;          /* double-precision float */

    fahr = 100;
    celsius = 5 * (fahr - 32) / 9;
    printf("%d F = %d C\n", fahr, celsius);
    return 0;
}
```

Key difference from C++: no `bool` without `<stdbool.h>` (C99), no `string`, no `auto` type deduction.

**Type sizes are machine-dependent.** The standard only guarantees minimums:
- `char` — at least 8 bits (always 1 byte by definition)
- `int` — at least 16 bits (could be 16 on AVR, 32 on ARM)
- `long` — at least 32 bits

In embedded, you use `<stdint.h>` types to nail down exact widths:

```c
#include <stdint.h>

uint8_t  sensor_byte;    /* exactly 8 bits, unsigned */
int16_t  temperature;    /* exactly 16 bits, signed */
uint32_t timestamp;      /* exactly 32 bits, unsigned */
```

K&R predates `stdint.h`, but the lesson is the same: **never assume a type's size.**

---

### 3. Arithmetic & Type Conversion

Integer division truncates — the fractional part is thrown away.

```c
int result;
result = 5 / 9;          /* result is 0, not 0.555 */
result = 1 / 3;          /* result is 0 */
result = 7 / 2;          /* result is 3 */
```

When you mix `int` and `float`, the int gets promoted to float:

```c
float voltage;
voltage = 5.0 / 9.0;           /* 0.555... — both are float */
voltage = 5 / 9;               /* 0.0 — integer division, then assigned to float */
voltage = 5.0 * (100 - 32) / 9.0;  /* correct — float math throughout */
```

**The order of operations matters for precision.** This is a classic embedded trick:

```c
/* BAD: 5/9 is 0, everything becomes 0 */
celsius = 5 / 9 * (fahr - 32);

/* GOOD: multiply first to keep precision, divide last */
celsius = 5 * (fahr - 32) / 9;
```

Why this matters in embedded: many MCUs have no floating-point unit (FPU). Float math on a Cortex-M0 is done in software — 10–100x slower than integer math. Embedded convention: use scaled integers and do the multiply before the divide.

---

### 4. Control Flow: while, for, if-else

**`while`** — test, then execute:

```c
int i = 0;
while (i < 10) {
    printf("%d\n", i);
    i++;
}
```

**`for`** — compact `while` with init and step in one line:

```c
int i;
for (i = 0; i < 10; i++) {
    printf("%d\n", i);
}
```

These are identical in behavior. `for` is preferred when the loop structure is obvious. In C89, you can't declare `i` inside the `for` — that's C99.

**`if` / `else if` / `else`:**

```c
if (temp > 100) {
    printf("OVERHEAT\n");
} else if (temp > 80) {
    printf("WARNING\n");
} else {
    printf("OK\n");
}
```

**Embedded connection:** The backbone of bare-metal firmware is a superloop:

```c
int main(void)
{
    init_hardware();
    while (1) {             /* never returns */
        read_sensors();
        process_data();
        update_outputs();
    }
    return 0;  /* never reached */
}
```

A UART polling loop: `while (!(UART_SR & RX_READY)) {}` — spins until a byte arrives.

---

### 5. Symbolic Constants (#define)

`#define` is preprocessor text substitution — it runs *before* compilation.

```c
#define BUFFER_SIZE  256
#define MAX_TEMP     120
#define UART_BASE    0x40011000
#define PI           3.14159

int buffer[BUFFER_SIZE];   /* becomes: int buffer[256]; */
```

Rules:
- No semicolon at the end (it would be pasted into your code)
- No `=` sign (it's not an assignment)
- ALL_CAPS by convention
- Not a variable — no memory, no address, no type checking

```c
/* BAD — semicolon gets pasted */
#define SIZE 10;
int a[SIZE];       /* becomes: int a[10;]; — compiler error */

/* GOOD */
#define SIZE 10
int a[SIZE];       /* becomes: int a[10]; */
```

In embedded, every MCU vendor header file is thousands of `#define` lines mapping register addresses and bit masks:

```c
#define GPIO_PORT_A   0x40020000
#define GPIO_PIN_5    (1 << 5)
#define LED_ON        (GPIO_PORT_A |= GPIO_PIN_5)
```

---

### 6. Character I/O: getchar, putchar, EOF

`getchar()` reads one byte from stdin. `putchar(c)` writes one byte to stdout. This is the simplest I/O model — and it maps directly to UART byte-at-a-time communication.

```c
#include <stdio.h>

int main(void)
{
    int c;                          /* int, NOT char — must hold EOF */
    while ((c = getchar()) != EOF) {
        putchar(c);
    }
    return 0;
}
```

**Why `int` and not `char`?** `EOF` is typically -1. If `char` is unsigned on your platform (which it is on ARM by default), then -1 becomes 255, and `c != EOF` is always true — infinite loop. This is a real embedded bug.

**The assignment-in-condition idiom:** `(c = getchar()) != EOF` does two things in one expression:
1. Reads a character and stores it in `c`
2. Tests whether it's `EOF`

The parentheses around `c = getchar()` are required — without them, `!=` binds tighter than `=`, and you'd test `getchar() != EOF` first, then assign `0` or `1` to `c`.

**Counting characters with a while loop:**

```c
long nc = 0;
while (getchar() != EOF)
    nc++;
printf("%ld\n", nc);
```

Note `long` and `%ld` — a `char` count can exceed `int` range for large files.

---

### 7. Arrays

Fixed-size, zero-indexed, no bounds checking.

```c
int counts[10];          /* 10 ints: counts[0] through counts[9] */
int i;

/* Initialize to zero */
for (i = 0; i < 10; i++)
    counts[i] = 0;

/* Count digit occurrences */
int c;
while ((c = getchar()) != EOF)
    if (c >= '0' && c <= '9')
        counts[c - '0']++;      /* character arithmetic: '3' - '0' = 3 */
```

**`c - '0'` explained:** Characters are just numbers. `'0'` is 48, `'1'` is 49, ..., `'9'` is 57. So `'5' - '0'` = 53 - 48 = 5. This converts a digit *character* to its *integer value*.

There is no bounds checking. `counts[10]` compiles fine — it reads/writes garbage memory. On an MCU, this can corrupt a peripheral register or the stack. Always validate indices.

**Embedded connection:** Lookup tables are everywhere — ADC-to-temperature conversion, sine tables for motor control, CRC tables. Fixed-size arrays with constant indices are the bread and butter.

```c
/* 256-entry lookup: index directly with ADC byte */
const int16_t temp_lut[256] = { -40, -39, -38, /* ... */ 125 };
int16_t temperature = temp_lut[adc_reading];   /* O(1), no math */
```

---

### 8. Functions

A function has a return type, a name, parameters, and a body.

```c
/* Prototype (declaration) — tells compiler what to expect */
int power(int base, int exp);

int main(void)
{
    int result;
    result = power(2, 10);
    printf("2^10 = %d\n", result);
    return 0;
}

/* Definition — the actual implementation */
int power(int base, int exp)
{
    int p = 1;
    int i;
    for (i = 0; i < exp; i++)
        p = p * base;
    return p;
}
```

The prototype goes before `main` (or in a header file). Without it, the compiler sees `power(2, 10)` before knowing what `power` looks like, and in C89 it assumes `int` for everything — which may silently produce wrong results.

**`void` return and parameters:**

```c
void print_header(void)       /* takes nothing, returns nothing */
{
    printf("=== SENSOR LOG ===\n");
}
```

`void` in the parameter list explicitly means "no arguments." An empty `()` in C (unlike C++) means "unspecified arguments" — a subtle difference.

---

### 9. Call by Value

C always copies arguments. The function gets its own copy — modifying it does not affect the caller.

```c
int power(int base, int exp)
{
    int p;
    for (p = 1; exp > 0; exp--)   /* exp is a copy — safe to modify */
        p = p * base;
    return p;
}
```

K&R's version decrements `exp` directly inside the function. This works because `exp` is a copy of whatever the caller passed. The caller's variable is untouched.

```c
int n = 5;
int result = power(2, n);
/* n is still 5 here — power() modified its own copy */
```

**The exception: arrays.** When you pass an array, C passes the address of the first element — so the function *can* modify the original data.

```c
void zero_out(int arr[], int len)
{
    int i;
    for (i = 0; i < len; i++)
        arr[i] = 0;              /* modifies the caller's array */
}

int data[5] = {1, 2, 3, 4, 5};
zero_out(data, 5);
/* data is now {0, 0, 0, 0, 0} */
```

**Embedded connection:** When you write to a peripheral register, you need its *address*, not a copy of its value. This is why embedded C is pointer-heavy — call by value forces you to pass addresses explicitly:

```c
void read_sensor(int *result)   /* pointer passed by value */
{
    *result = ADC_DATA_REG;     /* writes to caller's variable */
}
```

---

### 10. Character Arrays & Strings

Strings in C are `char` arrays terminated by `'\0'` (null byte, value 0). There is no string type.

```c
char msg[] = "hello";
/* In memory: 'h' 'e' 'l' 'l' 'o' '\0'  — 6 bytes, not 5 */
```

K&R's `getline` reads characters into a buffer until newline or limit:

```c
int getline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';        /* null-terminate */
    return i;
}
```

And `copy` duplicates a string:

```c
void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        i++;
}
```

`copy` works by assigning characters one at a time until it hits `'\0'`. The assignment `to[i] = from[i]` returns the assigned value, which is tested against `'\0'`.

**Buffer size matters.** `lim - 1` in `getline` leaves room for the null terminator. Off-by-one here means memory corruption. On an MCU with no memory protection, that corruption can overwrite the stack, crash the system, or silently produce wrong output.

---

### 11. External Variables & Scope

Variables declared outside functions are *external* — visible from their declaration to the end of the file.

```c
#include <stdio.h>

#define MAXLINE 1000

int max;                        /* external — visible to all functions below */
char longest[MAXLINE];          /* external */

int getline(char s[], int lim);
void copy(char to[], char from[]);

int main(void)
{
    int len;
    char line[MAXLINE];

    max = 0;
    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0)
        printf("%s", longest);
    return 0;
}
```

`max` and `longest` are shared state — all functions in this file can read and write them. Local (automatic) variables like `len` and `line` live on the stack, created when the function is entered, destroyed when it returns.

**`extern` keyword:** If `max` were defined in another file, you'd declare it with `extern int max;` — "this variable exists somewhere else, the linker will find it."

**Embedded connection:** Shared state between an ISR and the main loop uses external variables — but with a critical caveat:

```c
volatile uint8_t rx_flag = 0;    /* external, shared between ISR and main */

void UART_IRQHandler(void)       /* interrupt service routine */
{
    rx_flag = 1;
}

int main(void)
{
    while (1) {
        if (rx_flag) {           /* without volatile, compiler may optimize this away */
            rx_flag = 0;
            process_data();
        }
    }
}
```

Without `volatile`, the compiler sees that `rx_flag` is never modified inside `main()` and optimizes the check into a constant — your main loop never sees the ISR's update. K&R doesn't cover `volatile` yet, but the pattern starts here.
