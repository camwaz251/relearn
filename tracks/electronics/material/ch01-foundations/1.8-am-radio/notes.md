# Ch. 1.8 — Putting It All Together: An AM Radio
*Art of Electronics, pp. 55–56 (§1.8)*

---

## The Crystal Set — Simplest AM Receiver

**What it is:** A circuit that ties together every concept from Ch. 1 in one practical application: resonance, rectification, filtering, and loading. (See Figure 1.114, p. 56)

### Circuit Block by Block

```
Antenna → [LC tank C1/L] → [Diode D] → [R1 || C2] → Audio amplifier → Speaker
```

1. **Antenna:** Picks up a superposition of all AM stations (520–1720 kHz) plus powerline noise and other interference.

2. **Parallel LC tank (variable C1 + L):** Tuned to the desired station's carrier frequency. At resonance, the tank presents maximum impedance — only the selected frequency "gets through." The voltage across the tank at resonance is Q × V_antenna. High Q = better selectivity and sensitivity.

3. **Diode D:** Half-wave rectifies the modulated carrier. Strips off the negative half-cycles, leaving only positive half-cycles. This is the detection step — the envelope of the original AM signal is now visible.

4. **R1** provides a DC path so the diode has something to drive. Light load so Q is not degraded.

5. **C2** smooths the rectified carrier. Time constant R1×C2 must satisfy:
   - Long compared to the carrier period (~1μs at 1MHz) → smooths out the RF
   - Short compared to the audio period (~200μs at 5kHz) → follows the audio envelope
   - Typical: R1 = 100kΩ, C2 = 100pF → τ = 10μs (good)

6. **Audio amplifier** (Ch. 2+): Boosts the weak envelope signal to drive a speaker.

### The AM Signal Itself

AM modulates the *amplitude* of a high-frequency carrier with a low-frequency audio signal:
```
V(t) = [A + f(t)] * cos(2π f_c t)
```
where f(t) is the audio and f_c is the carrier frequency. The constant A keeps the coefficient always positive (no phase reversal).

The diode + RC filter is an **envelope detector** — it extracts f(t) (the slow amplitude modulation) while discarding the fast carrier cos(2πf_c t).

### Key Observations

- The LC tank amplifies the selected station by a factor of Q before the diode sees it. Higher Q = more sensitive but more narrow-band (less adjacent-channel rejection).
- Adding the LC to the antenna dramatically reduces interference from adjacent stations and power line noise (the low-frequency "hum" disappears because the LC is high-impedance at 60Hz).
- The bare antenna without LC picks up all stations simultaneously — you hear a cacophony.

### Why This Matters

Every concept in Ch. 1 appears here:
- Thévenin: the antenna has a source impedance; loading the tank degrades Q
- RC time constant: the envelope filter values
- Resonance: LC tank selection
- Rectification: diode half-wave
- Filtering: C2 removes carrier, passes audio
- Decibels: Q × gain at resonance

> **Embedded tie-in:** The envelope detector concept appears in RF receivers (AM, ASK modulation in RFID), motor back-EMF detection, and any circuit that extracts a slowly-varying amplitude from a high-frequency carrier. The LC tank concept appears in crystal oscillators, PLL loop filters, and impedance-matching networks.
