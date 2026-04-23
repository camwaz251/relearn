# Ch. 1.5 — Inductors and Transformers
*Art of Electronics, pp. 28–31 (§1.5.1–1.5.2)*

---

## 1.5.1 Inductors

### Fundamentals

**What they are:** A coil of wire that stores energy in a magnetic field. The dual of a capacitor — where caps resist voltage changes, inductors resist current changes.

**The math:**
```
V = L * dI/dt              (voltage proportional to rate of current change)
U = ½LI²                   (stored energy in magnetic field)
```

**Intuition:** An inductor tries to keep current flowing at a constant rate. Oppose any change — if current is rising, the inductor generates a voltage opposing the rise. If current is falling, it generates a voltage trying to maintain it.

The famous "inductive kick": open a switch in series with an inductor, and it generates a large voltage spike to force the current to keep flowing — potentially hundreds of volts from a 12V supply. This is the same physics as a spark plug and why you always put a flyback diode across relay/motor coils.

### Volt-Second Balance

**What it is:** In steady-state periodic operation, the average voltage across an ideal inductor must be zero over one full cycle. Otherwise the current ramps up without bound.

**Intuition:** This is the key constraint in switching power converters. A buck converter alternately applies V_in and 0V across the inductor. For equilibrium:
```
V_in * D * T = V_out * T       (volt-seconds in = volt-seconds out for lossless case)
→ V_out = D * V_in
```
where D is duty cycle. This is why switching regulators can step voltage down (or up in a boost) with high efficiency — the inductor stores and releases energy without dissipating it.

### Combining Inductors

```
Series:   L_total = L1 + L2 + ...          (like resistors)
Parallel: 1/L_total = 1/L1 + 1/L2 + ...
```
(Assuming no mutual coupling between inductors.)

### Real Inductor Limitations

- **DCR (DC resistance):** Wire has resistance. Causes I²R loss. Important for switching regulator efficiency.
- **Saturation:** At high enough current, the core material saturates — inductance drops dramatically. Must operate below I_sat specified in datasheet.
- **Self-resonant frequency (SRF):** Winding capacitance resonates with inductance. Above SRF, the "inductor" looks capacitive. Choose inductors with SRF well above your operating frequency.

> **Embedded tie-in:** Ferrite beads on MCU power pins look like inductors at RF frequencies — they filter high-frequency switching noise from the supply. They have high DCR (lossy by design) so they're not for energy storage, only for damping. The flyback diode across relay/solenoid coils is mandatory — without it, the inductive kick will destroy your MOSFET or BJT driver. Use a fast diode (Schottky or 1N4148) for speed, 1N4001–1N4007 for robust slow diodes.

---

## 1.5.2 Transformers

### Fundamentals

**What they are:** Two (or more) inductors sharing a common magnetic core. AC on the primary induces AC on the secondary through mutual inductance. Provides voltage/current scaling and galvanic isolation.

**The math:**
```
V_sec / V_pri = N_sec / N_pri = n        (turns ratio)
I_sec / I_pri = 1/n                       (current scales inversely — power in = power out)
Z_reflected = n² * Z_load                (impedance seen by primary)
```

**Intuition:** Transformers trade voltage for current. Step up voltage (n>1) → step down current by same ratio. Power is conserved (ignoring losses). The impedance transformation (n²) is why transformers are used in audio output stages — a 4Ω speaker can be transformed to look like 4kΩ to a tube amplifier output that needs a high impedance load.

### Real Transformer Limitations

- **Magnetizing inductance:** The primary draws current even with no secondary load, to maintain the magnetic flux. This is the "no-load current."
- **Leakage inductance:** Not all flux from primary links to secondary — the uncoupled portion causes voltage drop under load and voltage spikes on switching.
- **Core losses:** Hysteresis and eddy currents in the core dissipate power as heat. Proportional to frequency and flux density.
- **DC blocks:** Transformers cannot pass DC — only AC. The primary appears as a short to DC (just winding resistance), but the secondary sees nothing.

### Preview: Buck and Boost Converters

(See Figure 1.52, p. 30)

- **Buck (step-down):** Switch alternately connects inductor between V_in and ground. Inductor + output cap smooth the switching into DC. V_out = D × V_in.
- **Boost (step-up):** Inductor charges from V_in. When switch opens, stored energy is forced through a diode into the output cap. V_out = V_in/(1−D). Output is always > input.

**Intuition:** These are not transformers but they perform a similar trade-off (voltage vs. current) using an inductor as the energy storage element instead of a magnetic core. Most modern electronics use switching regulators rather than linear regulators because efficiency can be 85–95% vs 30–60%.

> **Embedded tie-in:** USB 5V → 3.3V on your dev board is almost certainly a buck converter. A boost converter generates the negative supply rail in some ADC/op-amp circuits that need ±supplies from a single +5V source. Isolated flyback converters (a transformer-based switching supply) provide galvanic isolation in medical devices and industrial equipment where ground loops are hazardous.
