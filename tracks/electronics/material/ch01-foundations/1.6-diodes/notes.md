# Ch. 1.6 — Diodes and Diode Circuits
*Art of Electronics, pp. 31–40 (§1.6.1–1.6.8)*

---

## 1.6.1 Diodes

### What Makes a Diode Different

**What it is:** A two-terminal passive *nonlinear* device. It's the first nonlinear device introduced in the book. Resistors, capacitors, and inductors are all linear (double the applied signal → double the response). The diode is not.

**The V-I curve:** Current flows easily in one direction (forward), almost not at all in the other (reverse). The anode (A) is the arrow terminal; current flows anode to cathode. See Fig. 1.54 and 1.55.

**The math:**
```
Forward drop: V_f ≈ 0.6 V for silicon at ~10 mA
  (anode is ~0.6 V more positive than cathode)

Reverse current: nanoamp range for general-purpose diodes
  (scales differ hugely — note the graph's scale change)

Reverse breakdown (PIV): typically 75 V for 1N4148
  Almost never reached in normal use — exception: zener diodes
```

**Intuition:** Think of the diode as a one-way valve with a voltage toll. Below ~0.6 V forward bias, nothing passes. Above that, it conducts freely. The forward voltage drop is roughly constant (not a fixed resistance) — it rises logarithmically with current, so doubling current raises V_f by only ~18 mV.

**Two things a diode is not:**
- It doesn't have a resistance (doesn't obey Ohm's law).
- It doesn't have a Thévenin equivalent (the book calls this out explicitly before moving to circuits).

**Where you see it in real hardware:** Every power supply, every relay driver, every AM radio detector, every logic OR gate made from discrete parts.

> **Embedded tie-in:** The 0.6 V drop matters when protecting MCU I/O pins. A series diode to a clamping rail blocks overvoltage but adds that drop into your protection budget.

### Representative Diodes (Table 1.1)

| Part | V_R max | I_F typ | V_F @ I_F | Cap | Notes |
|------|---------|---------|-----------|-----|-------|
| PAD5 | 45 V | 0.25 pA @ 20 V | 800 mV @ 1 mA | 0.5 pF @ 5 V | Metal + glass can |
| 1N4148 | 75 V | 10 nA @ 20 V | 750 mV @ 10 mA | 0.9 pF @ 0 V | Jellybean signal diode |
| 1N4007 | 1000 V | 50 nA @ 800 V | 800 mV @ 250 mA | 12 pF @ 10 V | 1N4004 lower V |
| 1N5406 | 600 V | <10 µA @ 600 V | 1.0 V @ 10 A | 18 pF @ 10 V | Heat-through leads |
| 1N6263 (Schottky) | 60 V | 7 nA @ 20 V | 400 mV @ 1 mA | 0.6 pF @ 10 V | See also 1N5711 |
| 1N5819 (Schottky) | 40 V | 10 µA @ 32 V | 400 mV @ 1000 mA | 150 pF @ 1 V | Jellybean |
| 1N5822 (Schottky) | 40 V | 40 µA @ 32 V | 480 mV @ 3000 mA | 450 pF @ 1 V | Power Schottky |
| MBRP40045 (Schottky) | 45 V | 500 µA @ 40 V | 540 mV @ 400 A | 3500 pF @ 10 V | Moby dual Schottky |

**Schottky key advantage:** lower forward voltage AND zero reverse-recovery time, but more capacitance.

---

## 1.6.2 Rectification

### Half-Wave Rectifier

**What it is:** A single diode in series with the load. Only positive half-cycles pass (Fig. 1.56). The output is a string of humps (Fig. 1.57) — "dc" only in the sense that it never reverses polarity.

**Intuition:** Think of the diode as a one-way gate. Negative half-cycles are blocked. You use only half the input waveform — hence "half-wave."

**Where you see it:** Rarely used alone in practice because the ripple is large and transformer efficiency is poor. Sometimes used in simple trickle chargers.

### Full-Wave Bridge Rectifier

**What it is:** Four diodes in a bridge arrangement (Fig. 1.58). Both half-cycles of the input are used — the bridge steers negative half-cycles around to appear positive at the output (Fig. 1.59). Ripple frequency is 2× the line frequency.

**The math:**
```
Two diodes are always in series with the input during conduction.
Peak output = V_peak − 2 × V_f   (two diode drops, ~1.2 V total for silicon)
Ripple frequency = 2f  (120 Hz for 60 Hz mains)
```

**Intuition:** The bridge "flips" negative half-cycles. At any moment, two diodes conduct — one on the top path, one on the bottom — so you always pay two forward drops.

**Important design note:** For low-voltage power supplies, the diode drop becomes significant and must be accounted for. Active synchronous switching can eliminate the drop (mentioned in footnote 29; covered in §9.5.3B).

**Where you see it:** Standard topology for AC-to-DC power supplies. Bought as a prepackaged module (bridges available from 1 A to 25 A+, 100 V to 1000 V PIV).

> **Embedded tie-in:** When powering a microcontroller from a wall adapter, the DC rail comes from a bridge + filter cap. Understanding that the diode drop reduces your available rail is essential when designing for low-voltage operation.

---

## 1.6.3 Power-Supply Filtering

### The Filter Capacitor

**What it is:** A large capacitor placed across the rectifier output (Fig. 1.60). It charges to the peak voltage during diode conduction, then supplies current to the load between charging cycles.

**The math:**
```
Ripple voltage (peak-to-peak):

  ΔV = I_load / (f × C)      (half-wave)
  ΔV = I_load / (2f × C)     (full-wave, ripple at 2f)

Derived from:  I = C × dV/dt  →  ΔV = I × Δt / C = I / (f × C)
```

**Derivation intuition (Fig. 1.61):** Assume load current is constant (it will be, for small ripple). During the discharge interval (~1/f), the cap loses Q = I × t coulombs. Since Q = C × ΔV, you get ΔV = I/(fC). Don't memorize — derive it. The book explicitly says not to waste brain cells memorizing these.

**Approximation limits:** The exact discharge is exponential only if the load is a resistor. Voltage regulators look like constant-current loads, so the linear approximation (ΔV = I/(fC)) is actually more accurate than the exponential formula for real power supplies. The approximation errs toward overestimating ripple — conservative and safe.

**Sizing rule:**
```
R_load × C >> 1/f
(time constant of discharge >> period between recharging events)
```

**Where you see it:** The large electrolytic capacitors in any AC-to-DC supply. Bigger cap → less ripple → smoother DC.

> **Embedded tie-in:** If your MCU resets when a motor starts, the motor in-rush is drooping the supply rail. The fix is more filter capacitance (and possibly a better regulator). Understanding ΔV = I/(fC) lets you calculate how much cap you need.

**Exercise 1.20** (from book): Design a full-wave bridge rectifier to deliver 10 V dc with less than 0.1 V (pp) ripple into a 10 mA load. The bridge rectifier circuit (Fig. 1.62) shows that V_dc = √2 × V_sec(rms), with 0.6 V diode drops. Use the correct ripple frequency (120 Hz, not 60 Hz) in your calculation.

---

## 1.6.4 Rectifier Configurations for Power Supplies

### A. Full-Wave Bridge

**What it is:** The standard configuration (Fig. 1.62). Packaged as a module. Available up to 25 A+ average current, 100–600 V (even 1000 V) minimum breakdown voltage ratings. The smallest come at 1 A average.

### B. Center-Tapped Full-Wave Rectifier

**What it is:** Two diodes + a center-tapped transformer (Fig. 1.63). Only one diode is in series with the load at any time — one forward drop instead of two.

**Why it's less efficient than it looks:** Each half of the transformer secondary is used only half the time. To deliver the same output power, each half-winding must carry the full load current during its half-cycle — but the I²R heating in the windings goes like the square of current. The result: transformer winding losses are twice as high as for an equivalent bridge configuration. You need a transformer rated 1.4× larger (√2 larger) in current than the bridge equivalent.

**Exercise 1.21** (from book): Using the waveform of Fig. 1.64 (2 A pulses, ~1 ms wide, 1 A average): what fuse rating is minimum? Hint — a fuse "blows out" by I²R heating of a metallic link. It responds to I² averaged over many cycles (RMS current), not average current. Work out the RMS of the discontinuous waveform.

### C. Split Supply

**What it is:** Center-tapped full-wave driving two filter caps to give ±V outputs (Fig. 1.65). Efficient because both halves of the winding are used. Many analog circuits need split supplies (op-amps, audio amplifiers).

### D. Voltage Multipliers

**What it is:** A voltage doubler (Fig. 1.66) is two half-wave rectifier circuits in series. Both halves of the input waveform are used — ripple frequency is 2× the ac frequency (120 Hz for 60 Hz input). Can be extended to triplers, quadruplers, etc. (Fig. 1.67). Extended to arbitrary N, this is a **Cockcroft-Walton generator**.

**Where you see it:** Particle accelerators, image intensifiers, air ionizers, laser copiers, bug zappers. Any application needing high voltage but very little current.

---

## 1.6.5 Regulators

### Why Brute-Force Filtering Falls Short

**Three disadvantages of using only big capacitors:**
1. Required capacitance may be prohibitively bulky and expensive.
2. Current flows only in short pulses near the top of the sinusoid (conduction angle very narrow) — this causes large I²R heating in transformer and diode (more than continuous current would cause).
3. Even with ripple reduced, output voltage still varies with ac input voltage (roughly proportional to it) and with load current (finite Thévenin resistance of the supply).

### Linear Regulation

**Better approach:** Use enough capacitance to reduce ripple to ~10% of the dc voltage, then use an active feedback circuit to eliminate the remaining ripple (Fig. 1.68). The feedback circuit monitors the output and adjusts a controllable series resistor (transistor) to hold the output constant. This is a **linear regulated dc power supply**.

**Where you see it:** Available as cheap IC regulators (under $1). Can be made adjustable and self-protecting (short circuit, overload, over-temperature). Internal resistance in milliohms. Chapter 9 covers these in depth.

> **Embedded tie-in:** The 7805, LM317, LDO regulators on every development board are linear regulators. Understanding that the pass transistor dissipates (V_in − V_out) × I_load as heat helps you size heatsinks and understand why switchers exist.

---

## 1.6.6 Circuit Applications of Diodes

### A. Signal Rectifier

**What it is:** A diode used to extract one polarity from a waveform — not for a power supply, but to process a signal. Example: rectify the differentiated output of a square wave to get pulses corresponding to only the rising edges (Fig. 1.69).

**Key constraint:** The 0.6 V forward drop matters here. For square waves smaller than 0.6 V pp, the circuit gives no output. Two solutions:
- Use a **Schottky diode** (forward drop ~0.25 V instead of 0.6 V).
- Use a **compensation circuit** (Fig. 1.70): diode D1 provides 0.6 V of bias to hold D2 at the threshold of conduction. Using a diode (rather than a voltage divider) for bias has three advantages: (a) nothing to adjust, (b) compensation is nearly perfect, (c) changes in forward drop with temperature are automatically cancelled because both diodes track together.

**Where you see it:** AM demodulators, envelope detectors, peak detectors, edge-detection circuits.

### B. Diode Gates

**What it is:** Diodes can implement logic — specifically, passing the *higher* of two voltages without affecting the lower. This is a diode OR gate.

**Key example — battery backup (Fig. 1.71):** A real-time clock chip (e.g., NXP PCF8563, Seiko S-35390A) must keep running even when main power is off. D1 connects +5 V (when on) through to the chip; D2 connects a +3 V lithium coin cell (CR2032). When +5 V is present, D1 conducts and D2 is reverse-biased — battery does nothing. When +5 V disappears, D2 takes over without interruption.

**The numbers:** The RTC draws 0.25 µA. From a CR2032 coin cell this gives a 1-million-hour life (about 100 years).

> **Embedded tie-in:** This exact circuit appears on microcontroller boards with RTC chips. The diode OR is why the battery backup works passively with no firmware involvement.

### C. Diode Clamps

**What it is:** A circuit that prevents a signal from exceeding a voltage limit. The basic clamp (Fig. 1.72) prevents output from exceeding ~+5.6 V (5 V rail + one diode drop). Has no effect on voltages below that threshold. Only limit: input must not go negative enough to exceed the reverse breakdown voltage (~−75 V for 1N4148).

**The series resistor:** Limits diode current during clamping. Side effect: adds ~1 kΩ of source resistance (Thévenin sense) to the signal. This is a compromise between low source impedance and low clamping impedance.

**Voltage-divider reference clamp (Fig. 1.73):** The diode's cathode is set by a voltage divider rather than a fixed supply rail. Lets you set an arbitrary clamp voltage. **Critical requirement:** the Thévenin resistance of the divider (R_vd) must be small compared to the series resistor R — otherwise the divider "sags" when the diode conducts (Fig. 1.74, 1.75, 1.76). This is the "stiff reference" requirement.

**Better reference options:** A transistor or op-amp buffer driving the clamp reference. This avoids consuming large currents while providing a low-impedance reference. Chapter 4 covers this.

**AC stiffening trick:** Add a bypass capacitor across the lower divider resistor (1 kΩ). For time-varying signals, the cap makes the divider look like it has very low Thévenin impedance at signal frequencies. A 15 µF cap makes the impedance < 10 Ω at frequencies above 1 kHz. This works well for AC signals; it does nothing at dc.

**DC restoration (Fig. 1.77):** A clamp applied to a capacitively-coupled (ac-coupled) signal. The capacitor charges to the signal's peak, holding one extreme of the waveform at a fixed voltage. Critical for circuits whose inputs look like grounded emitters (next chapter) — without dc restoration, an ac-coupled signal's dc level wanders to the capacitor's charge.

**Where you see it:** Diode clamps are standard on ALL inputs of contemporary CMOS digital logic ICs. Without them, static electricity discharges destroy the delicate input circuits during handling.

**Exercise 1.22** (from book): Design a symmetrical clamp that confines a signal to the range −5.6 V to +5.6 V.

### D. Limiter

**What it is:** Back-to-back diodes from output to ground (Fig. 1.78). Limits output swing to roughly ±0.6 V (one diode drop in either polarity).

**Why ±0.6 V is useful:** If the next stage is a high-gain amplifier (gain = 1000, operating from ±15 V supplies), its input must stay within ±15 mV to avoid saturating the output. A limiter at the input clips any large signal before it causes saturation. Fig. 1.79 shows limiting of large sinusoids and spikes.

**Where you see it:** Input protection for high-gain amplifiers. Common on oscilloscope input stages.

### E. Diodes as Nonlinear Elements

**What it is:** The diode's V-I curve is an exponential. Forward current is proportional to e^(V/V_T). This nonlinearity can be *exploited* rather than just tolerated.

**Logarithmic converter (Fig. 1.80):** Drive a diode with a current source. The voltage across the diode is proportional to log(I_in). Because V hovers near 0.6 V with only small variations reflecting input current changes, you can replace the current source with a resistor if V_in >> 0.6 V (Fig. 1.81).

**The math:**
```
V_out ∝ log(I_in)

For the resistor approximation:
  I_in ≈ V_in / R  (valid when V_in >> 0.6 V)
  → V_out ∝ log(V_in)
```

**Temperature problem:** Silicon diode forward voltage drops ~2 mV/°C. The log output drifts with temperature.

**Compensation (Fig. 1.82):** Use a matched pair of diodes (D1, D2). D1 provides bias to hold D2 in conduction. The forward drops cancel because both diodes track identically with temperature — except for the difference due to the input current through D1. R1 sets D2's quiescent current. This gives temperature-insensitive log conversion. Better op-amp-based log converters are in Chapter 2x.

**Where you see it:** Audio level compression circuits, signal processing, measurement instruments requiring wide dynamic range (log amplifiers in RF power meters, pH meters).

---

## 1.6.7 Inductive Loads and Diode Protection

### Inductive Kick

**What it is:** When a switch opens in series with an inductor, the inductor tries to maintain current flow. Since V = L dI/dt, turning off the current instantly would require infinite voltage. What actually happens: the voltage across the inductor rises until it finds a path for current — which may mean arcing across the switch contacts or destroying a transistor.

**The math:**
```
V = L × dI/dt

Cutting off current instantly → dI/dt → ∞ → V → ∞
In practice: voltage rises until breakdown occurs somewhere
```

**Intuition (Fig. 1.83):** The inductor is like a flywheel — it resists changes in current. Close the switch → current ramps up. Open the switch → the inductor *insists* on keeping current flowing, driving point B above ground (or above the supply) until something breaks down.

### The Flyback Diode (Fig. 1.84)

**What it is:** A diode placed across the inductor, cathode toward the positive supply. When the switch is ON, the diode is reverse-biased — does nothing. When the switch is turned OFF, the inductor's kick forward-biases the diode, clamping the spike to V_supply + V_f (~0.6 V above supply). Current decays exponentially through the inductor's own winding resistance.

**Selection:**
- Speed: 1N4004 is fine for nearly all cases (handles the steady-state inductor current, which equals the initial diode current at turnoff).
- Faster decay needed: put a resistor across the inductor instead of the supply. The resistor increases the voltage clamp (V_supply + I×R), which drives faster decay. Choose R so V_supply + I×R stays below the switch's maximum allowed voltage.
- Fastest decay: use a zener (or TVS) in series with the flyback diode. Gives linear ramp-down of current rather than exponential. See Chapter 1x for discussion.

**AC inductive loads (transformers, relays):** The simple flyback diode doesn't work because it would conduct on every half-cycle. Use an RC snubber instead (Fig. 1.85): typical values 100 Ω + 0.05 µF for small inductive loads from the AC powerline. Include a snubber in every instrument that runs from AC power — the power transformer is inductive.

**Alternatives to the RC snubber:**
- Bidirectional TVS (transient voltage suppressor) zener — clamps both polarities.
- MOV (metal-oxide varistor) — cheap, looks like a disk ceramic capacitor, behaves like a bidirectional zener. Available 10–1000 V. Can handle transient currents of thousands of amps.

**Where you see it:** Every relay driver in embedded systems. GPIO pin driving a relay coil must have a flyback diode — without it, the GPIO is destroyed in nanoseconds. No software protection is fast enough.

> **Embedded tie-in:** This is mandatory when driving relays, solenoids, motors, or any coil from a transistor or GPIO. The diode goes across the coil, cathode toward the positive supply. Use a 1N4001 for 50 V / 1 A applications; use a Schottky for high-frequency switching (MOSFETs in a buck converter, etc.). On PCBs, place the diode physically close to the coil — long traces add inductance and reduce the protection.

---

## 1.6.8 Interlude: Inductors as Friends

### Resonant Charging — Lossless Capacitor Charging

**What it is:** The book uses this section to show inductors in a positive role (Fig. 1.86). Charging a capacitor from a voltage source V_in through a resistor wastes 50% of the energy as heat in the resistor — always, regardless of resistor value. Using an inductor in series with the capacitor (plus a diode to stop the oscillation after one half-cycle) charges the capacitor to 2×V_in with *no energy loss* (ideal components).

**The math:**
```
Resistive charging (Fig. 1.86A):
  50% efficiency — half the energy is lost in R, always

Resonant (LC) charging (Fig. 1.86B):
  Capacitor charges to 2 × V_in
  Charging completes at t_f = half-period of resonant frequency
  f_resonant = 1 / (2π√LC)
  100% efficiency (ideal components)
```

**Intuition:** The inductor acts like a spring. Current builds up, overshoots the equilibrium, and the capacitor ends up at twice the supply voltage. The diode stops the oscillation after the first half-cycle — without it the circuit would ring back and forth between 0 and 2V_in indefinitely.

**Real-world applications:** Flashlamps and stroboscopes use resonant charging. Advantages: (a) capacitor fully charged between flashes (spaced no closer than t_f); (b) no current flows immediately after discharge — lets the flashlamp "quench" after each flash.

> **Embedded tie-in:** Switching regulators (buck, boost, flyback) use inductors as energy storage, not just filtering. The boost converter charges an inductor from V_in, then dumps the energy into a capacitor at a higher voltage. Understanding resonant behavior is prerequisite to understanding switcher stability and EMI.

**The loudspeaker equalization example (Fig. 1.87):** A loudspeaker has a non-flat frequency response. A compensating filter — built from reactive components (inductors, capacitors) — has the inverse response, so the combined system is flat across the audible range (20 Hz–20 kHz). This motivates the next section (§1.7, impedance and reactance): circuits with reactive components have frequency-dependent behavior that can be engineered deliberately.
