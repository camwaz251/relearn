# Session mc05 — Derived Types
**Modern C Ch 6 (book pp. 77–94) | MES Ch 2 sidebar**

---

## What this chapter covers (Modern C p. 77)

- Grouping objects into arrays
- Using pointers as opaque types
- Combining objects into structures
- Giving types new names with `typedef`

All derived types are built from the basic types covered in mc04.

---

## 1. Arrays — Contiguous Memory Blocks (pp. 77–80)

An array is a sequence of objects of the same type stored contiguously. On embedded this is critical — DMA requires contiguous buffers, and cache performance depends on spatial locality.

**Arrays are not pointers (Takeaway 6.1 #1, p. 77).** This is the book's first and most emphatic takeaway about arrays. Arrays and pointers are closely related but not the same thing.

### Declaration and initialization

```c
double a[4];                              // 4 doubles, uninitialized
signed b[N];                              // N signed ints (VLA if N not constant)
double E[] = { [3] = 42.0, [2] = 37.0 }; // 4 elements, designated init
double F[] = { 22.0, 17.0, 1, 0.5 };     // 4 elements, positional init
```

**The length of an array A is `sizeof A / sizeof A[0]` (Takeaway 6.1.3 #6, p. 80):**
```c
#include <stdint.h>
#include <stdio.h>

int main(void) {
    uint16_t adc_buf[16] = {0};
    size_t len = sizeof adc_buf / sizeof adc_buf[0];   // 16
    printf("Buffer has %zu elements\n", len);

    for (size_t i = 0; i < len; ++i) {
        adc_buf[i] = (uint16_t)(i * 256);
    }
    return 0;
}
```

### Array length: FLA vs VLA (p. 79)

- **Fixed-length array (FLA):** length is an integer constant expression — known at compile time
- **Variable-length array (VLA):** length determined at runtime — can't be declared outside functions, optional since C23

### Arrays as function parameters (p. 80)

**The innermost dimension of an array parameter to a function is lost (Takeaway 6.1.4 #1, p. 80).** Always pass the length separately:

```c
// These two declarations are equivalent:
void process(uint16_t *buf, size_t len);
void process(uint16_t buf[], size_t len);

// Inside the function, sizeof buf gives pointer size, not array size
// (Takeaway 6.1.4 #2: Don't use sizeof on array parameters)
```

**Array parameters behave as if the array is passed by reference (Takeaway 6.1.4 #3, p. 80).** Modifying `buf[i]` inside the function modifies the caller's array.

**Embedded angle — DMA buffer:**
```c
volatile uint16_t adc_dma_buf[3];   // one slot per ADC channel
// DMA controller needs: start address (array name) and length (3)
// This is the exact pattern for ADC DMA transfers on STM32
```

---

## 2. Pointers — Just Enough for HAL (pp. 84–85)

Full pointer coverage is in a later session (mc09). Here is exactly what you need now to read HAL function signatures.

**Pointers are opaque objects (Takeaway 6.2 #1, p. 84).** They refer to data stored elsewhere. The `*` syntax declares a pointer:

```c
char const*const p2string = "some_text";   // pointer to string literal
```

**Pointers are valid, null, or invalid (Takeaway 6.2 #2, p. 84):**
- **Valid:** points to an actual object
- **Null:** `nullptr` (C23) or `NULL` — explicitly "points to nothing"
- **Invalid:** uninitialized or pointing to freed memory — using it is undefined behavior

**In logical expressions, pointers evaluate to `false` if they are null (Takeaway 6.2 #4, p. 85):**
```c
char const* p = get_name();
if (p) {                     // true if p is not null
    printf("Name: %s\n", p);
}
```

**Always initialize pointers (Takeaway 6.2 #6, p. 85).** Invalid pointers lead to program failure (Takeaway 6.2 #5).

**Why HAL passes structs by pointer:**
```c
// By value — copies the whole struct (expensive, 20+ bytes on stack)
void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef init);

// By pointer — passes 4 bytes (address), struct stays in place
void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *init);

// const pointer — function promises not to modify the struct
void print_config(const GPIO_InitTypeDef *init);
```

**Arrow vs dot notation:**
```c
GPIO_Config cfg;          // value — use dot
cfg.pin = 5;

GPIO_Config *ptr = &cfg;  // pointer — use arrow
ptr->pin = 5;             // equivalent to (*ptr).pin = 5
```

---

## 3. Structures — Grouping Peripheral Config (pp. 85–90)

If arrays group objects of the **same** type, structures group objects of **different** types. Every HAL driver uses structs for configuration.

### Declaration and access (p. 85–86)

```c
struct birdStruct {
    char const* jay;
    char const* magpie;
    char const* raven;
};

struct birdStruct const aName = {
    .raven  = "Lissy",
    .magpie = "Frau",
    .jay    = "Joe",
};

printf("Raven: %s\n", aName.raven);   // dot notation for values
```

Members are accessed with `.` (dot) for values, `->` (arrow) for pointers.

**Omitted `struct` initializers force the corresponding member to 0 (Takeaway 6.3.1 #1, p. 87).**

### Structs are passed by value (Takeaway 6.3.1 #2, p. 87)

```c
struct tm time_set_yday(struct tm t) {
    t.tm_yday += DAYS_BEFORE[t.tm_mon] + t.tm_mday - 1;
    return t;   // modifies local copy only
}
today = time_set_yday(today);   // must reassign
```

This is why HAL passes structs by **pointer** — to modify the original without copying.

**Structures can be assigned but cannot be compared with `==` or `!=` (Takeaways 6.3.1 #3–#4, p. 88).**

**A structure layout is an important design decision (Takeaway 6.3.1 #5, p. 88).** Changing it later breaks all existing code.

### Struct padding (p. 90)

**There can be padding after any structure member (Takeaway 6.3.4 #1, p. 90).** The compiler aligns fields to their natural boundaries:

```c
struct Sensor {
    uint8_t  channel;    // 1 byte
    // 3 bytes padding — compiler aligns uint32_t to 4-byte boundary
    uint32_t timestamp;  // 4 bytes
    uint16_t raw_value;  // 2 bytes
    // 2 bytes padding — total struct size = 12
};

struct SensorPacked {
    uint32_t timestamp;  // 4 bytes — put largest first
    uint16_t raw_value;  // 2 bytes
    uint8_t  channel;    // 1 byte
    uint8_t  _pad;       // 1 byte explicit — total = 8 bytes
};
```

**Embedded rule:** Order struct fields largest to smallest to minimize padding.

**Embedded angle — HAL init struct (mirrors `GPIO_InitTypeDef`):**
```c
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint32_t pin;       // which pin(s) — bitmask
    uint8_t  mode;      // input, output, AF, analog
    uint8_t  pull;      // no pull, pull-up, pull-down
    uint8_t  speed;     // low, medium, high, very high
    uint8_t  alternate; // alternate function (0-15)
} GPIO_Config;

void gpio_init(uint32_t port_base, const GPIO_Config *cfg) {
    printf("Init port 0x%08X pin(s) 0x%04X\n", port_base, cfg->pin);
    printf("  mode=%u pull=%u speed=%u af=%u\n",
           cfg->mode, cfg->pull, cfg->speed, cfg->alternate);
}

int main(void) {
    GPIO_Config led_cfg = {
        .pin       = (1U << 12),   // PD12 — green LED on Discovery
        .mode      = 1,            // output
        .pull      = 0,            // no pull
        .speed     = 2,            // high speed
        .alternate = 0,            // not used for GPIO output
    };
    gpio_init(0x40020C00, &led_cfg);   // GPIOD base address
    return 0;
}
```
Compile: `gcc -Wall -Wextra -g -std=c2x -o gpio_config gpio_config.c`

---

## 4. `typedef` — Cleaner Driver APIs (pp. 92–93)

Without `typedef` you write `struct GPIO_Config` everywhere. With it, just `GPIO_Config`. HAL uses `typedef` for everything.

**A `typedef` only creates an alias for a type but never a new type (Takeaway 6.4 #2, p. 93).**

**Forward-declare a `struct` within a `typedef` using the same identifier as the tag name (Takeaway 6.4 #1, p. 93):**
```c
typedef struct GPIO_Config GPIO_Config;
struct GPIO_Config {
    uint32_t pin;
    uint8_t  mode;
    // ...
};
```

**Identifier names terminating with `_t` are reserved (Takeaway 6.4 #3, p. 93).** The standard uses `_t` for its own types (`size_t`, `uint32_t`). Don't create your own `_t` names in production code — use `_TypeDef` like HAL does, or just omit the suffix.

**STM32 HAL naming conventions:**
- `GPIO_InitTypeDef` — init configuration struct
- `GPIO_TypeDef` — the peripheral register struct (maps to hardware memory)
- `ADC_HandleTypeDef` — handle struct (config + state + pointer to peripheral)

---

## 5. `enum` — Named States and Modes (from Ch 5 §5.6.2)

Enums were covered in mc04 (named constants). Here they combine with structs for the complete HAL pattern:

```c
typedef enum {
    GPIO_MODE_INPUT  = 0,
    GPIO_MODE_OUTPUT = 1,
    GPIO_MODE_AF     = 2,
    GPIO_MODE_ANALOG = 3,
} GPIO_Mode;

typedef enum {
    STATE_IDLE,
    STATE_SAMPLING,
    STATE_PROCESSING,
    STATE_TX,
    STATE_ERROR,
} SysState;
```

When paired with a struct, the enum gives type safety to the state field:
```c
typedef struct {
    SysState state;
    uint32_t tick;
    float    adc_results[3];
    uint8_t  tx_ready;
} SysCtx;
```

---

## 6. Union — Register Bit-Field Access (preview, full coverage in Ch 12)

Unions are not in Ch 6 — the book covers them in Ch 12 (Memory Model). But they're essential for embedded register access, so here's a preview.

A union lets you access the **same memory** as different types:

```c
#include <stdint.h>
#include <stdio.h>

typedef union {
    uint32_t word;       // access whole register
    struct {
        uint32_t PE   : 1;   // bit 0 — parity error
        uint32_t FE   : 1;   // bit 1 — framing error
        uint32_t NE   : 1;   // bit 2 — noise error
        uint32_t ORE  : 1;   // bit 3 — overrun error
        uint32_t IDLE : 1;   // bit 4 — idle line detected
        uint32_t RXNE : 1;   // bit 5 — read data register not empty
        uint32_t TC   : 1;   // bit 6 — transmission complete
        uint32_t TXE  : 1;   // bit 7 — transmit data register empty
        uint32_t _res : 24;  // bits 8-31 reserved
    } bits;
} UART_SR;

int main(void) {
    UART_SR sr;
    sr.word = 0x000000A0;   // TXE (bit7) + RXNE (bit5) set

    printf("SR = 0x%08X\n", sr.word);
    printf("TXE  = %u\n", sr.bits.TXE);    // 1
    printf("RXNE = %u\n", sr.bits.RXNE);   // 1
    printf("TC   = %u\n", sr.bits.TC);     // 0

    sr.bits.TC = 1;
    printf("After setting TC: 0x%08X\n", sr.word);  // 0xE0
    return 0;
}
```
Compile: `gcc -Wall -Wextra -g -std=c2x -o uart_union uart_union.c`

**Do not use bare `int` for bit-field specification (Takeaway 6.3.4 #3, p. 91).** Use `unsigned` or `uint32_t`.

**Warning:** Bit-field layout is implementation-defined — bit ordering may vary between compilers and targets. Safe for readability and testing. For production drivers, most teams use explicit masks (`reg & (1U << 5)`) instead.

---

## Chapter Summary (from book p. 94)

- Arrays combine several values of the same base type into one object
- Pointers either refer to other objects, are null, or are invalid
- Structures combine values of different base types into one object
- `typedef`s provide new names for existing types

---

## MES Ch 2 Sidebar — Driver Interface Pattern

Every peripheral driver in professional embedded firmware follows the same structure:

```c
// open/init — configure the peripheral
HAL_StatusTypeDef ADC_Init(ADC_HandleTypeDef *hadc);

// read — get data from the peripheral
HAL_StatusTypeDef ADC_PollForConversion(ADC_HandleTypeDef *hadc, uint32_t timeout);
uint32_t          ADC_GetValue(ADC_HandleTypeDef *hadc);

// write/control — send commands or data
HAL_StatusTypeDef ADC_Start(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef ADC_Stop(ADC_HandleTypeDef *hadc);
```

The `HandleTypeDef` struct contains:
- Pointer to the peripheral's register struct (the hardware)
- Configuration (what you set up in `Init`)
- State (`IDLE`, `BUSY`, `ERROR` — prevents concurrent access)
- Error code (what went wrong)

This is exactly what you pass around when writing LWIP + ADC code. Every HAL call takes `&hadc1` or `&heth` as its first argument — that handle struct is the bridge between your code and the hardware.

The struct + typedef + enum + pointer patterns you learned in this session are the complete toolkit for reading and writing HAL code.
