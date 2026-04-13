# Bitwise Quick Reference — mc02 problem 3 prep

---

## The operators and what they actually do

| Operator | Name | Utility |
|----------|------|---------|
| `&` | AND | **Extract / test** a bit — "is this flag set?" |
| `\|` | OR | **Set** a bit — "turn this flag on" |
| `^` | XOR | **Toggle** a bit — "flip this flag" |
| `~` | NOT | **Invert** all bits |
| `<<` | Left shift | **Move bits left** — multiply by powers of 2, or place a 1 at a specific bit position |
| `>>` | Right shift | **Move bits right** — divide by powers of 2, or check upper bits |

You'll use `<<` and `&` constantly in embedded. `|` next. The rest come up less often at this stage.

---

## Bit shifting

`1U << N` puts a 1 at bit position N, all other bits 0.

```
1U       = 0000 0001   (bit 0)
1U << 1  = 0000 0010   (bit 1)
1U << 4  = 0001 0000   (bit 4)
1U << 7  = 1000 0000   (bit 7)
```

This is how you build a **bitmask** — a value that isolates one specific bit.

Why `1U` and not `1`? Plain `1` is a signed int. Shifting into the sign bit (bit 31) is undefined behavior. `U` makes it unsigned — safe to shift anywhere.

---

## Extracting / testing a bit with `&`

`&` compares two values bit by bit. A bit is 1 in the result only if **both** inputs have a 1 there.

```
  1010 1100   (your register value)
& 0000 1000   (mask for bit 3)
-----------
  0000 1000   (nonzero = bit 3 is SET)
```

```
  1010 0100   (different register value)
& 0000 1000   (mask for bit 3)
-----------
  0000 0000   (zero = bit 3 is NOT set)
```

In C:

```c
if (reg & (1U << 3)) {
    // bit 3 is set
}
```

The result is either 0 (bit not set) or nonzero (bit is set). C treats nonzero as true — so this `if` works directly.

---

## Setting a bit with `|`

`|` compares two values bit by bit. A bit is 1 in the result if **either** input has a 1 there.

```
  1010 0100   (your register value)
| 0000 1000   (mask for bit 3)
-----------
  1010 1100   (bit 3 is now SET, everything else unchanged)
```

In C:

```c
reg = reg | (1U << 3);   // set bit 3
// shorthand:
reg |= (1U << 3);
```

Embedded use: turning on a peripheral, enabling an interrupt, asserting a GPIO pin via a control register.

---

## Toggling a bit with `^`

`^` compares two values bit by bit. A bit is 1 in the result if the inputs **differ**.

```
  1010 1100   (your register value)
^ 0000 1000   (mask for bit 3)
-----------
  1010 0100   (bit 3 flipped — was 1, now 0)
```

```
  1010 0100   (same register, bit 3 already 0)
^ 0000 1000   (mask for bit 3)
-----------
  1010 1100   (bit 3 flipped — was 0, now 1)
```

In C:

```c
reg ^= (1U << 3);   // toggle bit 3 — if it was on, turn off; if off, turn on
```

Embedded use: blinking an LED by toggling a GPIO output register each tick.

---

## Inverting all bits with `~`

`~` flips every bit in the value. 0 becomes 1, 1 becomes 0.

```
~ 0000 1000
-----------
  1111 0111   (every bit flipped)
```

Most common use: **clearing** a specific bit while leaving all others alone.

```
  1010 1100   (your register value)
& 1111 0111   (~(1U << 3) — all 1s except bit 3)
-----------
  1010 0100   (bit 3 cleared, everything else unchanged)
```

In C:

```c
reg &= ~(1U << 3);   // clear bit 3
```

`~` alone isn't used much. It's almost always paired with `&` to clear a bit.

---

## Why separate `if`, not `else if`?

Multiple flags can be set at the same time in a status register.  
`else if` stops checking after the first match. You'd miss the others.  
Separate `if` blocks check every flag independently.

```c
if (reg & SR_BUSY)      { printf("[BUSY]\n"); }
if (reg & SR_RX_FULL)   { printf("[RX_FULL]\n"); }
if (reg & SR_PARITY_ERR){ printf("[PARITY_ERR]\n"); }
```

All three can print on the same register value.

---

## Quick practice (mental — no coding)

Given: `uint8_t reg = 0b10110010;`  (8-bit for simplicity)

1. Is bit 1 set? → `reg & (1U << 1)` = ?
2. Is bit 3 set? → `reg & (1U << 3)` = ?
3. Is bit 7 set? → `reg & (1U << 7)` = ?

Work it out on paper. Answers: bit 1 yes, bit 3 yes, bit 7 yes.  
(Binary: bit positions 7-6-5-4-3-2-1-0 → `1-0-1-1-0-0-1-0`)

---

Now you have everything you need for problem 3.
