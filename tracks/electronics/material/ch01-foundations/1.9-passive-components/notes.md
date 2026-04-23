# Ch. 1.9–1.10 — Other Passive Components
*Art of Electronics, pp. 56–65 (§1.9.1–1.10.1)*

---

## 1.9.1 Electromechanical Devices: Switches

### Types

**SPST (single-pole single-throw):** Simple on/off. One input, one output. The basic switch.

**SPDT (single-pole double-throw):** One input, two possible outputs. Selects between two connections. Used for "three-way" light switches, signal routing.

**DPDT (double-pole double-throw):** Two SPDT switches mechanically ganged. Can reverse motor polarity, select between two signal paths simultaneously.

**Momentary (pushbutton):**
- NO (normally open): open at rest, closes when pressed. Most common.
- NC (normally closed): closed at rest, opens when pressed.

**Rotary:** Multiple positions. Two flavors:
- Shorting (make-before-break): briefly connects old and new positions together while switching. Avoid for signal routing.
- Non-shorting (break-before-make): disconnects old before connecting new. Preferred for signal routing.

**DIP switches:** Banks of tiny SPST switches on a package. Used for configuration — setting addresses, enabling features, selecting modes without reprogramming.

### Contact Bounce

When a mechanical switch closes, the contacts bounce several times before settling. Duration: 1–20ms depending on switch. A microcontroller sees this as many rapid keypresses.

**Debouncing solutions:**
1. Hardware: RC lowpass filter (τ ≈ 5ms) on the switch input.
2. Software: read the pin, wait 10–20ms, read again. Use only if both reads match.
3. Hardware SR latch: single-pole double-throw switch with two NOR gates. Glitch-free.

> **Embedded tie-in:** Every physical button needs debouncing. The RC filter approach: 10kΩ pull-up + 10kΩ series resistor + 100nF cap to ground gives f_3dB ≈ 160Hz, settling in ~3ms. This is why buttons in firmware always require debounce logic — even "clean" switches bounce.

---

## 1.9.2 Electromechanical Devices: Relays

### Electromechanical Relay (EMR)

A coil energizes an electromagnet that physically pulls switch contacts together (or apart). Complete galvanic isolation between coil and contacts — allows a 3.3V MCU to switch a 120V AC circuit.

**Key specs:**
- Coil voltage: 3V, 5V, 12V, 24V, 115V
- Coil current: 10–100mA (always too high for direct GPIO drive)
- Contact rating: 1A, 5A, 10A, etc. at rated voltage
- Contact forms: SPST-NO, SPDT, DPDT

**Always include a flyback diode across the coil** (cathode to +, anode to −). The coil is an inductor — opening the switch generates a kick. Always.

**Driver circuit:** GPIO → BJT or MOSFET → Relay coil + flyback diode. The transistor provides current gain; the GPIO only sources/sinks a few mA to drive the transistor base/gate.

### Solid-State Relay (SSR)

LED + phototriac or photo-MOSFET. No mechanical parts, no contact bounce, no lifetime limit. Slower than mechanical relays for switching speed but much faster on/off (no bounce). Used for AC load switching (motor control, heating elements). Higher on-resistance than mechanical contacts.

---

## 1.9.3 Connectors

### Common Types

**BNC:** Coaxial, 50Ω or 75Ω. Quarter-turn bayonet lock. The standard for lab instruments (oscilloscopes, function generators, RF equipment).

**SMA/SMB:** Miniature coaxial. Screw or push-on. Common on RF PCBs, antennas, small instruments. Good to 18GHz (SMA).

**D-sub (DB-9, DB-15, DB-25):** Multi-pin connector with D-shaped shell. DB-9 = RS-232 serial. DB-25 = old parallel port. Still seen in industrial equipment.

**Pin headers (0.1" / 2.54mm pitch):** The standard for development boards and prototyping. Male pins on PCB, female Dupont wires. 0.05" (1.27mm) pitch for dense boards.

**USB:** Type-A (host), Type-B (device), Micro-B (small devices), Type-C (modern, reversible). Carries power (5V, up to 100W with PD) and data.

**Edge connectors:** Fingers directly on PCB copper. Used in memory DIMMs, PCIe cards, cartridges. Zero connector cost — the connector is just the PCB edge.

**JST:** Small polarized connectors popular in RC models and LiPo battery packs. Common on dev board battery connectors.

### Connector Design Rules

- Always include a keying mechanism (polarization) to prevent reverse insertion
- Specify current rating with margin — a 3A connector running 3A will overheat
- Coaxial connectors must match the system impedance (50Ω or 75Ω)
- Mating cycles matter for connectors on frequently-swapped cables (USB: 10k cycles typical)

---

## 1.9.4 Indicators

### LEDs

Two-terminal light-emitting diode. Conducts light when forward biased. Forward drop is 1.5–3.5V depending on color (higher for blue/white, lower for red/infrared).

**Current-limiting resistor (always required):**
```
R = (V_supply - V_LED) / I_LED

Example: R = (3.3V - 2.0V) / 5mA = 260Ω → use 270Ω standard value
```

Typical brightness: 2–20mA for indicators. High-brightness LEDs: 20–350mA.

**Driving from GPIO:** Most MCUs can source/sink 4–20mA per pin. Check datasheet. With a 270Ω resistor from a 3.3V GPIO to an LED to ground:
```
I = (3.3V - 2.0V) / 270Ω ≈ 4.8mA    (fine for most GPIOs)
```

For driving multiple LEDs or high-brightness LEDs, use a transistor or LED driver IC.

---

## 1.9.5 Variable Components

### Potentiometers

Three-terminal variable resistor. Wiper slides along a resistive track. Used as:
- **Volume controls:** Audio signal divider
- **Trim pots:** One-time calibration adjustment. Set it and forget it.
- **Panel controls:** User-adjustable gain, frequency, etc.

**Don't use as precision resistors** — poor temperature stability, mechanical wear, and resolution. For precision adjustable values, use a fixed resistor + small trim pot in series.

**Digital potentiometers:** IC with SPI/I²C control. Replace mechanical pots in systems where software-controlled resistance is needed.

### Varactors

Diodes operated in reverse bias. Capacitance varies with reverse voltage (1–50pF typically). Used in:
- **VCOs (voltage-controlled oscillators):** Tune frequency by varying reverse voltage
- **PLLs:** The varactor in the VCO is the feedback element
- **Automatic frequency control (AFC):** Compensate for drift without mechanical adjustment

**Intuition:** The depletion region in a reverse-biased diode acts as a dielectric. As reverse voltage increases, depletion region widens = more plate separation = less capacitance.

---

## 1.10.1 Surface-Mount Technology (SMT)

### What it is

Components soldered directly to pads on the PCB surface, rather than through holes. Dominates modern production — smaller, lower parasitic inductance, compatible with automated pick-and-place and reflow soldering.

### Package Sizes (Passives)

| Imperial code | Metric | Dimensions (mm) | Notes |
|--------------|--------|-----------------|-------|
| 0201 | 0603 | 0.6 × 0.3 | Microscopic. Machine only. |
| 0402 | 1005 | 1.0 × 0.5 | Tiny. Tweezers + magnification. |
| 0603 | 1608 | 1.6 × 0.8 | Common in production. |
| 0805 | 2012 | 2.0 × 1.25 | Good for hand soldering. |
| 1206 | 3216 | 3.2 × 1.6 | Easy to hand solder. |
| 2512 | 6332 | 6.3 × 3.2 | Power resistors. |

**For learning/prototyping:** Use 0805 or 1206. 0603 is manageable with practice. Anything smaller requires solder paste and a hot plate or reflow oven.

### SMT ICs

**SOT-23, SOT-89:** Small transistors and simple ICs. 3–6 pins. Manageable by hand.

**SOIC:** Standard SMT IC package. 1.27mm pitch. Easy to hand solder.

**QFP/LQFP:** Fine-pitch IC packages (0.5mm, 0.8mm pitch). Requires steady hands and flux.

**BGA (ball grid array):** No visible pins — balls underneath the package. Requires X-ray inspection and reflow. Not hand-solderable.

**Intuition:** The trend toward smaller packages is driven by density and performance (shorter leads = less parasitic inductance = better at high frequencies). The downside is that prototyping requires breakout boards or hot-air rework stations. Most new ICs are available only in SMT packages — through-hole is legacy.

> **Embedded tie-in:** When selecting components for a new design, check availability in SMT packages first. DIP through-hole parts are increasingly hard to find for modern ICs. 0805 resistors and capacitors, SOIC-8 for op-amps and regulators, SOT-23 for small transistors and LDOs — this combination covers most designs and is hand-solderable.
