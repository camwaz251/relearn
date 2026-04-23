# Ch. 1.7 — Impedance and Reactance
*Art of Electronics, pp. 40–55 (§1.7.1–1.7.17)*

---

## 1.7.1 Frequency Analysis of Reactive Circuits

### Why Frequency Domain

Time-domain analysis (exponential charge/discharge) gets complicated fast for anything beyond simple RC. Frequency domain trades this for a simpler algebraic approach: replace derivatives with multiplication by jω. Sinusoidal steady-state only — but that covers most of what you care about.

**Key insight:** Drive any linear circuit with a sinewave, and every voltage and current in the circuit is also a sinewave at the same frequency, possibly with different amplitude and phase. Impedance captures both the amplitude ratio and phase shift.

---

## 1.7.2 Reactance of Inductors

**The math:**
```
X_L = ωL = 2πfL         (inductive reactance, in ohms)
```

Reactance increases with frequency. At DC (f=0): X_L = 0 → short. At high frequency: X_L → ∞ → open. This is why inductors are used as RF chokes — they block high-frequency signals while passing DC.

---

## 1.7.3 Voltages and Currents as Complex Numbers (Phasors)

### Phasor Representation

A sinewave A·sin(ωt + φ) is represented as a complex number (phasor) A∠φ = A·e^(jφ).

**Intuition:** The phasor captures amplitude and phase in one number. The actual voltage is the real part of the phasor rotating in the complex plane at frequency ω. We do the algebra with complex numbers, then take the real part at the end.

**Why j?** Multiplying by j rotates a phasor 90° in the complex plane. Inductors and capacitors produce 90° phase shifts between voltage and current — hence j appears naturally in their impedances.

---

## 1.7.4 Reactance of Capacitors and Inductors

**The math:**
```
Z_C = 1/(jωC) = -j/(ωC)       (capacitive impedance)
Z_L = jωL                       (inductive impedance)

Magnitudes (reactance):
|Z_C| = X_C = 1/(ωC) = 1/(2πfC)    (decreases with f)
|Z_L| = X_L = ωL = 2πfL             (increases with f)
```

**Intuition table:**

| Component | At DC (f→0) | At high f | Phase (V vs I) |
|-----------|------------|-----------|----------------|
| Resistor  | R          | R         | 0° (in phase)  |
| Capacitor | ∞ (open)   | 0 (short) | −90° (I leads V)|
| Inductor  | 0 (short)  | ∞ (open)  | +90° (V leads I)|

Memory: **ELI the ICE man** — in an **L** (inductor), **E** (voltage) leads **I** (current). In a **C** (capacitor), **I** leads **E**.

---

## 1.7.5 Ohm's Law Generalized

```
V = I * Z        (exactly Ohm's law, but Z is complex)
```

Series and parallel combination rules work identically to resistors, using complex arithmetic. This is the power of impedance: one framework handles R, L, C, and any combination.

---

## 1.7.6 Power in Reactive Circuits

### Real and Reactive Power

```
P_real = V_rms * I_rms * cos(φ)       (watts — actual energy dissipated)
P_reactive = V_rms * I_rms * sin(φ)   (VAR — energy stored/returned)
Power factor = cos(φ)
```

**Intuition:** A purely reactive component (cap or inductor alone) has φ = 90°, so cos(90°) = 0. Power is exchanged back and forth but no net energy is consumed. This is why reactive components don't heat up (ideally). Real inductors and capacitors have some resistance (ESR, DCR) — that's where the actual power is dissipated.

**Where you see it:** Power factor correction in industrial equipment (motors are inductive loads). Power companies charge for apparent power (VA), not real power (W), so a poor power factor costs money.

---

## 1.7.7 Voltage Dividers Generalized

The voltage divider formula works for any impedances:
```
V_out = V_in * Z2 / (Z1 + Z2)
```

Z1 and Z2 can be any combination of R, L, C. The result is a complex number — magnitude is the amplitude ratio, angle is the phase shift. This is the foundation for all filter analysis.

---

## 1.7.8 RC Highpass Filter

### Circuit: C in series, R to ground

**The math:**
```
V_out/V_in = jωRC / (1 + jωRC)

|V_out/V_in| = ωRC / √(1 + (ωRC)²)

f_3dB = 1/(2πRC)       (output = 0.707 × input, phase = +45°)
```

**Behavior:**
- f << f_3dB: cap is high impedance, signal attenuated (cap blocks low frequencies and DC)
- f = f_3dB: output = −3dB (0.707×), phase shifted +45°
- f >> f_3dB: cap is low impedance, signal passes (−20dB/decade rolloff below f_3dB)

**Where you see it:** AC coupling between amplifier stages, removing DC offset from sensor signals, audio tone control (bass cut), UART/serial line coupling.

---

## 1.7.9 RC Lowpass Filter

### Circuit: R in series, C to ground

**The math:**
```
V_out/V_in = 1 / (1 + jωRC)

|V_out/V_in| = 1 / √(1 + (ωRC)²)

f_3dB = 1/(2πRC)       (same formula as highpass)
```

**Behavior:**
- f << f_3dB: output ≈ input (cap is high impedance, all voltage at output)
- f = f_3dB: output = −3dB, phase = −45°
- f >> f_3dB: cap short-circuits output (−20dB/decade rolloff above f_3dB)

**Where you see it:** Anti-aliasing filter before ADC input, power supply ripple filtering, EMI filtering on I/O lines, debouncing noisy switch signals.

> **Embedded tie-in:** Anti-aliasing: set f_3dB to half the ADC sample rate (Nyquist) or below. For a 100kSPS ADC, f_3dB ≤ 50kHz. With R=10kΩ, C = 1/(2π × 50k × 10k) ≈ 330pF.

---

## 1.7.10 RC Differentiators and Integrators in the Frequency Domain

**Time domain ↔ Frequency domain connection:**

| Time domain | Frequency domain |
|------------|-----------------|
| Differentiator (C series, R to gnd) | Highpass filter |
| Integrator (R series, C to gnd) | Lowpass filter |

Same circuits — different ways to think about them. Time domain is useful for pulse/step inputs. Frequency domain is useful for sinusoidal/periodic inputs.

---

## 1.7.11 Inductors versus Capacitors

**Duality:**

| Capacitor | Inductor |
|-----------|----------|
| V = Q/C | V = L·dI/dt |
| I = C·dV/dt | I = ∫V dt / L |
| Open at DC | Short at DC |
| Short at high f | Open at high f |
| Stores energy in E field | Stores energy in B field |
| Combines in parallel (adds) | Combines in series (adds) |

**When to use which:** Capacitors for bypassing and coupling (cheap, compact, no saturation). Inductors for energy storage in switching supplies, high-power filtering, and RF resonance (but bulky, more expensive, can saturate).

---

## 1.7.12 Phasor Diagrams

A graphical way to visualize phase relationships. Voltage and current phasors are arrows rotating in the complex plane. Resistor current is in phase with voltage. Capacitor current leads by 90°. Inductor current lags by 90°. Used to analyze power factor and filter phase response visually.

---

## 1.7.13 "Poles" and Decibels per Octave

**A "pole"** is one RC (or LC) time constant in a filter. Each pole contributes:
- −20 dB/decade rolloff in the stopband
- −6 dB/octave (doubling frequency = halving voltage)
- 45° phase shift at the corner frequency, 90° total asymptotic shift

A two-pole filter rolls off at −40 dB/decade. More poles = sharper cutoff.

**Intuition:** The book uses "poles" and "decibels per octave" interchangeably with decades because they measure the same rolloff — one in frequency-doubled steps, the other in frequency-×10 steps. 6dB/octave = 20dB/decade.

---

## 1.7.14 Resonant Circuits (LC)

### Series LC (Trap)
At resonance, X_L = X_C, they cancel. Net impedance → 0 (short circuit). Used to block a specific frequency.

### Parallel LC (Tank)
At resonance, X_L = X_C, circulating current between L and C is large, but the impedance looking in from outside → ∞ (open circuit). Used to select a specific frequency.

**The math:**
```
f_0 = 1/(2π√LC)             (resonant frequency)

Q = ω_0 * L / R             (series LC quality factor)
Q = R / (ω_0 * L)           (parallel LC quality factor)
Q = f_0 / Δf_3dB            (bandwidth relationship)
```

**Intuition:** Q is the sharpness of resonance — higher Q = narrower peak = more selective. A Q of 100 means the −3dB bandwidth is f_0/100. LC filters achieve much higher Q than RC filters (which are limited to Q = 0.5 for second order). This is why LC circuits are used in radio tuning.

---

## 1.7.15 LC Filters

LC lowpass filters achieve much sharper rolloff than RC:
- 2nd-order LC: −40dB/decade (vs. RC −20dB/decade)
- Can achieve very high Q (sharp transition from passband to stopband)
- Used in power supply output filters, RF bandpass filters

**Trade-off:** Inductors are larger, more expensive, and have imperfections (DCR, saturation). RC filters are simpler and cheaper for audio/signal conditioning. LC is preferred for power filtering and RF.

---

## 1.7.16 Other Capacitor Applications

**Bypassing:** 100nF ceramic on every VDD pin. Looks like a short at switching frequencies, shunts noise to ground.

**Power-supply filtering:** Large electrolytic after rectifier. Stores charge to reduce ripple.

**Timing:** With a resistor, sets the time constant for oscillators (555 timer), delay circuits, ADC sample windows.

**Coupling (AC coupling):** Series cap blocks DC, passes AC. Sets the lowpass filter.

**Sample and hold:** In ADC front ends, a cap charges to the input voltage during sample phase, holds it during conversion. Cap quality (dielectric absorption, leakage) matters.

---

## 1.7.17 Thévenin's Theorem Generalized

When L and C are present, Thévenin still applies — but V_Th and Z_Th are now complex and frequency-dependent.

```
V_Th = V_open_circuit (phasor)
Z_Th = complex impedance looking into the terminals with sources killed
```

**Finding Z_Th:** Kill all independent sources (short voltage sources, open current sources). Compute the impedance of the remaining R, L, C network. This is the same procedure as with resistors — just using complex impedance.

**Intuition:** Every signal source at every frequency has a Thévenin equivalent. An amplifier's output impedance varies with frequency. A filter's output impedance determines how much it is loaded by the next stage. Always consider loading when cascading filter stages.
