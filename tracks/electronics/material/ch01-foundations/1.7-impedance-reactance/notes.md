# Ch. 1.7 — Impedance and Reactance
*Art of Electronics, pp. 40–55 (§1.7.1–1.7.17)*

---

## 1.7.1 Frequency Analysis of Reactive Circuits

### The Core Idea

Capacitors and inductors are *linear* devices: the amplitude of the output waveform increases exactly in proportion to the input amplitude, regardless of waveshape. This linearity has one critical consequence:

> The output of a linear circuit, driven with a sinewave at some frequency f, is itself a sinewave at the same frequency (with, at most, changed amplitude and phase).

This is why analyzing circuits at a single frequency is useful — even though it's not always the intended use case. A graph of output/input amplitude ratio versus sinewave frequency is the *frequency response*.

**Example from the book:** A "boom box" loudspeaker has the frequency response shown in Figure 1.87. It is not flat over audible frequencies (20 Hz–20 kHz). A compensating passive filter with the inverse response can be inserted in the amplifier chain to flatten it.

### Capacitor Driven by a Sinewave (Starting Point)

Drive a capacitor with V(t) = V₀ sin ωt. Using I = C dV/dt:

```
I(t) = CωV₀ cos ωt
```

The current has amplitude ωCV₀ and leads the voltage by 90°. Ignoring phase and looking only at the ratio of magnitudes:

```
I = V / (1/ωC)
```

This behaves like a frequency-dependent resistance. The official name is *reactance*, symbol X. For a capacitor:

```
X_C = 1 / (ωC)      (eq. 1.26)
```

A larger capacitance has a smaller reactance — it takes twice as much current to charge and discharge it through the same voltage swing in the same time (I = C dV/dt). Increasing frequency also decreases reactance, because doubling frequency doubles the rate of voltage change, requiring twice the current.

**Key warning from the book:** Treating a capacitor as a frequency-dependent resistor is a useful simplification — but it ignores phase shifts. The book explicitly flags approximate equations with ≈ (not =). The correct treatment using complex algebra comes in §1.7.4–1.7.5.

### Terminology

- **Impedance (Z):** the generalized resistance — covers R, L, C and combinations. Z = R + jX.
- **Reactance (X):** the imaginary part of impedance — for pure capacitors and inductors only.
- **Resistance (R):** the real part; only resistors are purely resistive.

You often use the word "impedance" even when you mean resistance: "source impedance," "output impedance," "input impedance" — all refer to the Thévenin equivalent seen at those terminals.

---

## 1.7.2 Reactance of Inductors

Imagine an inductor L driven by a sinusoidal current source I(t) = I₀ sin ωt. The voltage across it is:

```
V(t) = L dI/dt = LωI₀ cos ωt
```

The ratio of magnitudes (reactance) is:

```
X_L = ωL      (eq. 1.29)
```

Inductor reactance *increases* with frequency — the opposite of capacitors. At low frequencies reactance is small (near-short); at high frequencies it is large (near-open).

**Where you see it:** A series inductor passes DC and low frequencies, blocks high frequencies. This is an *RF choke*. Used in power supply output stages to block switching noise from reaching the load while passing DC.

> **Embedded tie-in:** Ferrite beads on PCB power rails and IC supply pins are RF chokes. They are inductors with high loss at RF, preventing switching noise from one part of the board coupling into analog or RF sections.

---

## 1.7.3 Voltages and Currents as Complex Numbers

### Why Complex Numbers?

Phase shifts exist in reactive circuits. Writing out V(t) = 23.7 sin(377t + 0.38) everywhere is laborious. Complex numbers let you add and subtract phasors algebraically instead of with trig.

### The Rules

1. A sinewave V₀ cos(ωt + φ) is *represented* by the complex number **V** = V₀e^(jφ) = a + jb, where j = √−1.
2. The actual voltage is recovered by multiplying **V** by e^(jωt) and taking the real part: V(t) = Re(**V**e^(jωt)).

In other words:

```
circuit voltage V₀cos(ωt + φ)  ←→  complex number V₀e^(jφ)
                                     multiply by e^(jωt), take Re() to go back
```

**Example from the book:** A complex amplitude **V** = 5j corresponds to a real voltage:

```
V(t) = Re[5j cos ωt + 5j(j) sin ωt]
     = Re[5j cos ωt − 5 sin ωt]
     = −5 sin ωt  volts
```

**Why j specifically?** Electronics uses j (not i) to avoid confusion with the symbol i for small-signal current.

**Intuition:** Multiplying by j rotates a phasor 90° in the complex plane. Inductors and capacitors shift voltage and current by 90° — so j appears naturally in their impedance expressions.

---

## 1.7.4 Reactance of Capacitors and Inductors

### Correct Complex Analysis of a Capacitor

Apply V(t) = Re(V₀e^(jωt)) across a capacitor. Using I = C dV/dt:

```
I(t) = Re(V₀e^(jωt) / (−j/ωC))
```

So the impedance of a capacitor is:

```
Z_C = −j/ωC  (= −jX_C)      (eq. 1.32)
```

The magnitude is X_C = 1/ωC (the reactance we found approximately before), but the −j factor accounts for the 90° leading phase of current versus voltage.

**Example from the book:** A 1 μF capacitor has an impedance of −2653jΩ at 60 Hz and −0.16jΩ at 1 MHz. Its reactances are 2653 Ω and 0.16 Ω respectively.

### Inductor Impedance

```
Z_L = jωL  (= jX_L)
```

### Summary Table

| Component | Impedance Z | At DC (ω→0) | At high ω | Phase (I vs V) |
|-----------|-------------|-------------|-----------|----------------|
| Resistor  | R           | R           | R         | 0° (in phase)  |
| Capacitor | −j/ωC       | ∞ (open)    | 0 (short) | I leads V 90°  |
| Inductor  | jωL         | 0 (short)   | ∞ (open)  | I lags V 90°   |

A circuit with only capacitors and inductors has purely imaginary impedance — voltage and current are always 90° out of phase, and no real power is consumed.

---

## 1.7.5 Ohm's Law Generalized

With complex representations, Ohm's law becomes:

```
I = V/Z
V = IZ
```

where **V** and **I** are complex amplitudes. Series and parallel combination rules are identical to resistors:

```
Z_series   = Z₁ + Z₂ + Z₃ + ...           (eq. 1.30)
Z_parallel = 1 / (1/Z₁ + 1/Z₂ + 1/Z₃ + ...)    (eq. 1.31)
```

**Exercise 1.25** (from book): Use these rules to derive the series and parallel capacitance formulas (1.17 and 1.18). Hint: let each capacitor have impedance 1/jωC, find the combined impedance of the parallel or series combination, then equate it to the impedance of a single capacitor C.

**Example from the book:** 1 μF capacitor across a 115V rms, 60 Hz powerline.

```
Z = −j/ωC = −j/(2π × 60 × 10⁻⁶) ≈ −2653j Ω

V = 115√2 ≈ 163 V (peak)
I = V/Z = (163) / (−2653j) = j × 0.061 A

I(t) = −0.061 sin ωt A   (leads voltage by 90°)
```

Amplitude is 61 mA peak (43 mA rms), confirming the approximate calculation from §1.7.1.

**Exercise 1.26** (from book): Show that if **A** = **BC** then A = BC, where A, B, C are magnitudes. Hint: represent each in polar form.

---

## 1.7.6 Power in Reactive Circuits

### Instantaneous vs. Average Power

Instantaneous power delivered to any element is P = VI. But in reactive circuits V and I are not in phase, so you can't just multiply amplitudes.

**Example (capacitor alone):** During intervals A and C of a full sinewave cycle, power is positive (energy being stored). During B and D, power is negative (energy returned). The average over a full cycle is exactly zero. (See Figure 1.94 in the book.)

This is always true for any purely reactive element (capacitor, inductor, or any combination of them).

### Average Power Formula

```
P = (1/T) ∫₀ᵀ V(t)I(t) dt = Re(VI*)      (eq. 1.34)
```

where **V** and **I** are complex rms amplitudes and * denotes complex conjugate.

**Example — series RC circuit (Figure 1.95):**

```
Z = R − j/ωC
I = V₀ / Z = V₀ / (R − j/ωC)
P = Re(VI*) = V₀²R / (R² + 1/ω²C²)
```

The power dissipated depends on R only — the capacitor contributes zero net power.

### Power Factor

```
power factor = P / (|V||I|) = R / [R² + (1/ω²C²)]^(1/2)
```

Power factor equals cos(φ), where φ is the phase angle between voltage and current. It ranges from 0 (purely reactive) to 1 (purely resistive).

**Why it matters in practice:** Power companies charge industrial users according to power factor. Reactive currents don't deliver useful power but cause I²R heating in generators, transformers, and wiring. Large factories use capacitor banks to cancel the inductive reactance of motors, bringing power factor back toward 1.

**Exercise 1.27** (from book): Prove that a circuit whose current is 90° out of phase with the driving voltage consumes no power averaged over a full cycle.

**Exercise 1.28** (from book): For a 1 μF capacitor and 1.0k resistor in series across the 115V, 60 Hz powerline, compute power using V²_R/R. What is the power in watts?

**Exercise 1.29** (from book): Show that adding a series capacitor C = 1/ω²L makes the power factor equal to 1 in a series RL circuit. Do the same for the parallel case.

---

## 1.7.7 Voltage Dividers Generalized

The resistive voltage divider (§1.2.5) generalizes directly. Replace either or both resistors with arbitrary impedances Z₁ (series), Z₂ (shunt):

```
V_out = V_in × Z₂ / (Z₁ + Z₂)      (Figure 1.96)
```

The analysis is straightforward: total current I = V_in / Z_total, output voltage V_out = I × Z₂.

**What changes:** The division ratio is now complex and frequency-dependent. Magnitude gives the amplitude ratio; angle gives the phase shift. This is the foundation for all RC and LC filter analysis.

---

## 1.7.8 RC Highpass Filters

### Circuit: C in series, R to ground (Figure 1.92)

Using complex Ohm's law (correcting the approximate analysis from §1.7.1):

```
V_out = V_in × R / (R − j/ωC)
      = V_in × R(R + j/ωC) / (R² + 1/ω²C²)
```

Taking the magnitude only:

```
|V_out/V_in| = R / [R² + (1/ω²C²)]^(1/2)
             = 2πfRC / [1 + (2πfRC)²]^(1/2)      (eq. 1.35)
```

The −3 dB breakpoint (output = 1/√2 of input) is:

```
f_3dB = 1 / (2πRC)
```

**Behavior:**
- f >> f_3dB: |Z_C| << R, output ≈ input (capacitor is a near-short)
- f = f_3dB: output = 0.707 × input, phase = +45°
- f << f_3dB: |Z_C| >> R, output → 0 (capacitor dominates denominator)

The phase goes smoothly from +90° at ω = 0, through +45° at ω₃dB, to 0° at ω = ∞ (Figure 1.99).

**Note on the approximate formula:** The approximate result from §1.7.1 was V_out/V_in ≈ ωRC/(1 + ωRC). This is accurate at both extremes but modestly wrong near the crossover — it gives 0.5 where the exact result is 1/√2 ≈ 0.7 (Figure 1.91). The approximate formula is still adequate for blocking-capacitor design where the signal band is fully in the passband.

### Driving and Loading RC Filters

The impedance of a capacitor is the same as its reactance in magnitude. A signal source's impedance should be small compared to what it drives. For RC filters, the worst-case input impedance (hardest to drive) and worst-case output impedance (hardest to load) are both equal to R.

> **Exercise 1.23** (from book): Show that the preceding statement is correct.

**Practical rule:** To hang an RC lowpass filter on an amplifier output with 100Ω source resistance, start with R = 1k. Choose C for the breakpoint you want. Ensure the load has input impedance ≥ 10k.

> **Exercise 1.24** (from book): Design a two-stage "bandpass" RC filter — first stage is highpass at 100 Hz, second is lowpass at 10 kHz. Assume the signal source has 100Ω impedance. What is the worst-case output impedance? Minimum recommended load impedance?

### C. Blocking Capacitor

A highpass filter is used as a *blocking capacitor* (or *dc blocking capacitor*) when you choose the crossover frequency below all frequencies of interest. The capacitor blocks DC and any slow drift; the signal band is fully in the passband.

**Example:** Every stereo audio amplifier input is AC coupled. Pick R and C so all frequencies 20 Hz–20 kHz pass. Choose RC > 1/ω_min, i.e., τ = RC >> 1/(2π × 20) ≈ 8 ms. Common choice: R = 10 kΩ, C = 3.3 μF → f_3dB = 1/(2π × 10k × 3.3μ) ≈ 5 Hz (Figure 1.93).

**Practical constraint:** Input resistance R must be large enough not to load the driving stage, but small enough to be practical. 10 kΩ is common in audio. The driving circuit must handle a 10 kΩ load.

**Time-domain view:** When passing pulses or square waves through a blocking capacitor, use τ = RC >> T (pulse duration) to avoid "droop" and overshoot.

### Reactance Chart (Figure 1.100)

The book provides a log-log chart of |Z_C| = 1/(2πfC) versus frequency for standard capacitor values. All decades are identical in shape; the chart covers standard E6 component values. Use it to read off reactance at a glance for filter design.

> **Embedded tie-in:** AC coupling between amplifier stages, removing DC offset from sensor signals, UART/SPI signal coupling in isolated interfaces, oscilloscope "AC coupling" switch (highpass at ~10 Hz).

---

## 1.7.9 RC Lowpass Filters

### Circuit: R in series, C to ground (Figure 1.102)

Interchanging R and C in the highpass gives the lowpass. Exact analysis:

```
|V_out/V_in| = 1 / (1 + ω²R²C²)^(1/2)      (eq. 1.36)
```

The 3 dB point is again f = 1/(2πRC) (Figure 1.103).

**Log-log response (Figure 1.104):**
- Flat at 1 for f << f_3dB
- −3 dB at f_3dB, phase = −45°
- −6 dB/octave (= −20 dB/decade) rolloff above f_3dB
- Phase goes from 0° at low f, through −45° at f_3dB, to −90° at high f
- Rule of thumb: phase is within 6° of its asymptotic value at 0.1f_3dB and at 10f_3dB

**Output impedance:** At low frequencies the filter output looks like R (capacitor is high impedance). At high frequencies it looks like zero (capacitor dominates, signal is attenuated). Worst-case source and load impedances of an RC filter (lowpass or highpass) are both equal to R.

**Exercise 1.30** (from book): Show that the preceding expression for the response of an RC lowpass filter is correct.

**Exercise 1.31** (from book): Prove that the phase is within 6° of its asymptotic value at 0.1f_3dB and at 10f_3dB.

**Can you independently specify amplitude and phase response?** No. Causality forces a relationship between them for realizable analog filters — this is the Kramers–Kronig relation.

**Multistage caution:** You cannot simply cascade identical RC sections and concatenate their responses. Each stage loads the previous one significantly. Solution: use op-amp buffers between stages (Chapters 2–4), or make each successive section have much higher impedance than the preceding one.

> **Embedded tie-in:** Anti-aliasing before ADC (set f_3dB at or below Nyquist), power supply ripple filtering, EMI suppression on I/O lines, RFI rejection on audio amplifier inputs (0.5–800 MHz interference from radio/TV stations).

---

## 1.7.10 RC Differentiators and Integrators in the Frequency Domain

The RC differentiator (§1.4.3) is exactly the same circuit as the RC highpass filter. The time-domain condition for proper differentiation (dV_out << dV_in) is equivalent to saying that all signal frequencies must be well below the 3 dB point.

**Check:** For V_in = sin ωt, the differentiator gives V_out = RC × d/dt(sin ωt) = ωRC cos ωt. If ωRC << 1, V_out is small compared to V_in. If the input has a range of frequencies, all must satisfy this condition — i.e., all must be well below f_3dB.

Similarly, the RC integrator (§1.4.4) is the same circuit as the lowpass filter. Good integration requires all signal frequencies well above the 3 dB point.

| Time domain     | Frequency domain  | Condition                      |
|-----------------|-------------------|--------------------------------|
| Differentiator  | Highpass filter   | Signal frequencies << f_3dB   |
| Integrator      | Lowpass filter    | Signal frequencies >> f_3dB   |

---

## 1.7.11 Inductors versus Capacitors

Instead of capacitors, inductors can make lowpass or highpass filters with resistors (RL filters). In practice, RL filters are rare. Inductors are bulkier, more expensive, and depart further from ideal (they have DCR, can saturate, and have worse high-frequency behavior than capacitors — see Chapter 1x).

**Rule:** If you have a choice, use a capacitor.

**One important exception:** Ferrite beads and RF chokes. These are inductors strung in series on wire or PCB traces. A few beads raise the impedance at very high frequencies, preventing oscillations, without adding series resistance (as an RC filter would). They are essential for suppressing parasitic oscillations at hundreds of MHz.

**Inductors are essential in two cases:**
1. LC tuned circuits (§1.7.14) — RC cannot achieve high Q
2. Switch-mode power converters (§9.6.4) — inductors store and release energy efficiently

---

## 1.7.12 Phasor Diagrams

A phasor diagram is a graphical method for visualizing phase relationships in reactive circuits.

**Example — RC lowpass at the −3 dB point (Figure 1.105A):**

At f = 1/(2πRC), the capacitor's reactance equals R. Draw the impedance on the complex plane: the real axis has length R, the imaginary axis has length −j/ωC = −jR. The total impedance **Z** = R − jR is the hypotenuse (length R√2). The output voltage (across C only) is proportional to the imaginary leg; the input voltage is proportional to the hypotenuse. The ratio is R/(R√2) = 1/√2, confirming the −3 dB result. The angle between vectors is 45° — this is the phase shift.

**Compare with a resistive divider (Figure 1.105B):** Two equal resistors give −6 dB (factor of 2), not −3 dB. The difference is because with a capacitor at −3 dB, the two impedances are at right angles, not in line — the total is R√2, not 2R.

**Exercise 1.32** (from book): Use a phasor diagram to derive the response of an RC highpass filter: V_out = V_in × R / √(R² + 1/ω²C²).

**Exercise 1.33** (from book): At what frequency does an RC lowpass filter attenuate by 6 dB (output = half the input)? What is the phase shift at that frequency?

**Exercise 1.34** (from book): Use a phasor diagram to obtain the lowpass filter response previously derived algebraically.

> In §2.2.8 the book shows a practical application of phasor diagrams: a constant-amplitude phase-shifting circuit.

---

## 1.7.13 "Poles" and Decibels per Octave

Far above the "knee" of the RC lowpass response, output amplitude drops proportionally to 1/f. In one octave (frequency doubles), the output halves: −6 dB per octave. Equivalently: −20 dB per decade.

A simple RC filter has **one pole** — one RC time constant. Each additional RC section adds one more pole:

| Number of poles | Rolloff above cutoff       |
|-----------------|---------------------------|
| 1 (one RC)      | −6 dB/octave = −20 dB/decade |
| 2 (two RC)      | −12 dB/octave = −40 dB/decade |
| 3 (three RC)    | −18 dB/octave = −60 dB/decade |

A "three-pole filter" means three RC sections (or a filter that behaves like one). The word "pole" comes from analysis of transfer functions in the complex frequency plane (the "s-plane") — discussed in Chapter 1x.

**Caution on cascading identical sections:** you cannot just cascade identical RC sections because each loads the previous. Use op-amp buffers or make each stage much higher impedance.

---

## 1.7.14 Resonant Circuits

Combining capacitors with inductors (or using active filters) enables much sharper frequency selectivity than RC alone.

### A. Parallel and Series LC Circuits

**Parallel LC (tank circuit, Figure 1.106):**

The impedance of the parallel LC combination is:

```
1/Z_LC = 1/Z_L + 1/Z_C = 1/jωL − ωC/j = j(ωC − 1/ωL)

Z_LC = j / (1/ωL − ωC)    (parallel LC)
```

As ω → ω₀ = 1/√LC, the denominator → 0 and **Z_LC → ∞**. In combination with series resistance R, this forms a voltage divider with a peak in V_out/V_in at resonance (Figure 1.107).

**Resonant frequency:**

```
f₀ = 1 / (2π√LC)      (eq. 1.37)
```

In the time domain, the parallel LC ring is a damped oscillation — after a voltage step or pulse, the circuit oscillates at f₀ with amplitude decaying as losses in R remove energy.

**Quality factor Q:**

```
Q = f₀ / Δf_3dB   (bandwidth definition)
Q = ω₀RC          (for parallel RLC, eq. 1.46-equivalent)
```

Q measures sharpness of resonance. Q = 20 means the −3 dB bandwidth is f₀/20. In the time domain, a parallel LC with Q = 20 oscillates for Q/π ≈ 6 cycles before falling to 1/e of its initial amplitude.

**Series LC (trap, Figure 1.108):**

At resonance the series LC impedance goes to zero (short circuit), shorting the output to ground. This is a *notch* (trap) — it rejects a specific frequency. The Q of a series RLC circuit is:

```
Q = ω₀L / R   (series RLC)
```

Figure 1.109 shows the sharp phase and amplitude changes at resonance for the series trap.

**Figure 1.110** shows response curves for tank (dotted) and trap (solid) circuits at Q = 1, 3, 10.

**Exercise 1.35** (from book): Find the response (V_out/V_in vs. frequency) for the series LC trap circuit in Figure 1.108.

### LC versus RC for Selectivity

LC resonant circuits are not unique in providing high Q. Alternatives with even higher Q exist: quartz-crystal resonators, ceramic resonators, surface acoustic wave (SAW) devices, transmission lines, and resonant cavities.

**Time vs. frequency domain for LC:** In the frequency domain, Q is the ratio of f₀ to bandwidth. In the time domain (radians), energy falls to 1/e in Q radians; voltage falls to 1/e in 2Q radians. Think in whichever domain is cleaner for the problem at hand.

> **Embedded tie-in:** Parallel LC tanks appear in RF transmitters and receivers for frequency selection. Crystal oscillators use quartz resonators (Q up to 10⁶) to set microcontroller and communication clocks. SAW filters appear in mobile phone front ends.

---

## 1.7.15 LC Filters

Combining inductors with capacitors produces lowpass, highpass, and bandpass filters with far sharper rolloff than any RC or cascaded RC combination.

**Example from the book (Figure 1.111):** A "mixer-digitizer" circuit board for a 250-million-channel radio receiver. Six LC lowpass filters on the board, each comprising three inductors (square metal cans) and four capacitors, designed to cut off at 1.0 MHz. These prevent aliases in the digitized output.

**Figure 1.112** shows a frequency sweep comparison: the 7-section LC lowpass versus an RC lowpass, both with 1 MHz cutoff. The LC filter achieves a sharp cutoff the RC cannot approach. As the book notes: "The RC is pathetic by comparison. It's not even good English to call 1 MHz its 'cutoff': it hardly cuts anything off."

**Trade-off:**

| RC Filter            | LC Filter                         |
|----------------------|-----------------------------------|
| Simple, cheap        | Inductors bulky, expensive        |
| Adequate for audio   | Essential for RF and power        |
| No saturation issues | Inductors can saturate            |
| Low Q (max ~0.5)     | High Q achievable                 |

Chapter 6 and Appendix E cover LC filter design in detail.

---

## 1.7.16 Other Capacitor Applications

Beyond filters and resonant circuits, capacitors serve several other important roles. These are previewed here; detail appears in later chapters.

### A. Bypassing

A capacitor's impedance decreases with increasing frequency. Place a capacitor across a circuit element (usually a resistor) where you want DC to pass but signals to be shorted. Choose C so its impedance at the lowest signal frequency of concern is small compared to what it is bypassing.

> **Embedded tie-in:** 100 nF ceramic capacitor on every IC VDD pin. Its impedance at 10 MHz is ~1.6 Ω, far less than the supply rail resistance — it shunts high-frequency switching noise to ground locally, before it can propagate.

### B. Power-Supply Filtering

The large electrolytic capacitors after a rectifier circuit are *storage capacitors* (the book prefers this term over "filter capacitor"). They store charge to reduce ripple on the DC rail. Covered in detail in Chapter 9.

### C. Timing and Waveform Generation

A capacitor charged by a constant current produces a linear ramp. This is the basis of:
- Ramp and sawtooth generators
- Oscilloscope sweep circuits
- Analog-to-digital converters (ADC sample windows)
- RC timing circuits (monostable multivibrators, 555 timer)
- Delay circuits

Covered in Chapters 3, 6, 10, and 11.

> **Embedded tie-in:** 555 timer and RC oscillators set timing in simple microcontroller-free circuits. In ADC front ends, a capacitor charges to the input voltage during sampling and holds it while the converter runs — capacitor dielectric absorption and leakage directly limit ADC accuracy.

---

## 1.7.17 Thévenin's Theorem Generalized

Thévenin's theorem extends to circuits containing capacitors and inductors. The generalized statement:

> Any two-terminal network of resistors, capacitors, inductors, and signal sources is equivalent to a single complex impedance in series with a single signal source.

You find the (complex) impedance and the signal source waveform from:
- **Z_Th:** the complex impedance seen at the terminals with all independent sources killed (voltage sources shorted, current sources opened)
- **V_Th:** the open-circuit output voltage (a phasor, frequency-dependent)

The procedure is identical to the resistor-only case, using complex impedance arithmetic.

**Practical consequence:** A filter's output impedance varies with frequency. The worst-case output impedance of an RC filter is R (§1.7.1D). When cascading stages, always consider loading — the next stage's input impedance should be much larger than the driving stage's output impedance at all frequencies of interest. Op-amp buffers solve this (Chapters 2–4).

> **Example application — AM radio (§1.8):** The parallel LC tank in a crystal-set radio is tuned to the carrier frequency by a variable capacitor C₁. The Thévenin equivalent of this tuned circuit is then the input to the detector diode. The tank's output impedance at resonance (very high) determines how much the diode loads the circuit.
