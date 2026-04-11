# C Programming — Session Index

Primary pace-setter: **Mastering STM32** (Noviello, 2022)
C refreshers: **Modern C** (Gustedt, C23) + **Making Embedded Systems** (White, 2nd ed)
Status: `done` / `in-progress` / `ready` / `not started`

Hardware: STM32F407G-DISC1 | PHY: LAN8740A | Goals: ETH/LWIP + 3× ADC
Board status: ACTIVE — blink LED flashed 2026-03-30

---

## How sessions work

**mcXX sessions** — C Refresher (Modern C as source, embedded framing from MES)
Do these first when the corresponding STM32 chapter needs those C fundamentals.

**msXX sessions** — STM32 HAL (Mastering STM32 as source, code on Discovery board)
These are the primary sessions. Pace is set by your work reading.

---

## Session 1 — Getting Started (done before restructure)

| Session | Source | Topic | Status |
|---------|--------|-------|--------|
| mc01 | Modern C Ch 1–2 | Getting Started, Program Structure | in-progress |

---

## C Refreshers (do mc02–mc05 before ms06)

| Session | Modern C Ch. | Topic | Status | Needed before |
|---------|-------------|-------|--------|--------------|
| mc02 | Ch 3 | Control (if/else, switch, loops) | ready | ms07 Interrupts |
| mc03 | Ch 4 | Computations (bitwise, shifts, masks) | ready | ms10 Clock Tree |
| mc04 | Ch 5 | Values and Data (stdint, volatile, const, float) | ready | ms12 ADC |
| mc05 | Ch 6 | Derived Types (structs, typedef, enum, arrays, pointers) | ready | ms06 GPIO |
| mc06 | Ch 7 | Functions | not started | ms08 UART |
| mc07 | Ch 8 | C Library | not started | ms08 UART |

---

## STM32 HAL Sessions (Mastering STM32 primary)

| Session | MS Ch. | Topic | C Prereqs | MES Sidebar | Status |
|---------|--------|-------|-----------|-------------|--------|
| ms06 | Ch 6 | GPIO — modes, HAL_GPIO_Init, BSRR | mc05 | MES Ch4 I/O | not started |
| ms07 | Ch 7 | Interrupts — NVIC, EXTI, ISR patterns | mc02, mc03 | MES Ch5 | not started |
| ms08 | Ch 8 | UART — HAL_UART, polling + DMA | mc06 | MES Ch7 serial | not started |
| ms09 | Ch 9 | DMA — streams, circular mode | mc05 | MES Ch7 DMA | not started |
| ms10 | Ch 10 | Clock Tree — RCC, PLL, prescalers | mc03 | MES Ch4 | not started |
| ms11 | Ch 11 | Timers — TIM config, PWM, input capture | mc03, mc04 | MES Ch4 | not started |
| ms12 | Ch 12 | ADC — HAL_ADC, DMA mode, 3-channel | mc04, mc05 | MES Ch8 ADC | not started |
| ms13 | Ch 13 | DAC | mc04 | — | not started |
| ms14 | Ch 14 | I²C | mc06 | MES Ch7 | not started |
| ms15 | Ch 15 | SPI | mc06 | MES Ch7 | not started |
| ms26 | Ch 26 | Ethernet / LWIP | mc10, mc13 | MES Ch10 | not started |

---

## Deeper C (add alongside STM32 sessions as needed)

| Session | Modern C Ch. | Topic | Status |
|---------|-------------|-------|--------|
| mc08 | Ch 9–10 | Style, Organization, Headers | not started |
| mc09 | Ch 11 | Pointers (deep) | not started |
| mc10 | Ch 12 | Memory Model | not started |
| mc11 | Ch 13 | Storage (malloc, stack/heap, static) | not started |
| mc12 | Ch 14 | Advanced I/O | not started |
| mc13 | Ch 15 | Program Failure, Error Handling | not started |

---

## Legacy (K&R-based, superseded)

| Chapter | Topic | Status | Notes |
|---------|-------|--------|-------|
| Ch. 1 | A Tutorial Introduction | superseded | Material in `material/ch01-tutorial-intro/`, kept as reference |
