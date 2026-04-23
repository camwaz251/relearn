# Ch. 1.3 — Signals
*Art of Electronics, pp. 13–18 (§1.3.1–1.3.5)*

---

## 1.3.1 Sinusoidal Signals

### What they are

The fundamental AC waveform. Every periodic signal can be decomposed into sinusoids (Fourier's theorem). Linear circuits preserve sine shapes — a sine in always gives a sine out at the same frequency, possibly with different amplitude and phase. This is why frequency-domain analysis works.

**The math:**
```
V(t) = A * sin(2πft + φ)
     = A * sin(ωt + φ)

ω = 2πf          (angular frequency, rad/s)
f = 1/T           (frequency in Hz, T = period in seconds)
```

**Key amplitude measures:**
```
V_rms = V_peak / √2 ≈ 0.707 * V_peak    (sinewaves only)
V_pp  = 2 * V_peak
```

**Intuition:** V_rms is the DC-equivalent for power dissipation. A 1V_rms sinewave dissipates the same power in a resistor as 1V DC. US mains: 120V_rms = 170V_peak, 60Hz. European mains: 230V_rms = 325V_peak, 50Hz.

---

## 1.3.2 Signal Amplitudes and Decibels

### Decibels

**What they are:** Logarithmic ratios for comparing signal levels. Used because circuits span many orders of magnitude, and human perception (hearing, vision) is logarithmic.

**The math:**
```
dB = 10 * log₁₀(P2/P1)     (power ratio)
dB = 20 * log₁₀(A2/A1)     (amplitude/voltage ratio)
```
The factor of 20 (not 10) for voltage comes from P ∝ V², so log(V²) = 2·log(V).

**Landmarks to memorize:**

| dB  | Voltage ratio | Power ratio | Memory hook         |
|-----|--------------|-------------|---------------------|
| 0   | 1×           | 1×          | No change           |
| 3   | 1.41× (√2)   | 2×          | Double power        |
| 6   | 2×           | 4×          | Double voltage      |
| 10  | 3.16×        | 10×         | Decade in power     |
| 20  | 10×          | 100×        | Decade in voltage   |
| -3  | 0.707×       | 0.5×        | Half power (cutoff) |
| -20 | 0.1×         | 0.01×       |                     |

**Intuition:** Only memorize +3, +6, +20. Everything else is addition:
- +26dB = +20 + 6 = 10× × 2× = 20× voltage
- +23dB = +20 + 3 = 10× × √2 ≈ 14× voltage
- -6dB = half voltage = quarter power

**Where you see it:** Filter rolloff specs (−3dB cutoff, −20dB/decade), amplifier gain, antenna gain, audio levels, cable attenuation, ADC dynamic range (each bit ≈ 6dB).

### dBm and Absolute References

**dBm** = dB relative to 1mW into 50Ω. The standard in RF work.
- 0dBm = 1mW = 223mV_rms into 50Ω
- +30dBm = 1W
- −10dBm = 100μW (typical RF signal generator output level)

---

## 1.3.3 Other Signal Types

### Square Waves
Alternates between two fixed levels. V_rms = V_peak (not V_peak/√2 — the √2 is for sinewave only). Rise time (10% to 90% transition) defines the bandwidth content. A fast edge contains high-frequency harmonics — this is why fast digital signals cause EMI.

### Triangle and Ramp Waves
Sweep circuits, sawtooth oscillators. V_rms = V_peak/√3 for triangle wave.

### Noise
Random thermal fluctuations. Every resistor generates Johnson noise:
```
V_noise_rms = √(4kTRB)      k = 1.38×10⁻²³ J/K, T in Kelvin, B = bandwidth
```
At room temp, 1kΩ in 1MHz bandwidth: ≈4μV_rms. Can't be eliminated, only minimized by reducing R, T, or B.

### Pulses
Characterized by amplitude, width, repetition rate, duty cycle. Duty cycle = t_on / T_period. Average value = V_high × duty cycle.

> **Embedded tie-in:** PWM is a fixed-amplitude pulse train with variable duty cycle. The "signal" is the average value, recoverable with a lowpass filter. UART idle is HIGH; start bit is a LOW pulse. I2C SDA/SCL are open-drain — the "signal" depends on which device is pulling low, with the pull-up resistor determining the HIGH level.

---

## 1.3.4 Logic Levels

### What they are
Digital circuits use predefined voltage windows for HIGH (1) and LOW (0). The gap between guaranteed output levels and required input thresholds is the **noise margin** — the amount of corruption the signal can tolerate.

**Example — 3.3V LVCMOS:**
```
V_OH (output high, min): 2.4V
V_OL (output low, max):  0.4V
V_IH (input high, min):  1.5V
V_IL (input low, max):   0.8V

Noise margin HIGH = V_OH_min - V_IH_min = 2.4 - 1.5 = 0.9V
Noise margin LOW  = V_IL_max - V_OL_max = 0.8 - 0.4 = 0.4V
```

**Intuition:** The output window is always *inside* the input window — this gives margin for noise on the line. A 5V signal driving a 3.3V input violates V_IH max and can damage the input or latch up the chip.

> **Embedded tie-in:** Level shifting between 3.3V and 5V logic requires either resistor dividers (unidirectional, slow), dedicated level shifter ICs, or open-drain + pull-up to the target voltage. The STM32 accepts 5V-tolerant inputs on certain pins — check the datasheet pin-by-pin.

---

## 1.3.5 Signal Sources

### Thévenin Model of a Signal Source

Every real signal source has an output impedance R_out (its Thévenin resistance). The signal it delivers to a load depends on the voltage divider formed by R_out and R_load.

**Intuition:** A function generator with 50Ω output impedance connected to a 50Ω load delivers half its open-circuit voltage. The same generator driving a 10kΩ scope probe delivers ~99.5% of its open-circuit voltage. For signal fidelity, you want R_load >> R_source. For power transfer, you want them equal.

**Common source impedances:**
- Function generator output: 50Ω
- Op-amp output: <1Ω to ~100Ω
- Microphone (dynamic): 150–600Ω
- Microphone (condenser): 200Ω with phantom power
- ADC input (sample-and-hold): 1k–10kΩ during acquisition
