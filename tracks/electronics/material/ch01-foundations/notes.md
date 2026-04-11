# Ch. 1 — Foundations

Companion notes for *The Art of Electronics*, 3rd ed., Chapter 1 (pp. 1–67).
Covers all passive components and foundational circuit analysis.

---

## 1. Voltage, Current, Resistance (sections 1.2)

### Ohm's Law and Kirchhoff's Laws

**What it is:** The three rules that govern all resistive circuits.

- **Ohm's law:** V = IR. Voltage across a resistor equals current times resistance.
- **KCL (Kirchhoff's Current Law):** The sum of currents into a node equals the sum out. Conservation of charge.
- **KVL (Kirchhoff's Voltage Law):** The sum of voltage drops around any closed loop is zero. Conservation of energy.

**The math:**
```
V = IR          (Ohm's law)
sum(I_in) = sum(I_out)   (KCL)
sum(V_loop) = 0           (KVL)
```

**Intuition:** Voltage is the *cause* (pressure), current is the *effect* (flow), resistance is the *opposition*. Current flows *through* things; voltage appears *across* things. Never say "voltage through a resistor" — that's nonsense.

### Resistors: Series and Parallel

**What it is:** Two ways to combine resistors, with shortcuts for mental math.

**The math:**
```
Series:    R_total = R1 + R2 + ...
Parallel:  R_total = (R1 * R2) / (R1 + R2)    [two resistors]
           1/R_total = 1/R1 + 1/R2 + 1/R3 + ...  [general]
```

**Intuition:**
- Series: more resistance in the path = harder to push current through = larger R.
- Parallel: more paths for current = easier to flow = smaller R.

**Shortcut #1:** A large resistor in series (parallel) with a small one has roughly the resistance of the larger (smaller) one. Use this to "trim" values — series resistor to bump up, parallel to bring down.

**Shortcut #2:** Think in terms of "how many equal resistors in parallel." 5k in parallel with 10k? That's three 10k's in parallel = 10k/3 = 3.33k. n equal resistors in parallel = R/n.

**Where you see it in real hardware:** Resistor networks in bias circuits, feedback dividers in op-amp circuits, current-limiting resistors for LEDs.

### Power Dissipation

**What it is:** Electrical energy converted to heat in a resistor.

**The math:**
```
P = IV = I²R = V²/R
```

**Intuition:** All three forms are Ohm's law substitutions of the same P=IV. Pick whichever form matches what you know. A 1/4W resistor above 1k can never blow from a 15V battery (Exercise 1.5 in the book — prove this to yourself).

**Where you see it in real hardware:** Power ratings on resistors (1/8W, 1/4W, 1/2W), heatsink calculations, thermal design of PCBs.

### Voltage Dividers

**What it is:** The most important circuit fragment in electronics. Two resistors in series, output taken from the middle. Produces a predictable fraction of the input voltage.

**The math:**
```
V_out = V_in * R2 / (R1 + R2)
```
(See Figure 1.6, p. 7)

**Intuition:** It's a ratio. The output is the fraction of resistance "below" the tap point. If R2 is 1/3 of the total, you get 1/3 of the input. This is also how you *think about* circuits — any node in a circuit can be modeled as a divider between the source impedance above and load impedance below.

**Where you see it in real hardware:** ADC input scaling (e.g., measuring 12V battery with 3.3V ADC), bias networks, volume controls, level shifting.

> **Embedded tie-in:** Pull-up and pull-down resistors on MCU GPIO pins are just one leg of a voltage divider. The other leg is the internal switch (transistor) in the driving device. A 10k pull-up to 3.3V with a button to ground is a divider that switches between 3.3V (open) and 0V (pressed).

### Voltage and Current Sources

**What it is:** Idealized circuit elements that maintain a fixed voltage (or current) regardless of load.

- **Voltage source:** Maintains V across its terminals. Internal resistance ideally zero. A real battery is a perfect voltage source + small series resistance (e.g., 9V battery ~ 3 ohm internal R).
- **Current source:** Maintains I through its terminals. Internal resistance ideally infinite. Hates open circuits.

**Intuition:** Voltage sources "like" open circuits (no current to supply) and "hate" shorts (infinite current demanded). Current sources are the opposite.

### Thevenin Equivalent Circuit

**What it is:** Any two-terminal network of resistors and voltage sources can be replaced by a single voltage source V_Th in series with a single resistor R_Th. (See Figure 1.11, p. 9)

**The math:**
```
V_Th = V_open_circuit
R_Th = V_open_circuit / I_short_circuit
```

For a voltage divider:
```
V_Th = V_in * R2 / (R1 + R2)
R_Th = R1 * R2 / (R1 + R2)    (= R1 || R2)
```
(See Figures 1.12–1.13, p. 9–11)

**Intuition:** Thevenin tells you how "stiff" a voltage source is. A low R_Th means the output barely sags under load. A voltage divider made from two 10k resistors has R_Th = 5k — not a great voltage source. To avoid loading, keep R_load >> R_Th (rule of thumb: 10x or more). Figure 1.14 (p. 11) shows attenuation vs. load ratio graphically.

**Where you see it in real hardware:** Every signal source has a Thevenin equivalent. Op-amp outputs have R_Th of milliohms. A GPIO pin driving HIGH has R_Th of ~25-50 ohm (depending on the chip).

### Small-Signal (Dynamic) Resistance

**What it is:** For nonlinear devices (diodes, zeners), the ratio V/I isn't constant. Instead, we care about the *slope* of the V-I curve: r = dV/dI. This is the resistance the device presents to *small changes* around its operating point.

**The math:**
```
r_dyn = dV / dI = delta_V / delta_I
```

**Intuition:** A zener diode at its rated current might have V_Z = 5.1V but r_dyn = 10 ohm. A 10% change in current (say 1mA around 10mA) causes delta_V = 10 * 0.001 = 10mV change in output. That's 0.2% regulation — good. For small signals, the zener *acts like* a 10 ohm resistor in a voltage divider with the series dropping resistor. (See Figure 1.16, p. 12)

**Where you see it in real hardware:** Diode forward drop variation with current, zener regulation quality, LED brightness variation. This concept is *essential* for understanding transistor circuits in Ch. 2.

### Circuit Loading

**What it is:** When you attach a load to a voltage source, the output voltage drops because current flows through the source's internal (Thevenin) resistance.

**Intuition:** Always make R_load >> R_source to minimize loading. This is why voltmeters have high input resistance (10M ohm) and why buffer amplifiers exist — they present high impedance to the source and low impedance to the load.

> **Embedded tie-in:** Current-sense resistors (small R in series with load, measure voltage across it to infer current) are everywhere in embedded power management. The STM32 ADC has ~6k input impedance during sampling — your source must be able to drive that without sagging.

---

## 2. Signals (section 1.3)

### Sinusoidal Signals

**What it is:** The fundamental AC waveform. Every periodic signal can be decomposed into sinusoids (Fourier).

**The math:**
```
V(t) = A * sin(2*pi*f*t + phi)
      = A * sin(omega*t + phi)

omega = 2*pi*f    (angular frequency, rad/s)
f = 1/T            (frequency in Hz)
```

**Intuition:** Sinewaves are special because linear circuits preserve their shape — a sinewave in always produces a sinewave out (possibly with different amplitude and phase). This is why frequency-domain analysis works.

**Key values:**
- V_rms = V_peak / sqrt(2) = 0.707 * V_peak (sinewaves only)
- V_pp = 2 * V_peak
- US mains: 120V rms, 170V peak, 60Hz

### Decibels

**What it is:** A logarithmic ratio for comparing signal levels. Used because human perception and circuit behavior span many orders of magnitude.

**The math:**
```
dB = 10 * log10(P2/P1)        (power ratio)
dB = 20 * log10(A2/A1)        (amplitude ratio)
```

**Landmarks to memorize:**

| dB | Voltage ratio | Power ratio |
|----|--------------|-------------|
| 0  | 1            | 1           |
| 3  | 1.41 (sqrt2) | 2           |
| 6  | 2            | 4           |
| 10 | 3.16         | 10          |
| 20 | 10           | 100         |
| -3 | 0.707        | 0.5         |
| -20| 0.1          | 0.01        |

**Intuition:** +3dB = double the power. +6dB = double the voltage. +20dB = 10x voltage. These are the only three you need; everything else is addition. Example: +26dB = +20 + 6 = 10x * 2x = 20x voltage.

### Other Signal Types

- **Square wave:** Digital signals. Peak = rms (no sqrt(2) factor). Characterized by rise time (10% to 90% transition).
- **Triangle/ramp:** Basis of sweep circuits, sawtooth oscillators, ADC conversion.
- **Noise:** Random thermal fluctuations. Johnson noise from every resistor. Specified as power spectral density or rms voltage in a bandwidth.
- **Pulses:** Defined by amplitude, width, repetition rate, duty cycle.
- **Steps and spikes:** Useful for describing transient events. Step = part of square wave. Spike = vanishingly short pulse.

### Logic Levels

**What it is:** Digital circuits use predefined voltage ranges for HIGH (1) and LOW (0).

**Example — 3.3V LVCMOS (74LVC family):**
- V_OH (output high): ~3.3V
- V_OL (output low): ~0V
- V_IH (input high threshold): 1.5V (above this = HIGH)
- Noise margin: actual outputs can be 0.4V away from rails without malfunction

> **Embedded tie-in:** PWM is a rectangular signal with variable duty cycle — the "signal" is the average voltage (duty * V_high). UART idle is HIGH; start bit pulls LOW. I2C uses open-drain with pull-ups — the signal levels depend on the pull-up voltage. When interfacing 3.3V and 5V logic, you need level shifters or series resistors with clamp diodes.

---

## 3. Capacitors & RC Circuits (section 1.4)

### Capacitor Fundamentals

**What it is:** A device that stores charge (and energy) in an electric field between two plates. The second most common passive component after resistors.

**The math:**
```
Q = CV                    (charge = capacitance * voltage)
I = C * dV/dt             (current proportional to RATE of voltage change)
U = (1/2) * C * V^2      (stored energy)
```

**Intuition:** A capacitor resists changes in voltage. It takes current to change the voltage across a cap — the bigger the cap, the more current (or time) needed. At DC, a cap is an open circuit (no voltage change = no current). At high frequencies, it's nearly a short (rapid voltage changes = large current).

**Parallel and series:**
```
Parallel: C_total = C1 + C2 + ...          (opposite of resistors!)
Series:   1/C_total = 1/C1 + 1/C2 + ...
```

### Bypass vs. Coupling — The Two Most Common Uses

**Bypass (decoupling):** Cap from power pin to ground. Provides a local reservoir of charge so transient current demands don't cause voltage dips on the supply rail. Looks like a short at high frequencies, shunting noise to ground.

**Coupling (blocking):** Cap in series with signal path. Passes AC signals while blocking DC bias. Acts as a highpass filter — must be large enough that its reactance is small at the lowest signal frequency.

> **Embedded tie-in:** Every MCU datasheet specifies bypass caps — typically 100nF ceramic on each VDD pin, plus a bulk 10uF nearby. This is not optional. Without them, fast switching currents cause ground bounce and supply droop that corrupt logic levels and cause mysterious crashes.

### RC Time Constant and Charge/Discharge

**What it is:** The fundamental timing behavior of any circuit with resistance and capacitance.

**The math:**
```
tau = R * C                              (time constant, in seconds)

Discharge: V(t) = V0 * e^(-t/RC)        (exponential decay)
Charge:    V(t) = Vf * (1 - e^(-t/RC))  (exponential rise to Vf)
```
(See Figures 1.32–1.34, pp. 21–22)

**Intuition:** After 1 tau, the capacitor has charged to 63% (or discharged to 37%) of its final value. The **5*tau rule**: after 5 time constants, the cap is >99% settled. A 1uF cap across 1k has tau = 1ms; it's fully charged in ~5ms.

| Time | % of final value (charging) |
|------|---------------------------|
| 1 RC | 63% |
| 2 RC | 86% |
| 3 RC | 95% |
| 4 RC | 98% |
| 5 RC | 99.3% |

**Where you see it in real hardware:** Button debouncing (RC filter on switch input, tau ~ 5-20ms), power-on reset delay circuits, ADC sample-and-hold settling.

### Differentiator (Edge Detector)

**What it is:** A capacitor in series with the signal, resistor to ground. Output is proportional to the *rate of change* of the input. (See Figure 1.41B, p. 25)

**The math:**
```
V_out ≈ RC * dV_in/dt     (when RC << signal period)
```

**Intuition:** Feed in a square wave, get spikes at the edges. The cap passes fast changes and blocks slow ones. This is a highpass filter in the frequency domain, a differentiator in the time domain — same circuit, two ways to think about it.

**Where you see it in real hardware:** Edge detection in digital logic, trigger circuits, detecting transitions in serial communication. Unintentional capacitive coupling (e.g., crosstalk between adjacent PCB traces) also acts as a differentiator.

### Integrator (Averager)

**What it is:** A resistor in series with the signal, capacitor to ground. Output is proportional to the *integral* (running average) of the input. (See Figure 1.46B, p. 27)

**The math:**
```
V_out ≈ (1/RC) * integral(V_in dt)     (when V_out << V_in)
```

**Intuition:** Feed in a square wave, get a triangle (ramp up, ramp down). The cap smooths out rapid changes, keeping only the slow trend. This is a lowpass filter in the frequency domain, an integrator in the time domain.

**Where you see it in real hardware:** Power supply ripple filtering, ADC input smoothing, ramp generators (constant current into a cap gives a linear ramp — basis of many ADC architectures).

> **Falstad simulation suggestion:** Build an RC lowpass filter. Drive it with a square wave. Vary R and C to see the smoothing effect. Then swap R and C positions to make a highpass filter.

---

## 4. Inductors & Transformers (section 1.5)

### Inductor Fundamentals

**What it is:** A coil of wire that stores energy in a magnetic field. The dual of a capacitor — where caps resist voltage changes, inductors resist current changes.

**The math:**
```
V = L * dI/dt              (voltage proportional to RATE of current change)
U = (1/2) * L * I^2       (stored energy in magnetic field)
```

**Intuition:** An inductor tries to keep current flowing at a constant rate. If you try to suddenly stop current through an inductor (open a switch), it generates a huge voltage spike ("inductive kick") to force the current to keep flowing. This is the same physics that makes a spark when you unplug something under load.

### Volt-Second Balance

**What it is:** For an inductor in a steady-state periodic circuit, the average voltage across it must be zero over one cycle. Otherwise the current would ramp up without limit.

**Intuition:** This is the fundamental constraint that governs all switching power converters. In a buck converter, the inductor is alternately connected to V_in and ground; the duty cycle sets the ratio so that the average voltage (and thus the output) is D * V_in.

### Transformers

**What it is:** Two coupled inductors. AC on the primary induces AC on the secondary, with voltage and current scaled by the turns ratio. (See Figure 1.53, p. 30)

**The math:**
```
V_sec / V_pri = N_sec / N_pri = n      (turns ratio)
I_sec / I_pri = 1/n                     (current scales inversely)
Z_reflected = n^2 * Z_load              (impedance transformation)
```

**Intuition:** Transformers trade voltage for current (or vice versa) while conserving power. They also provide galvanic isolation — no DC path between primary and secondary. Real transformers have magnetizing inductance (draws current even unloaded) and leakage inductance (voltage drops under load, causes spikes).

### Boost and Buck Converter Preview

(See Figure 1.52, p. 30)

- **Buck (step-down):** Switch alternately connects inductor to V_in and ground. Inductor + cap smooth the output. V_out = D * V_in where D is duty cycle.
- **Boost (step-up):** Inductor charges from V_in, then switch forces stored energy through diode to output cap. V_out = V_in / (1-D). Can produce output > input.

> **Embedded tie-in:** Every modern MCU board has a switching regulator (usually buck) to convert USB 5V to 3.3V or 1.8V core voltage. Ferrite beads on digital signal lines are just tiny inductors — they present high impedance at RF frequencies, filtering out high-frequency noise without affecting the DC signal. The flyback diode across relay/motor coils is mandatory — without it, the inductive kick will destroy your MOSFET driver transistor.

---

## 5. Diodes & Diode Circuits (section 1.6)

### Diode V-I Curve

**What it is:** A diode is a two-terminal nonlinear device that conducts in one direction. (See Figure 1.55, p. 31)

- **Forward biased:** Current flows when V_anode > V_cathode by ~0.6V (silicon) or ~0.3V (Schottky).
- **Reverse biased:** Essentially no current flows (nanoamps) until breakdown voltage (typically 50-1000V).

**Intuition:** Think of it as a one-way valve with a 0.6V toll. The forward drop is roughly constant over a wide current range (that's what makes the V-I curve steep). It's *not* a resistor — it doesn't obey Ohm's law. Schottky diodes have lower drop (~0.3V) and zero reverse recovery time, making them preferred for high-speed switching.

### Rectification

**What it is:** Converting AC to DC using diodes.

- **Half-wave:** Single diode, passes only positive half-cycles. (Figure 1.56, p. 32)
- **Full-wave bridge:** Four diodes in a bridge, passes both half-cycles. (Figure 1.58, p. 32)

**Ripple calculation:**
```
delta_V = I_load / (f * C)         (half-wave, f = line frequency)
delta_V = I_load / (2 * f * C)     (full-wave, ripple freq = 2*f)
```
(See Figure 1.61, p. 33)

**Intuition:** The capacitor charges to the peak voltage during diode conduction, then discharges into the load between peaks. Bigger cap = less ripple but higher peak charging currents (I^2*R heating in transformer windings). Don't memorize the ripple formula — derive it from I = C*dV/dt with delta_t ~ 1/f.

> **Falstad simulation suggestion:** Build a bridge rectifier with capacitor filter. Vary the load resistance and capacitor value. Watch the ripple change. Note the narrow conduction angle of the diodes.

### Zener Diodes and Voltage Regulation

**What it is:** A diode designed to operate in reverse breakdown at a specified voltage. (See Figure 1.16, p. 12)

**The math:**
```
delta_V_out = (R_dyn / (R + R_dyn)) * delta_V_in
```
This is the voltage divider equation with the zener's dynamic resistance substituting for R2.

**Intuition:** A zener acts like a "voltage clamp" — it holds its terminal voltage nearly constant as current varies. The smaller R_dyn relative to the series resistor R, the better the regulation. At 5.1V, a typical zener has R_dyn ~ 7 ohm at 50mA. Low-voltage zeners (<3.3V) have poor performance (see Figure 1.17, p. 13) — use IC voltage references instead.

### Diode Circuit Applications

- **Clamps:** Limit signal voltage to a fixed range. (Figure 1.72, p. 36)
- **Limiters:** Back-to-back diodes clip signal to +/-0.6V. Input protection for sensitive amplifier inputs. (Figure 1.78, p. 37)
- **OR gates (diode logic):** Pass the higher of two voltages. Used in battery backup circuits. (Figure 1.71, p. 36)
- **Flyback diode:** Across inductive loads (relays, motors) to clamp the inductive kick. *Always* include one. 1N4004 works for most applications. (Figure 1.84, p. 39)

> **Embedded tie-in:** Every CMOS GPIO pin has ESD protection diodes to VDD and ground. If your signal goes above VDD + 0.6V or below GND - 0.6V, current flows through these diodes — which can latch up and destroy the chip if the current is too high. Schottky diodes in the power path (between USB and battery) prevent back-feeding. Reverse polarity protection: series Schottky diode (simple, wastes 0.3V) or P-MOSFET (better, near-zero drop).

---

## 6. Impedance & Reactance (section 1.7)

### Reactance

**What it is:** The frequency-dependent "resistance" of capacitors and inductors. Unlike resistance, reactance doesn't dissipate power — energy is alternately stored and returned.

**The math:**
```
X_C = 1 / (omega * C) = 1 / (2*pi*f*C)     (capacitive reactance, decreases with f)
X_L = omega * L = 2*pi*f*L                   (inductive reactance, increases with f)
```

**Intuition:** Capacitors are "short" at high frequencies, "open" at DC. Inductors are the opposite: "short" at DC, "open" at high frequencies. This is why caps are used for bypassing (short out high-freq noise) and inductors for chokes (block high-freq noise).

### Complex Impedance

**What it is:** The generalization of resistance to AC circuits. Combines magnitude (how much the component opposes current) with phase (whether current leads or lags voltage).

**The math:**
```
Z_R = R                      (resistor — purely real)
Z_C = -j/(omega*C) = 1/(j*omega*C)   (capacitor — negative imaginary)
Z_L = j*omega*L              (inductor — positive imaginary)

General impedance: Z = R + jX
Generalized Ohm's law: V = I*Z
```

Series and parallel rules work exactly as with resistors, but with complex arithmetic.

**Intuition:** The "j" tracks the 90-degree phase shift. In a capacitor, current leads voltage by 90 degrees (current flows first to change the voltage). In an inductor, voltage leads current by 90 degrees (voltage appears first to change the current). The magnitude |Z| gives the ratio of voltage to current amplitudes.

### RC Lowpass Filter

**What it is:** R in series, C to ground. Passes low frequencies, attenuates high frequencies. (See Figure 1.90, p. 42; Figure 1.104, p. 50)

**The math:**
```
V_out/V_in = 1 / sqrt(1 + (2*pi*f*R*C)^2)

f_3dB = 1 / (2*pi*R*C)       (breakpoint: output is -3dB = 0.707 of input)
```
Above f_3dB: rolls off at -20 dB/decade (-6 dB/octave).

**Intuition:** Below the breakpoint, the cap's reactance >> R, so the divider ratio is near 1. Above the breakpoint, cap's reactance << R, so most of the voltage drops across R and little reaches the output. The phase shifts from 0 degrees (well below f_3dB) to -90 degrees (well above), passing through -45 degrees at f_3dB.

### RC Highpass Filter

**What it is:** C in series, R to ground. Passes high frequencies, blocks low frequencies and DC. Same breakpoint formula. (See Figure 1.92, p. 43; Figure 1.99, p. 49)

**The math:**
```
V_out/V_in = (2*pi*f*R*C) / sqrt(1 + (2*pi*f*R*C)^2)

f_3dB = 1 / (2*pi*R*C)       (same formula)
```

**Intuition:** This is the "blocking capacitor" configuration. Below f_3dB, the cap's reactance >> R, so the signal is attenuated. Above f_3dB, the cap is a near-short and the signal passes through.

### LC Resonance

**What it is:** When an inductor and capacitor are combined, they can exchange energy back and forth at a natural frequency — the resonant frequency. (See Figures 1.107–1.110, pp. 53–54)

**The math:**
```
f_0 = 1 / (2*pi*sqrt(L*C))       (resonant frequency)
Q = f_0 / delta_f_3dB            (quality factor — sharpness of peak)

Parallel LC (tank):  Q = omega_0 * R * C = R / (omega_0 * L)
Series LC (trap):    Q = omega_0 * L / R = 1 / (omega_0 * R * C)
```

**Intuition:** At resonance, the inductive and capacitive reactances are equal and opposite — they cancel. A parallel LC ("tank") has *maximum* impedance at resonance (energy sloshes between L and C, presenting high impedance to the outside world). A series LC ("trap") has *minimum* impedance (goes to zero for ideal components). Q measures how sharp the resonance is — higher Q = narrower peak = more selective.

### Power Factor

**What it is:** In circuits with reactive components, voltage and current are out of phase. Only the in-phase component does real work.

```
Power factor = cos(phi) = P_real / (V_rms * I_rms)
```

**Intuition:** A purely reactive circuit (cap or inductor alone) has power factor = 0. All current flows but no power is consumed. Industrial motors are inductive, so power companies charge for reactive power and require power factor correction (parallel capacitors).

> **Embedded tie-in:** Anti-aliasing filter before an ADC is an RC lowpass. Set f_3dB to half the sample rate (Nyquist) or below to prevent aliasing. For a 1 MSPS ADC sampling at 500 kHz Nyquist, you might set f_3dB = 100 kHz with R=1k, C=1.6nF. LC filters in switching power supplies have much sharper cutoffs than RC — that's why switchers use inductors. The impedance of a bypass cap at a given frequency tells you how effective it is: a 100nF ceramic has |Z| = 1.6 ohm at 1 MHz but 160 ohm at 10 kHz.

> **Falstad simulation suggestion:** Build an RC lowpass filter and sweep the input frequency. Watch the output amplitude decrease and phase shift increase above f_3dB. Then build a parallel LC tank and observe the resonant peak.

---

## 7. AM Radio Capstone (section 1.8)

### The Simplest AM Receiver

**What it is:** A circuit that ties together resonance, rectification, and filtering — all the concepts from Chapter 1 in one elegant application. (See Figure 1.114, p. 56)

**How it works (block by block):**
1. **Antenna** picks up a mix of all AM stations plus noise.
2. **Parallel LC tank** (variable C1 + inductor L) tuned to the desired station's carrier frequency (520–1720 kHz). The high Q of the tank amplifies the selected station and rejects others.
3. **Diode D** half-wave rectifies the modulated carrier, stripping off the negative half-cycles.
4. **R1 provides a DC path** (light load) so the rectified output follows the envelope.
5. **C2 smooths** the rectified carrier — its time constant (R1*C2) is long compared to the carrier period (~1 us) but short compared to the audio period (~200 us), so it follows the audio envelope while filtering out the RF carrier.
6. **Audio amplifier** boosts the weak signal to drive a speaker.

**Intuition:** AM works by varying the *amplitude* of a high-frequency carrier to encode a low-frequency audio signal. The diode + RC filter act as an "envelope detector" — they extract the slow amplitude variations while discarding the fast carrier oscillation. This is the same principle as power supply filtering, just at RF frequencies.

**Key observation:** The LC tank not only selects the station but actually *amplifies* the signal — the voltage across the tank at resonance is Q times the antenna voltage. The book shows this dramatically in Figures 1.115–1.116 (p. 56).

---

## 8. Other Passive Components (sections 1.9–1.10)

### Switches

**What it is:** Mechanical devices that make or break electrical connections.

**Types:**
- **SPST:** Single-pole single-throw. Simple on/off. (Figure 1.119, p. 58)
- **SPDT:** Single-pole double-throw. Selects between two connections. Used for "three-way" light switches.
- **DPDT:** Double-pole double-throw. Two SPDT switches ganged together. Can reverse polarity of a motor.
- **Momentary (pushbutton):** Returns to default position when released. NO (normally open) or NC (normally closed). (Figure 1.120, p. 58)
- **Rotary:** Multiple positions. Shorting (make-before-break) or non-shorting (break-before-make).

**Where you see it in real hardware:** Reset buttons on dev boards, DIP switches for configuration, rotary encoders for user input.

### Relays

**What it is:** Electrically controlled switches. A coil energizes an electromagnet that pulls contacts closed. (section 1.9.2, p. 59)

- **Electromechanical:** Coil + mechanical contacts. Provides complete galvanic isolation. Coil voltages from 3V to 115V.
- **Solid-state relay (SSR):** LED + phototransistor/triac. No mechanical parts. Faster, no contact bounce, longer life. Used for AC switching.

> **Embedded tie-in:** Never drive a relay coil directly from an MCU GPIO pin — the coil draws too much current (10-100mA) and the inductive kick will damage the pin. Use a transistor (NPN or N-MOSFET) as a switch, with a flyback diode across the coil. GPIOs typically source/sink only 4-20mA.

### Connectors

**What it is:** The physical interface for getting signals and power in and out of circuits. (Figures 1.123–1.125, pp. 60–62)

**Common types:**
- **BNC:** Coaxial, 50 or 75 ohm. The standard for lab instruments.
- **SMA/SMB:** Miniature coaxial. Common on RF boards and small instruments.
- **D-sub (DB-9, DB-25):** Multi-pin, used for serial ports, old parallel ports.
- **Pin headers (0.1" / 2.54mm):** The standard for prototyping and dev boards. Male pins on board, female Dupont connectors on wires.
- **USB:** Power and data. Type-A, Type-B, Micro-B, Type-C.
- **Edge connectors:** Direct contact with PCB copper. Used in memory DIMMs, PCIe cards.

### LEDs and Indicators

**What it is:** LEDs are diodes that emit light when forward biased. Forward drop is 1.5–2V (red/orange/green) or 3–3.6V (blue/white). Typical operating current: 2–10mA for indicators.

**The math for a series current-limiting resistor:**
```
R = (V_supply - V_LED) / I_LED
Example: R = (3.3V - 2.0V) / 5mA = 260 ohm -> use 270 ohm
```

### Variable Components

- **Potentiometers:** Variable resistors with a wiper. Don't use as precision resistors — poor stability and resolution. Use a fixed resistor + small trim pot for precision.
- **Varactors:** Voltage-variable capacitors (diodes operated in reverse bias). Used in PLLs, VCOs, automatic frequency tuning.

### Surface-Mount Technology (SMT)

**What it is:** Components designed to be soldered directly to the surface of a PCB rather than through holes. (Figures 1.131–1.133, pp. 65–66)

**Common package sizes (imperial/metric):**

| Imperial | Metric | Dimensions (mm) | Notes |
|----------|--------|-----------------|-------|
| 0402     | 1005   | 1.0 x 0.5       | Tiny. Tweezers required. |
| 0603     | 1608   | 1.6 x 0.8       | Common for production. |
| 0805     | 2012   | 2.0 x 1.25      | Good for hand soldering. |
| 1206     | 3216   | 3.2 x 1.6       | Easy to hand solder. |

**Intuition:** SMT dominates modern electronics because it's smaller, has lower parasitic inductance (shorter leads), and is compatible with automated assembly. The downside: prototyping is harder. For learning, use 0805 or larger. Many new ICs are *only* available in SMT packages.

---

## Falstad Simulation Suggestions

1. **Voltage divider with loading** — Build a 10k/10k divider from 10V. Measure output unloaded (should be 5V). Then add a 10k load resistor. Output drops to 3.33V. Calculate the Thevenin equivalent and verify.

2. **RC lowpass filter (frequency sweep)** — R=10k, C=10nF (f_3dB ~ 1.6kHz). Drive with a sinewave, sweep from 100Hz to 100kHz. Watch the output attenuate above f_3dB.

3. **Bridge rectifier with capacitor filter** — Transformer secondary, four diodes, filter cap, load resistor. Vary the cap and load to see ripple change.

4. **LC resonant tank** — L=100uH, C=100pF (f_0 ~ 1.6MHz). Drive through a series resistor and sweep frequency. Watch the voltage across the tank peak at resonance.
