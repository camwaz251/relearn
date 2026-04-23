# Ch. 1.2 — Voltage, Current, and Resistance
*Art of Electronics, pp. 1–13 (§1.1–1.2.7)*

---

## 1.2.1 Voltage and Current

### What they are
- **Current (I):** Rate of charge flow through a conductor. Measured in amperes (A = coulombs/second). Conventional current flows from + to −; electrons actually move the other way. Doesn't matter which convention you use as long as you're consistent.
- **Voltage (V):** Electric potential difference between two points. The "pressure" that drives current. Always measured *between two points* — never at one point in isolation. Measured in volts.

**Intuition:** Water analogy — voltage is pressure, current is flow rate, resistance is pipe narrowness. Works well for DC intuition but breaks down for AC and reactive components. Use it early, abandon it later.

### Kirchhoff's Laws

**What they are:** The two conservation laws that govern all circuit analysis.

**The math:**
```
KCL: sum(I_in) = sum(I_out)    at any node
KVL: sum(V_loop) = 0           around any closed loop
```

**Intuition:**
- KCL = conservation of charge. Charge doesn't pile up at a node. Whatever current flows in must flow out.
- KVL = conservation of energy. If you walk around a loop and come back to the start, your net elevation change is zero. Voltage is the same — you can't gain or lose net voltage going around a closed path.

**Where you see it:** Every circuit analysis you will ever do uses one or both of these. Mesh analysis (KVL), node analysis (KCL).

---

## 1.2.2 Resistors — Ohm's Law

### Ohm's Law

**The math:**
```
V = IR
```

**Intuition:** Linear relationship — double the voltage, double the current. Not all components obey this (diodes, transistors don't), but resistors do by definition. A component is "ohmic" if V/I is constant regardless of V or I.

**Key rule:** Current flows *through* a resistor; voltage appears *across* it. "Voltage through" is nonsense.

### Series and Parallel Combinations

**The math:**
```
Series:   R_total = R1 + R2 + ...
Parallel: R_total = (R1 * R2) / (R1 + R2)      [two resistors]
          1/R_total = 1/R1 + 1/R2 + ...         [general]
```

**Intuition:**
- Series: resistances add. More pipe length = more opposition.
- Parallel: conductances (1/R) add. More pipes in parallel = easier flow = lower total R.

**Shortcuts:**
- Two equal resistors in parallel = half the value.
- Large R in series with small R ≈ large R.
- Large R in parallel with small R ≈ small R.
- n equal resistors in parallel = R/n.

**Where you see it:** Resistor networks everywhere — bias circuits, feedback dividers, current limiters, pull-ups.

### Power Dissipation

**The math:**
```
P = IV = I²R = V²/R
```

**Intuition:** All three forms are Ohm's law substitutions of P = IV. Pick whichever matches what you know. Power is always dissipated as heat in a resistor — never returned to the circuit. Resistor power ratings (1/8W, 1/4W, 1/2W, 1W) must not be exceeded or the component burns.

**Where you see it:** Heatsink design, PCB thermal analysis, selecting resistor wattage, current-sense resistors.

---

## 1.2.3 Voltage Dividers

### The Circuit

**What it is:** Two resistors in series from V_in to ground, output taken from the middle node. The single most important passive circuit fragment.

**The math:**
```
V_out = V_in * R2 / (R1 + R2)
```

**Intuition:** The output is the fraction of total resistance that is "below" the tap. If R2 is 1/3 of total, you get 1/3 of V_in. Voltage divides in proportion to resistance.

**Loading effect:** Connecting a load R_L across R2 changes the effective lower resistance to R2 || R_L, which is always less than R2. Output voltage drops. To minimize this: R_L >> R2 (rule of thumb: 10x or more). This is *circuit loading*.

**Where you see it:** ADC input scaling (12V signal → 3.3V ADC), bias networks, volume controls, level shifting, sensor bridges.

> **Embedded tie-in:** A pull-up resistor on a GPIO with a button to ground is a voltage divider. The "pull-up" is R1, the button resistance (near zero when pressed) is R2. Open: V_out ≈ V_supply. Pressed: V_out ≈ 0V.

---

## 1.2.4 Voltage Sources and Current Sources

### Ideal vs. Real Sources

**Voltage source:** Maintains a fixed voltage regardless of current drawn. Ideal internal resistance = 0. Real batteries are an ideal voltage source + small series resistance (e.g., 9V battery ≈ 3Ω internal R).

**Current source:** Maintains a fixed current regardless of load voltage. Ideal internal resistance = ∞. Hates open circuits (voltage spikes to infinity trying to push current nowhere).

**Intuition:**
- Voltage sources like open circuits (no current to supply). Hate shorts (infinite current demanded).
- Current sources are exactly opposite.
- Real signal sources (oscillators, sensors, amplifiers) all have an internal resistance — they're imperfect voltage sources. Thevenin captures this.

---

## 1.2.5 Thévenin Equivalent Circuit

### The Theorem

**What it is:** Any two-terminal network of resistors and voltage sources can be replaced by a single voltage source V_Th in series with a single resistance R_Th.

**The math:**
```
V_Th = V_open_circuit           (voltage at terminals with nothing connected)
R_Th = V_open_circuit / I_short_circuit

For a voltage divider driven by V_in:
  V_Th = V_in * R2 / (R1 + R2)
  R_Th = R1 || R2 = (R1 * R2) / (R1 + R2)
```

**How to find R_Th:** Kill all independent sources (short voltage sources, open current sources), then find the resistance looking into the terminals. For simple resistor networks this is often faster than computing I_short.

**Intuition:** Thévenin tells you two things about a source: what voltage it tries to produce (V_Th) and how "stiff" it is (R_Th). A low R_Th = stiff source — output barely sags under load. A high R_Th = soft source — output droops badly when loaded. To avoid loading: R_load >> R_Th.

**Where you see it:** Every signal source has a Thévenin equivalent. Op-amp outputs: R_Th ≈ milliohms. GPIO driving HIGH: R_Th ≈ 25–50Ω. A 10k/10k voltage divider: R_Th = 5kΩ — terrible voltage source.

### Maximum Power Transfer (Exercise 1.11)

**The result:** Power delivered to R_load is maximized when R_load = R_Th (source resistance).

**The math:** Starting from P = V_Th² * R_L / (R_Th + R_L)², take dP/dR_L = 0 using the quotient rule. Setting the numerator to zero yields R_L = R_Th.

**Intuition:** If R_L is too small, most voltage drops across R_Th. If R_L is too large, current is small. Maximum power is the balance point. Note: this is *not* the same as maximum efficiency — at matched impedance, half the power is wasted in R_Th (50% efficiency). For power delivery (batteries, audio amplifiers, RF transmitters) you match impedances. For signal fidelity (voltmeters, ADC inputs) you want R_load >> R_source to minimize loading, not to maximize power.

**Where you see it:** RF antenna matching, audio power amplifiers driving speakers, transmission lines.

---

## 1.2.6 Small-Signal (Dynamic) Resistance

### What it is

For nonlinear devices, V/I is not constant. We care about how the device responds to *small changes* around its operating point.

**The math:**
```
r_dyn = dV / dI ≈ ΔV / ΔI
```

**Intuition:** A zener at 10mA might have V_Z = 5.1V and r_dyn = 10Ω. A 10% change in current (1mA) causes ΔV = 10Ω × 1mA = 10mV change in output. Good regulation. For small signals, the zener acts like a 10Ω resistor in a voltage divider with the series dropping resistor.

**Why it matters:** This concept is the foundation of transistor small-signal models in Ch. 2. A BJT in its active region has a small-signal resistance r_e = V_T/I_C ≈ 26mV/I_C at room temperature.

**Where you see it:** Diode forward drop variation with current, zener regulation quality, LED brightness variation.

---

## 1.2.7 An Example: "It's Too Hot!"

### The Concept

A thermistor (temperature-dependent resistor) in a voltage divider. As temperature rises, the thermistor resistance changes, and V_out at the tap changes accordingly. The Thévenin equivalent of the divider feeds a comparator or ADC.

**Intuition:** This example ties together voltage dividers, Thévenin equivalents, and small-signal thinking in one practical design. The nonlinearity of NTC (negative temperature coefficient) thermistors is handled by choosing the companion resistor at the midpoint of the operating range.

**Where you see it:** Temperature sensing on MCU boards, fan control circuits, battery management systems (cell temperature monitoring).
