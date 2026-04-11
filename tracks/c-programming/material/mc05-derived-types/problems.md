# Session mc05 — Problems
**Modern C Ch 6 (pp. 77–94) | MES Ch 2 sidebar**

---

### Problem 1: ADC Config Struct

**Context:** Every HAL peripheral driver starts with an init struct — building one from scratch teaches you exactly what CubeMX generates automatically.

**Thought process:**
1. What am I producing? A struct representing ADC channel configuration, two instances, a print function that takes a pointer.
2. What fields make sense? Channel number (uint8_t), resolution (enum), sample time in cycles (uint32_t), reference voltage in mV (uint16_t), a human-readable name (const char *).
3. How to pass to a function? By `const` pointer — the function only reads it.
4. Gotchas: Use designated initializers when creating instances. Arrow notation inside the function. Print all fields meaningfully.

**Task:** Write `adc_config.c` with:
- `typedef enum { ADC_RES_6=6, ADC_RES_8=8, ADC_RES_10=10, ADC_RES_12=12 } ADC_Res`
- `typedef struct { ... } ADC_Config` with at least 5 meaningful fields
- `void adc_print_config(const ADC_Config *cfg)` using arrow notation throughout
- Two instances: one for ADC1 on PB0 (channel 8, 12-bit), one for ADC3 on PC3 (channel 13, 10-bit)
- `main` that creates both with designated initializers, passes each to `adc_print_config`
- Compile: `gcc -Wall -Wextra -g -std=c2x -o adc_config adc_config.c`

---

### Problem 2: DMA Buffer + Max Finder

**Context:** ADC DMA transfers fill a buffer in memory automatically — your code then processes the buffer. This is the exact pattern for reading all three ADC channels simultaneously.

**Thought process:**
1. What am I producing? A simulated DMA receive buffer (global array) and a function that finds the max value.
2. Why global? DMA writes to a fixed address — it cannot be a local (stack) variable in production. Simulate this with a file-scope array.
3. Function signature: takes `const uint16_t *buf` and `size_t len`, returns `uint16_t`.
4. Gotchas: The function should not know the buffer size at compile time — always pass length as a parameter. Use `size_t` for the index, not `int`.

**Task:** Write `dma_buffer.c` with:
- Global `volatile uint16_t adc_dma_buf[16]` simulating a DMA destination
- `uint16_t buf_max(const uint16_t *buf, size_t len)` — returns max value
- `float buf_average(const uint16_t *buf, size_t len)` — returns average as float
- `void buf_print(const uint16_t *buf, size_t len)` — prints all values, 8 per line
- `main` that fills the buffer with a mix of values including a known max, calls all three functions, verifies max is correct
- Compile: `gcc -Wall -Wextra -g -std=c2x -o dma_buffer dma_buffer.c`

---

### Problem 3: Register Union

**Context:** The STM32 HAL defines peripheral register structs internally as unions — understanding how they work lets you read the HAL source code and write your own register-level drivers.

**Thought process:**
1. What am I producing? A union that lets you access a UART status register both as a `uint32_t` and as named bit fields.
2. Which bits? Model the STM32F407 USART_SR: PE(0), FE(1), NE(2), ORE(3), IDLE(4), RXNE(5), TC(6), TXE(7). Bits 8-31 reserved.
3. How to test it? Set the whole register with a known hex value, verify each bit field reads correctly. Then set a bit via the struct, verify the whole-word value changed correctly.
4. Gotchas: Bit fields are declared with `: N` syntax. The struct inside the union needs no tag name. Test both directions: word → bits and bits → word.

**Task:** Write `uart_union.c` with:
- `typedef union { uint32_t word; struct { uint32_t PE:1; ... } bits; } UART_SR`
- `void print_sr(UART_SR sr)` — prints the hex word and all named bit fields
- `main` with at least 4 test cases:
  - Set `word = 0x000000A0` (TXE + RXNE), verify bits
  - Set `word = 0x00000048` (TC + ORE), verify bits
  - Start from zero, set `bits.TXE = 1` and `bits.PE = 1`, verify word = `0x00000081`
  - Demonstrate clearing a bit via the word: `sr.word &= ~(1U << 5)` then check `sr.bits.RXNE`
- Compile: `gcc -Wall -Wextra -g -std=c2x -o uart_union uart_union.c`

---

### Problem 4: Full State Machine with Struct

**Context:** This is the architecture pattern for the ETH+ADC firmware you will write — a state machine where each state has associated data, updated by a function that takes a pointer.

**Thought process:**
1. What am I producing? A struct holding state machine data, updated by an `update()` function called in a loop.
2. What data? Current state (enum), a tick counter (uint32_t), a result buffer (float array, 3 entries — one per ADC), a transmit ready flag (bool or uint8_t).
3. Why pass by pointer? The function modifies the struct — must be a non-const pointer.
4. Build on session 2: Use the same state names (IDLE, SAMPLING, PROCESSING, TX, ERROR) but now the state is inside a struct alongside the data it produces.

**Task:** Write `state_machine.c` with:
- `typedef enum { STATE_IDLE, STATE_SAMPLING, STATE_PROCESSING, STATE_TX, STATE_ERROR } SysState`
- `typedef struct { SysState state; uint32_t tick; float adc_results[3]; uint8_t tx_ready; } SysCtx`
- `void sys_update(SysCtx *ctx)` — advances the state machine one tick:
  - IDLE: increment tick, transition to SAMPLING after 3 ticks
  - SAMPLING: fill `adc_results` with simulated values (e.g., `1000.0f + tick`), transition to PROCESSING
  - PROCESSING: scale results (multiply by 3300.0f/4095.0f), set `tx_ready=1`, transition to TX
  - TX: print all three results, clear `tx_ready`, transition to IDLE
- `main` that creates a `SysCtx`, initializes it, runs `sys_update` in a loop 12 times, printing state name and tick each iteration
- Compile: `gcc -Wall -Wextra -g -std=c2x -o state_machine state_machine.c`
