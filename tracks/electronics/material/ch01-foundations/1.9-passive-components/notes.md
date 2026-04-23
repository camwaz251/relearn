# Ch. 1.9 — Other Passive Components
*Art of Electronics, pp. 56–64 (§1.9.1–1.9.5)*

---

## 1.9.1 Electromechanical Devices: Switches

### A. Toggle Switches

**What it is:** The classic toggle switch comes in several configurations depending on number of poles and throws:
- **SPST** — single-pole single-throw. One input, one output. Simple on/off.
- **SPDT** — single-pole double-throw. One input, two possible outputs.
- **DPDT** — double-pole double-throw. Two poles switched simultaneously.

Toggle switches are also available with "center OFF" positions and with up to four poles switched simultaneously. Toggle switches are always **break-before-make** — the moving contact never connects to both terminals at once (important in SPDT switches).

**Figures 1.117 and 1.119** show common switch types and the standard schematic symbols.

**Where you see it in real hardware:** Panel controls, mode selection, power switches on instruments and enclosures.

---

### B. Pushbutton Switches

**What it is:** Useful for momentary-contact applications. Drawn schematically as shown in Figure 1.120.
- **NO (normally open, form A):** open at rest, closes when pressed.
- **NC (normally closed, form B):** closed at rest, opens when pressed.
- **SPDT (form C):** common terminal plus NC and NO terminals.

In the electrical (as opposed to electronic) industry: form A = SPST NO, form B = SPST NC, form C = SPDT. Momentary-contact switches are always break-before-make.

**Where you see it in real hardware:** Reset buttons, mode select, keyboard keys, limit switches in machines.

> **Embedded tie-in:** Every physical button into a microcontroller needs debouncing — contacts bounce for 1–20 ms before settling. The MCU sees this as multiple rapid edges. Fix in hardware (RC lowpass) or software (read pin, wait 10–20 ms, read again).

---

### C. Rotary Switches

**What it is:** Many poles, many positions. Often sold as kits with individual wafers and shaft hardware. Two flavors:
- **Shorting (make-before-break):** briefly connects old and new positions together. Useful to prevent open circuits between switch positions (circuits can go wrong with unconnected inputs).
- **Non-shorting (break-before-make):** disconnects old before connecting new. Required when the separate lines must never be connected to each other.

Both types can be mixed on the same switch.

**Rotary encoders:** A related device — an electromechanical panel-mounting device that creates N pulse pairs per full rotation of the knob. Available in mechanical-contact or electro-optical versions; typically 16 to 200 pulse pairs per revolution. Optical versions cost more but last indefinitely.

**Where you see it in real hardware:** Multi-position mode selectors, channel selectors on instruments, audio source selectors.

---

### D. PC-Mounting Switches (DIP Switches)

**What it is:** Little arrays of switches on PCBs. Called **DIP switches** (borrowing the DIP IC package name). Increasingly available in compact surface-mount packages. Common types (see Figure 1.118):
- SPST arrays (side-action toggle, rocker, slide)
- Coded rotary switches (hexadecimal output, 4-bit binary)
- Jumper/header blocks with slide-on "shunts" as a simpler substitute

**Where you see it in real hardware:** Board configuration — setting I²C addresses, enabling/disabling features, selecting operating modes without reprogramming.

---

### E. Other Switch Types / Ratings

Hall-effect switches, reed switches, proximity switches. All switches carry maximum current and voltage ratings — a small toggle might be rated at 150V and 5A.

**Critical point:** Inductive loads drastically reduce switch life due to arcing at turn-off. Always operate a switch *below* its maximum ratings.

**Dry switching:** When switching low-level signals, use a switch designed for this. Many switches rely on substantial current flow to clean contact oxides — without it you get noisy, intermittent contact. Gold-plated contacts handle dry switching.

---

### F. Switch Circuit Example

**Figure 1.121** shows a car door warning buzzer: the buzzer sounds if one OR the other door is open AND the driver is seated. Both door switches and the seat switch are SPST-NO. The circuit implements the logic OR and AND directly with switches.

**Figure 1.122** shows the electrician's "three-way" switch: two SPDT switches wire a ceiling lamp so either of two entrances can turn it on or off. Generalized to N switches: two SPDTs and N−2 DPDTs.

---

## 1.9.2 Electromechanical Devices: Relays

### Electromechanical Relay (EMR)

**What it is:** An electrically controlled switch. A coil pulls an armature (to close contacts) when sufficient coil current flows. Available in "latching" and "stepping" varieties. Coil voltages from 3V up to 115V (ac or dc). "Mercury-wetted" and "reed" relays are intended for high-speed (~1 ms) applications. Giant relays switch thousands of amps for power utilities.

**Key specs to know:**
- Coil voltage: 3V, 5V, 12V, 24V, 115V (ac or dc)
- Contact forms: SPST-NO, SPDT, DPDT, latching

**Where you see it in real hardware:** Anywhere you need complete **galvanic isolation** between control signal and switched circuit — a 3.3V MCU GPIO switching a 120V AC load. Also remote switching and high-voltage/high-current switching.

> **Embedded tie-in:** GPIO cannot drive a relay coil directly (coil current 10–100 mA, GPIO max ~20 mA). Use a BJT or MOSFET driver. Always add a **flyback diode** across the coil (cathode to +V, anode to −): when the coil is de-energized its collapsing magnetic field generates a large reverse voltage spike that destroys transistors without the diode.

---

### Solid-State Relay (SSR)

**What it is:** A semiconductor electronic switch turned on by an LED — no moving parts. SSRs operate rapidly, without contact bounce, and with no mechanical wear. They turn on AC power **at the moment of zero voltage** and turn off **at zero current** — this zero-crossing switching reduces electrical noise and EMI.

**Trade-offs vs. EMR:**
- Better: no bounce, no lifetime limit, faster, silent
- Worse: higher cost, higher on-resistance than mechanical contacts

**The book's view:** SSRs provide better performance and reliability than mechanical relays, at greater cost. Primary uses of relays (either type) are remote switching and high-voltage/high-current switching where isolation is essential. For lower-voltage signal switching inside a circuit, transistors (Ch. 2 and 3) are preferred over relays.

---

## 1.9.3 Connectors

**What connectors do:** Bring signals in/out of instruments, route signal and DC power between parts of an instrument, allow circuit boards and modules to be unplugged and replaced. The book notes connectors are usually "the most unreliable part" of any piece of electronic equipment.

---

### A. Single-Wire Connectors

Simple **pin jack** or **banana jack** — used on multimeters, power supplies. Inexpensive but not as useful as shielded-cable or multiwire connectors. The humble **binding post** is another form.

---

### B. Shielded-Cable Connectors

**BNC (bayonet Neill–Concelman):** The most popular shielded connector for instruments. Quarter-turn bayonet lock; adorns most instrument front panels. Connects shield (ground) and inner (signal) conductor simultaneously. Available in panel-mounting and cable-terminating varieties.

Related coaxial connectors:
- **TNC** — threaded version of BNC. Close cousin, bulkier.
- **Type N** — high-performance, bulky.
- **SMA and SMB** — miniature coaxial; SMA common on RF PCBs and antennas.
- **LEMO and SMC** — subminiature coaxial.
- **MHV and SHV** — high-voltage coaxial.

**The phono jack ("RCA type"):** Used in audio equipment. The book calls it "a nice lesson in bad design" — the inner (signal) conductor mates *before* the shield when you plug it in, causing audible pops. The type-F coax "connector" (which uses the bare coax wire as the pin) is inducted into the book's "Components Hall of Infamy" (Figure 1.126).

**Figure 1.125** shows the full range of RF and shielded connectors: stereo phone jack, XLR, N, UHF, BNC, TNC, type F, MHV, SHV, audio connectors, LEMO, SMA, SMB, SC and ST (optical fiber).

---

### C. Multipin Connectors

Electronic instruments demand multiwire cables. The book lists common types:
- **IEC powerline cord connector** — simplest, three-wire
- **Type-D subminiature (D-sub):** popular and reliable. DB-9, DB-25, DB-50. DB-9 = RS-232. Seen in industrial equipment.
- **Winchester MRA series**
- **MS type (MIL-C-5015)** — rugged military-spec, hundreds of configurations
- **Flat ribbon cable + IDC** — mass-termination connectors, common on development boards

**Figure 1.123** shows the staggering variety of rectangular multipin connectors: Molex-type power connectors, 0.1" dual-row box headers (with and without latch ejectors, Wire-Wrap tails), IDC ribbon connectors, single-row 0.1" headers, AMP MODU shells, terminal blocks, Faston spade lugs, USB, RJ-45, RJ-11, D-sub (DB-9, 26-pin high-density, DB-25), VME backplane, card-edge connectors, Centronics-type, Winchester shrouded, screw-terminal barrier blocks.

**Warning:** Avoid connectors that can't tolerate being dropped on the floor (miniature hexagon connectors) or that lack a secure locking mechanism (Jones 300 series).

---

### D. Card-Edge Connectors

**What it is:** The PCB edge itself serves as the connector. Gold-plated contacts at the board edge mate with a receptacle. Used for motherboard memory modules (DIMMs), PCIe cards, and VME backplane systems (Figure 1.123, upper right). May have 15 to 100+ connections.

Connection options: solder to a motherboard/backplane, use standard solder-lug edge connectors, or use "two-part" PCB connectors where one part solders to the board and mates with the other part on the backplane. VME (VersaModule Eurocard) uses this system.

---

### Figures 1.124

Circular connectors: MS-type (MIL-C-5015) rugged, Supericon 50A locking XLR, weatherproof (Switchcraft EN3), 12 mm video (Hirose RM), circular DIN, mini-DIN, 4-pin microphone, locking 6-pin (Lemo), microminiature 7-pin shielded (Microtech EP-7S), 2-pin shrouded (Litton SM), 2.5 mm power, banana, pin jack.

---

## 1.9.4 Indicators

### A. Meters

Two main types for reading voltage or current:
- **Moving-pointer (analog):** time-honored, less expensive, less accurate.
- **Digital readout:** more expensive, more accurate.

Both types cover a wide variety of voltage and current ranges. Exotic panel meters read VUs (audio volume units), dB, expanded-scale AC volts (e.g., 105–130V), temperature (from a thermocouple), percentage motor load, frequency, etc. Digital panel meters often provide logic-level outputs for internal use by the instrument.

**LCD/LED panel displays:** Increasingly, a dedicated meter is replaced by an **LCD** (liquid-crystal display) or **LED panel** with a meter-like pattern. A graphic LCD display module (§12.5.3) can offer the user a choice of "meters" according to the quantity being displayed, all under the control of an embedded controller (see Chapter 15).

---

### B. Lamps, LEDs, and Displays

**Incandescent lamps:** Were the standard for front-panel indicators. Now largely replaced by LEDs.

**LEDs:** Behave electrically like ordinary diodes, but with a forward voltage drop of:
- 1.5–2 V for red, orange, and some green LEDs
- 3.6 V for blue and high-brightness green (see Figure 2.8)

Typically **2 mA to 10 mA** produces adequate brightness. LEDs are cheaper than incandescent lamps and last essentially forever. Available in four standard colors plus "white" (a blue LED with a yellow fluorescent coating). Come in panel-mounting packages; some have built-in current-limiting resistors.

**The math:**
```
R = (V_supply - V_LED) / I_LED

Example: R = (5V - 2V) / 10mA = 300Ω
```

**LEDs for digital displays:** 7-segment numeric displays; 16-segment alphanumeric displays; dot-matrix displays. When more than a few digits or characters need to be displayed, **LCDs are generally preferred**: line-oriented arrays (e.g., 16 chars × 1 line, up to 40 chars × 4 lines), simple interface for sequential or addressable entry of alphanumeric characters and symbols. Inexpensive, low power, visible even in sunlight. Back-lit versions work in subdued light but are not low power. More on opto-electronic devices in §12.5.

> **Embedded tie-in:** When driving an LED directly from a GPIO, check the pin's source/sink current limit in the datasheet. Most MCUs can source/sink 4–20 mA per pin. Always use a current-limiting resistor — never connect an LED to a GPIO without one. For multiple LEDs or high-brightness types, use a transistor or LED driver IC.

---

## 1.9.5 Variable Components

### A. Variable Resistors (Potentiometers)

**What it is:** Also called volume controls, pots, or trimmers. Three-terminal variable resistor with a rotatable "wiper" contact sliding along a resistive track (Figure 1.127 shows the schematic symbol, with CW and CCW ends marked).

Classic panel type is the **2-watt AB potentiometer** — uses the same carbon-composition material as fixed resistors, with a rotatable wiper. Also available with ceramic or plastic resistive elements (improved characteristics). **Multiturn types** (3, 5, or 10 turns) have counting dials for improved resolution and linearity. **Ganged pots** — several independent sections on one shaft — available in limited variety for applications that need it. Figure 1.8 shows a representative selection.

**Trimmer pots:** For use inside an instrument rather than on the front panel. Single-turn and multiturn styles, most intended for PCB mounting. For calibration adjustments of the "set-and-forget" type.

**Book's warning:** "Resist the temptation to use lots of trimmers in your circuits. Use good design instead."

**Don't use a pot as a precision resistor:**
- Pots are not as stable as 1% resistors
- They may not have good resolution (can't be set to a precise value)

**Correct approach for a precise settable resistance:** Use a 1% (or better) precision resistor in series with a small trimmer pot, with the fixed resistor contributing most of the resistance. Example: need 23.4 kΩ → use a 22.6 kΩ 1% fixed resistor in series with a 2 kΩ trim pot.

**Digital potentiometers:** An all-electronic version using an array of transistor switches selecting taps along a chain of fixed resistors. Made as ICs by Analog Devices, Maxim/Dallas, and Xicor — up to 1024 steps, available as single or dual units, some **nonvolatile** (remember last setting after power-off). Application: consumer electronics (TV, stereo) where volume is adjusted by infrared remote control rather than by turning a knob; see §3.4.3E.

**Other variable-resistance approaches:** FETs as voltage-controlled resistors (§3.2.7), optoresistors (§12.7), transistors as variable-gain amplifiers.

---

### B. Variable Capacitors

**What it is:** Primarily confined to smaller capacitance values (up to about 1000 pF). Commonly used in RF circuits. Trimmer variable capacitors are available for in-circuit adjustments, in addition to the panel type for user tuning. Figure 1.128 shows the schematic symbol.

**Varactors (varicaps, epicaps):** Diodes operated with applied reverse voltage. The reverse-biased diode junction acts as a voltage-controlled capacitor.

**Intuition:** The depletion region in a reverse-biased diode acts as the dielectric of a capacitor. Increasing reverse voltage widens the depletion region (more plate separation) → less capacitance. Decreasing reverse voltage narrows it → more capacitance.

**Where you see it in real hardware:**
- **PLLs (phase-locked loops):** The varactor in the VCO is the feedback element
- **VCOs (voltage-controlled oscillators):** Tune frequency by varying reverse voltage
- **AFC (automatic frequency control):** Compensate for frequency drift without mechanical adjustment
- **Modulators and parametric amplifiers**

---

### C. Variable Inductors

**What it is:** Usually made by moving a piece of core material within a fixed coil. Available with inductances ranging from microhenrys to henrys; typically a 2:1 tuning range for any given inductor. Also available: rotary inductors (coreless coils with a rolling contact).

---

### D. Variable Transformers

**What it is:** Variable transformers operated from the 115V AC line. Usually configured as **autotransformers** — one winding with a sliding contact, so they are **not electrically isolated from the powerline**. Commonly called **Variacs** (General Radio's trade name; also made by Technipower, Superior Electric, and others). Figure 1.129 shows a classic 5A unit.

**Output:** Typically 0 to 135V AC when operated from 115V. Available in ratings from 1 amp to 20 amps or more.

**Where you see it in real hardware:** Testing instruments that need to be subjected to powerline variations; verifying worst-case performance.

**Important Warning:** The Variac is NOT electrically isolated from the powerline — unlike a transformer. Treat the output as live mains.
