# Ch. 1.3 — Signals
*Art of Electronics, pp. 13–18 (§1.3.1–1.3.5)*

---

## 1.3.1 Sinusoidal Signals

### What they are

The most popular signals in electronics — what you get out of the wall plug. If someone says "take a 10μV signal at 1MHz," they mean a sinewave. Described mathematically as:

```
V = A sin(2πft)         (eq. 1.10)

A = amplitude
f = frequency in Hz (cycles per second)
```

When you need to specify the value at t = 0, add a phase:

```
V = A sin(2πft + φ)
```

The angular frequency form (equivalent, just cleaner in calculus):

```
V = A sin(ωt)

ω = 2πf     (radians per second)
```

Just remember ω = 2πf and you won't go wrong.

**Why sinewaves matter:** A linear circuit driven by a sinewave always responds with a sinewave — same frequency, possibly different amplitude and phase. No other periodic signal has this property. This is why circuits are described by their *frequency response*: how the circuit changes the amplitude of an applied sinewave as a function of frequency. A stereo amplifier should have a flat frequency response from 20 Hz to 20 kHz.

**Intuition:** Sinewaves are the eigenfunctions of linear systems. Feed a sine in, get a sine out. Everything else (squares, ramps, pulses) is a sum of sinewaves — which is why Fourier analysis works.

**Frequency ranges in practice:**
- Typical electronics: a few Hz to a few tens of MHz
- Down to 0.0001 Hz or lower with carefully built circuits
- Up to ~2 GHz with special techniques; above that you're in microwave territory (waveguides, striplines)

**Where you see it in real hardware:** AC mains (US: 120V_rms, 60Hz, amplitude = 170V; Europe: 230V_rms, 50Hz, amplitude = 325V). Audio signals. RF carriers. Clock signals (approximately).

> **Embedded tie-in:** The rms value matters for power calculations. V_rms = A/√2 ≈ 0.707A for a sinewave. This is the DC-equivalent for heating — a 1V_rms sine dissipates the same power in a resistor as 1V DC. ADC inputs see the rms value when measuring AC signals.

---

## 1.3.2 Signal Amplitudes and Decibels

### Amplitude measures

Three ways to characterize amplitude:

```
Peak-to-peak (pp):   V_pp = 2A
RMS:                 V_rms = A / √2 = 0.707 A     (sinewaves only)
```

RMS is the standard for power calculations. It is what a true-rms meter reads. For non-sinewave signals, the rms/peak ratio is different — using the sinewave formula on a square wave gives the wrong answer (use a true-rms meter).

### Decibels

**What they are:** Logarithmic ratios for comparing signal levels. Named after Alexander Graham Bell; the decibel (dB) is one-tenth of a bel. Used because signal ratios routinely span many orders of magnitude.

**The math:**

```
dB = 10 log₁₀(P₂ / P₁)       (eq. 1.11 — power ratio)
dB = 20 log₁₀(A₂ / A₁)       (eq. 1.12 — amplitude/voltage ratio)
```

The factor of 20 vs. 10: power is proportional to voltage squared, so log(V²) = 2 log(V).

**Key landmarks:**

| dB  | Power ratio | Voltage ratio | Notes                    |
|-----|-------------|--------------|--------------------------|
| 0   | 1×          | 1×           | no change                |
| 3   | 2×          | 1.41× (√2)  | double power             |
| 6   | 4×          | 2×           | double voltage           |
| 10  | 10×         | 3.16×        | decade in power          |
| 20  | 100×        | 10×          | decade in voltage        |
| -3  | 0.5×        | 0.707×       | half power (−3dB cutoff) |
| -20 | 0.01×       | 0.1×         |                          |

**Intuition:** Only memorize +3, +6, +20. Combine by addition:
- +26 dB = 20 + 6 → 10× × 2× = 20× voltage
- +23 dB = 20 + 3 → 10× × √2 ≈ 14× voltage
- −6 dB = half voltage, quarter power

> **Exercise 1.12** (from book): Find voltage and power ratios for (a) 3 dB, (b) 6 dB, (c) 10 dB, (d) 20 dB.

> **Exercise 1.13 — "Desert Island dBs":** Fill in the table of power ratios for 0–11 dB without a calculator. Hint: start at 10 dB, go down in steps of 3 dB, then back up. Replace 3.125 and relatives with π.

### Absolute dB references

Decibels alone are ratios. To express an absolute level, you specify the reference:

- **dBV** — 0 dBV = 1 V rms. Common in audio line-level work.
- **dBm** — 0 dBm = 1 mW into a specified load impedance. For RF: 50Ω (so 0 dBm = 0.22 V rms). For audio: 600Ω (so 0 dBm = 0.78 V rms). State which impedance or it's ambiguous.
- **dBSPL** — 0 dB SPL = 20 μPa rms (threshold of hearing). Used in acoustics.
- **dBm noise floor** — 0 dBm at room temperature in 1 Hz bandwidth ≈ −174 dBm/Hz (thermal noise floor of a resistor).

**Where you see it:** Filter rolloff specs (−3 dB cutoff, −20 dB/decade), amplifier gain, RF link budgets, ADC dynamic range (each bit ≈ 6 dB), cable attenuation, antenna gain, audio levels.

> **Embedded tie-in:** ADC effective number of bits (ENOB) maps directly to dB: 12-bit ADC ≈ 72 dB dynamic range. Each bit of resolution is ~6 dB.

---

## 1.3.3 Other Signals

### A. Ramp

**What it is:** Voltage rising (or falling) at a constant rate (Figure 1.20A). Cannot go on forever — in practice it is approximated by a finite ramp (1.20B) or a periodic repeating ramp called a **sawtooth** (1.20C).

**Where you see it:** CRT horizontal sweep circuits. DAC output during a linear sweep. Integrator output with a constant input.

### B. Triangle Wave

**What it is:** A symmetrical ramp — rises at constant rate, then falls at constant rate (Figure 1.21). Close cousin of the ramp.

**Where you see it:** Function generators. PWM triangle carrier waves. Some oscillator topologies.

### C. Noise

**What it is:** Signals of interest are often mixed with noise — random fluctuations. The most common type is **band-limited white Gaussian noise**: equal power per hertz in some band, with a Gaussian (bell-curve) distribution of instantaneous amplitudes. Generated by resistors (Johnson noise or Nyquist noise). It plagues sensitive measurements of all kinds.

**The math:**

```
Noise is characterized by power spectral density (power per hertz)
or amplitude distribution.
Johnson noise voltage (rms) across a resistor R:
    V_n = √(4kTRB)
    k = 1.38×10⁻²³ J/K,  T in Kelvin,  B = bandwidth in Hz
```

**Intuition:** You can't eliminate thermal noise, only reduce it by lowering R, T, or B. Noise adds in quadrature (rms sum), not directly.

**Where you see it:** Chapter 8 covers noise and low-noise design in detail.

> **Embedded tie-in:** Every resistor in an ADC input network contributes Johnson noise. Minimize input resistance and bandwidth to improve SNR.

### D. Square Wave

**What it is:** Alternates between two fixed voltage levels (Figure 1.23). Characterized by amplitude, frequency, and phase. Unlike a sinewave, a linear circuit driven by a square wave rarely responds with a square wave.

```
For a square wave: V_peak = V_rms   (peak and rms amplitudes are equal)
```

The edges of a real square wave are not perfectly square. **Rise time t_r** is the time for the signal to go from 10% to 90% of its total transition (Figure 1.24). In typical circuits, rise time ranges from a few nanoseconds to a few microseconds.

**Intuition:** A fast edge contains high-frequency harmonics. This is why fast digital signals cause EMI. Rise time and bandwidth are inversely related: BW ≈ 0.35 / t_r.

> **Embedded tie-in:** SPI/I2C clock edges, UART transitions — all square waves. Slow rise times mean slower maximum bit rate. PCB trace capacitance directly limits rise time.

### E. Pulses

**What it is:** Signals like Figure 1.25 — defined by amplitude and pulse width. A periodic train of pulses has a frequency (repetition rate) and a **duty cycle**: ratio of pulse width to repetition period, from 0 to 100%.

Pulses can be positive or negative polarity, and "positive-going" or "negative-going."

**Intuition:** Average value of a pulse train = V_high × duty cycle. The "signal" in PWM is this average value.

> **Embedded tie-in:** PWM is a fixed-amplitude pulse train with variable duty cycle. Average value recovered with a lowpass filter. UART idle is HIGH; start bit is a LOW pulse. I2C SDA/SCL are open-drain — pull-up resistor sets the HIGH level.

### F. Steps and Spikes

**What it is:** Idealized waveforms useful for describing circuit behavior (Figure 1.26). A **step** is a sudden transition from one level to another — it is one half of a square wave. A **spike** is a jump of vanishingly short duration.

**Where you see it:** Step response characterizes how a circuit handles sudden changes (rise time, overshoot, ringing). Spikes appear from switching transients, ESD events, inductive kickback.

> **Embedded tie-in:** Inductive loads (relays, motors) generate voltage spikes when switched off. A flyback diode clamps the spike. Without it, the spike can exceed 100V and destroy FET gate oxide.

---

## 1.3.4 Logic Levels

**What they are:** Pulses and square waves dominate digital electronics. Predefined voltage levels represent one of two states at any point in a digital circuit — HIGH (1) and LOW (0), corresponding to the Boolean true and false.

**Key point from the book:** Precise voltages are not necessary. You only need to distinguish which of the two possible states is present. Each digital logic family specifies legal HIGH and LOW states.

**Example — 74LVC logic family (from book):**
```
Supply: +3.3V
Output LOW:  typically 0V (can be as much as 0.4V away from 0V)
Output HIGH: typically 3.3V (can be as much as 0.4V away from 3.3V)
Input decision threshold: 1.5V
```

**Intuition:** The gap between guaranteed output levels and required input thresholds is the noise margin — how much corruption the signal can absorb before the receiver misreads it. Output window is always inside the input window.

The book notes there is much more to say about logic levels — Chapters 10 through 12 cover this in detail.

> **Embedded tie-in:** Mixing logic families (3.3V and 5V) requires level shifting. A 5V signal on a 3.3V input can violate input thresholds and damage the device. Check the datasheet for 5V-tolerant pins — not all pins are tolerant even on devices advertised as such (e.g., STM32).

---

## 1.3.5 Signal Sources

**What they are:** For test purposes, a flexible external signal source is invaluable. Three types:

### A. Signal Generators

Sinewave oscillators. Equipped to cover a wide frequency range with precise control of amplitude (using a resistive attenuator network). Some allow AM or FM modulation. Sweep generators vary frequency over a range — used for testing filters and frequency-dependent circuits.

For many generators the source is a **frequency synthesizer**: generates sinewaves with digitally settable frequency, often to 8 significant figures. Internally derived from a quartz-crystal oscillator, rubidium standard, or GPS-derived oscillator. Example: Stanford Research Systems SG384, 1 μHz to 4 GHz, −110 dBm to +16.5 dBm, with AM/FM/ΦM modulation. Cost ~$4,600.

### B. Pulse Generators

Make pulses only — but with full control of pulse width, repetition rate, amplitude, polarity, and rise time. Fastest units reach gigahertz pulse rates. Many allow programmable patterns (also called pattern generators). Contemporary units provide logic-level outputs for direct connection to digital circuitry.

### C. Function Generators

The most flexible of the three. Can generate sine, triangle, and square waves over a wide frequency range (0.01 Hz to 30 MHz is typical), with amplitude and DC offset control. Most provide frequency sweeping.

Contemporary function generators are synthesized digital instruments — they combine the stability of a frequency synthesizer with the waveform flexibility of a function generator, and allow you to program arbitrary waveforms by specifying amplitude at equally spaced time points.

**Example (from book):** Tektronix AFG3102 — sine and square to 100 MHz, pulses and "noise" to 50 MHz, arbitrary waveforms up to 128k points, five modulation types, sweep, burst modes. Cost ~$5k.

**Intuition:** If you only have one signal source on your bench, get a function generator. It does sine, square, triangle, and arbitrary — enough for almost any test situation.

> **Embedded tie-in:** Function generators are how you test analog front-ends before the real sensor is connected. Inject a known sine to verify gain and frequency response of an ADC input filter. Use a square wave to check rise time and settling behavior.
