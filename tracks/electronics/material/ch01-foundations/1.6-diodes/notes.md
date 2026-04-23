# Ch. 1.6 — Diodes and Diode Circuits
*Art of Electronics, pp. 31–40 (§1.6.1–1.6.8)*

---

## 1.6.1 Diodes

### The V-I Curve

**What it is:** A two-terminal nonlinear device that conducts strongly in one direction (forward) and blocks in the other (reverse). Not a resistor — does not obey Ohm's law.

**Regions:**
- **Forward biased:** V_anode > V_cathode. Current flows. Forward drop V_f ≈ 0.6V (silicon) or 0.3V (Schottky). The drop is roughly constant over a wide current range — it's a nearly constant voltage drop, not a fixed resistance.
- **Reverse biased:** V_cathode > V_anode. Tiny leakage current (nA to μA). Holds until breakdown.
- **Breakdown:** At V_breakdown (typically 50–1000V for rectifier diodes), reverse current increases sharply. Destructive for regular diodes; intentional for zener diodes.

**Diode equation (Shockley):**
```
I = I_S * (e^(V/V_T) - 1)

I_S = saturation current (10⁻¹² to 10⁻⁶ A depending on device)
V_T = kT/q ≈ 26mV at room temperature (thermal voltage)
```

**Intuition:** Think of the diode as a one-way valve with a voltage toll (0.6V). Below 0.6V forward bias, it won't open. Above 0.6V, it conducts freely. The V_f increases slowly with current (logarithmically) — doubling current raises V_f by only ~18mV.

### Diode Types

| Type | V_f | V_breakdown | Key use |
|------|-----|------------|---------|
| Silicon (1N4001–1N4007) | 0.6–1V | 50–1000V | Rectification, flyback |
| Schottky (1N5817, BAT54) | 0.2–0.4V | 20–40V | High-speed, low-drop rectification |
| Signal (1N4148) | 0.7V | 75V | Fast switching, clamping |
| Zener | 0.6V fwd | V_Z (2.4–200V) | Voltage regulation/clamping |
| LED | 1.5–3.5V | — | Indicators, illumination |

---

## 1.6.2 Rectification

### Half-Wave Rectifier

Single diode in series with load. Passes only positive half-cycles. Peak output = V_peak − V_f. DC average = V_peak/π ≈ 0.318 × V_peak. High ripple.

### Full-Wave Bridge Rectifier

Four diodes arranged so both half-cycles contribute. Peak output = V_peak − 2V_f (two diodes in the path). DC average = 2×V_peak/π ≈ 0.636 × V_peak. Ripple frequency = 2× line frequency.

**Intuition:** The bridge flips negative half-cycles to positive. Always two diodes conduct simultaneously (two drops). More efficient use of the transformer.

---

## 1.6.3 Power-Supply Filtering

### Adding a Filter Cap

A large capacitor across the rectifier output charges to the peak voltage, then discharges into the load between diode conduction intervals. Reduces ripple.

**Ripple approximation:**
```
ΔV ≈ I_load / (f * C)           (half-wave, f = line freq)
ΔV ≈ I_load / (2f * C)          (full-wave, ripple at 2f)
```

**Derivation intuition:** During the discharge interval (≈ 1/f), the cap loses I_load × t coulombs of charge. Q = C × ΔV, so ΔV = Q/C = I × t / C = I/(fC). Don't memorize — derive from I = C dV/dt.

**Where you see it:** Every AC-to-DC power supply. Bench supply, phone charger, wall wart. The large electrolytic capacitors visible inside power supplies are the filter caps.

---

## 1.6.4 Rectifier Configurations for Power Supplies

### Center-Tap Full-Wave
Two diodes + center-tapped transformer. Only one diode drop in path. Used when minimizing drop matters (high-current supplies). Requires a center-tapped transformer.

### Bridge (No Center Tap)
Four diodes + any transformer. Two diode drops in path. More common because standard transformers work. The standard topology.

**Peak inverse voltage (PIV):** The reverse voltage a diode must withstand. For a bridge: PIV = V_peak. For half-wave: PIV = 2×V_peak. Specify diodes with PIV rated well above the expected peak.

---

## 1.6.5 Regulators (Zener)

### Zener Voltage Regulation

**What it is:** A zener diode in reverse breakdown at a specified voltage V_Z. Used with a series dropping resistor to regulate output voltage.

**The math:**
```
I_Z = (V_in - V_Z) / R_series

Line regulation:
  ΔV_out = ΔV_in * R_dyn / (R_series + R_dyn)

Load regulation:
  ΔV_out = ΔI_load * (R_dyn || R_series)
```

**Intuition:** The zener acts as a "voltage clamp" in the voltage divider formed with R_series. R_dyn (dynamic resistance of the zener, typically 5–50Ω at rated current) takes the role of R2. The smaller R_dyn relative to R_series, the better the regulation. Low-voltage zeners (<3.3V) have poor R_dyn — use IC references instead.

**Efficiency:** Zener regulators are inherently inefficient. Excess current flows through the zener as heat even at light load. For anything beyond simple clamping, use an IC linear regulator or switching supply.

> **Embedded tie-in:** 3.3V zener as an I/O protection clamp: put it from the signal line to ground with a series resistor. Any signal above 3.3V gets clamped. Useful for protecting MCU inputs from 5V signals when a level shifter isn't available.

---

## 1.6.6 Circuit Applications of Diodes

### Clamps
A diode that prevents a node voltage from exceeding (or dropping below) a reference. Used in peak detectors, envelope detectors, and input protection.

### Limiters (Clippers)
Back-to-back diodes (one forward, one reverse) clip the signal to ±V_f = ±0.6V. Any signal larger than 0.6V is clipped. Used as input protection for sensitive amplifier inputs.

### Diode OR Gate
Two diodes with anodes tied to separate sources, cathodes tied together. Output = higher of two input voltages. Used in battery backup circuits (primary supply OR battery). No logic ICs needed.

### Envelope Detector
Diode + RC. Charges to peak, discharges slowly through R. Tracks the amplitude envelope of a modulated signal. This is the AM radio detector (§1.8).

---

## 1.6.7 Inductive Loads and Diode Protection

### The Flyback Diode

**Why it's needed:** When a transistor switch opens in series with an inductor (relay coil, motor, solenoid), the inductor generates a large positive voltage spike (inductive kick) to maintain current flow. Without a flyback diode, this spike can be hundreds of volts — enough to destroy the transistor.

**The fix:** Place a diode across the inductor with cathode toward the positive supply. Under normal operation, the diode is reverse biased and does nothing. When the switch opens, the kick forward-biases the diode, clamping the spike to V_supply + V_f.

**Selection:** 1N4001 works for most slow relay applications. For high-speed switching, use a Schottky diode (no reverse recovery time). Place physically close to the inductor on the PCB.

> **Embedded tie-in:** This is mandatory when driving relays from GPIO or transistors. No exceptions. The inductive kick that kills a GPIO happens in nanoseconds — you can't protect it in software.

---

## 1.6.8 Interlude: Inductors as Friends

### The Book's Point

Inductors seem troublesome (inductive kicks, saturation, bulky), but they're essential:
- Switching regulators would be impossible without them
- RF circuits need them for resonance and matching
- Filters with inductors have far sharper rolloffs than RC filters

**Intuition:** The inductive kick is just stored energy being released. Harness it (boost converter, flyback supply) and it's useful. Ignore it (unprotected relay driver) and it destroys things. The difference is a flyback diode or a controlled switching topology.
