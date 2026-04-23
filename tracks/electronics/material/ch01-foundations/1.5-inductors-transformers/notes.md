# Ch. 1.5 — Inductors and Transformers
*Art of Electronics, pp. 28–31 (§1.5.1–1.5.2)*

---

## 1.5.1 Inductors

### Defining equation

**What it is:** An inductor is a coil of wire (Figure 1.50). Current flowing through it
creates a magnetic field along the coil's axis. Any change in that field induces a
voltage — called back EMF — that opposes the change (Lenz's law). This is the dual
of a capacitor: for a cap, constant current produces a voltage ramp; for an inductor,
constant voltage produces a current ramp.

**The math:**
```
V = L * dI/dt                     (eq. 1.23)
```
L is the inductance in henrys (H), or mH, µH, nH in practice. 1 V across 1 H
produces a current that increases at 1 A/s.

**Intuition:** Swap the roles of V and I relative to a capacitor. A capacitor resists
voltage changes (constant current → voltage ramp). An inductor resists current changes
(constant voltage → current ramp). Same math, different quantities.

### Stored energy

**What it is:** The energy invested in ramping up the current is stored internally in
the magnetic field — not dissipated as heat. You get it back when you interrupt the
current.

**The math:**
```
U_L = ½LI²                        (eq. 1.24)
```
U_L in joules, L in henrys, I in amperes.

**Intuition:** Same form as the capacitor energy formula (½CV²). This result is at the
core of switching power conversion — the little black wall-wart power supplies and
all switching regulators store energy in an inductor's magnetic field on each switching
cycle and release it to the output. More on this in Chapter 9.

### Inductance and coil geometry

**What it is:** The inductance L of a coil equals the ratio of magnetic flux passing
through the coil to the current that produces that flux (times an overall constant).
It depends on coil geometry (diameter d, length l, number of turns n) and on the
permeability of any core material used to concentrate the field.

**The math:**

Wheeler's formula (semi-empirical, accurate to 1% as long as l > 0.4d):
```
L ≈ K * (d²n²) / (18d + 40l)     µH
```
where K = 1.0 for dimensions in inches, K = 0.395 for centimeters.

**Intuition:** Inductance scales with n². More turns → more flux per ampere → much
higher inductance. This is why closely wound toroids achieve high inductance in a
small package.

**Exercise 1.19:** Explain why L ∝ n² for a coil of n turns, maintaining fixed
diameter and length as n is varied.

### Core materials and physical forms

**What it is:** The "core" is a material inside the coil that increases inductance by
multiplying the magnetic flux for a given current. The core's permeability is the
multiplier.

Core shapes seen in practice (Figure 1.51):
- **Toroid** (doughnut) — encapsulated or bare, hermetically sealed variants
- **Pot core** — a doughnut mold split horizontally in half; geometry confines the
  field well
- **Rod / solenoid** — simplest form; field extends outside the core
- **Ferrite bead / ferrite-core choke** — used as RF choke or for noise suppression

Core materials:
- **Iron (and iron alloys, laminations, powder)** — high permeability, used at power
  frequencies
- **Ferrite** — gray, nonconductive, brittle; used at higher frequencies (RF)

All core types are ways to multiply the inductance of a given coil geometry.

**Where you see it in real hardware:** Switching regulators, RF chokes, ferrite beads
on power supply pins. The book notes that practical inductors depart from ideal
behavior — winding resistance, core losses, and self-capacitance are all real issues
(covered in Chapter 1x and Chapter 9). Inductors are indispensable in switching power
converters and in tuned LC circuits for RF.

### Volt-second balance (preview)

**What it is:** V = LdI/dt requires that the *average* voltage across an ideal inductor
be zero in steady-state periodic operation. If it were not, the average current would
rise without bound. This is the "volt-second balance rule."

**Intuition:** In Figure 1.52A (synchronous buck converter), the left side of inductor
L is alternately switched between V_in and ground at a 50% duty cycle. Volt-second
balance then forces the average output voltage to equal half the input voltage:
```
V_out = ½ * V_in      (for 50% duty cycle buck)
```
The output capacitor C₂ smooths the switching into a steady DC. Unlike a resistive
divider, this wastes no energy (the inductor stores and releases, not dissipates) —
it is 100% efficient in the ideal case. This topology is called a synchronous buck
converter.

Figure 1.52B is the boost variant: volt-second balance requires the output to be
*twice* the input voltage (for 50% duty cycle). This configuration is a synchronous
boost converter. Buck and boost converters are covered extensively in Chapter 9.

> **Embedded tie-in:** The 5 V → 3.3 V conversion on virtually every dev board is a
> buck converter. A boost converter can generate a higher rail or a negative rail from
> a single positive supply.

---

## 1.5.2 Transformers

### Fundamentals

**What it is:** A transformer consists of two closely coupled coils (primary and
secondary) on a shared magnetic core (Figure 1.53). An AC voltage on the primary
appears on the secondary, scaled by the turns ratio. Current scales inversely.
Power is conserved.

**The math:**
```
V_sec / V_pri = N_sec / N_pri = n      (voltage scales with turns ratio)
I_sec / I_pri = 1/n                    (current scales inversely)
Z_reflected = n² * Z_load             (impedance seen by primary scales as n²)
```

**Intuition:** A step-up transformer (n > 1) gives higher voltage at lower current.
A step-down transformer does the reverse. Efficiency is very high — output power is
very nearly equal to input power. Jumping ahead: a transformer of turns ratio n
increases the impedance by n². There is very little primary current if the secondary
is unloaded.

**Where you see it in real hardware:**
- **Power transformers** (50/60 Hz) — convert mains voltage (115 V) to a lower, useful
  AC voltage and provide galvanic isolation. Outputs range from 1 V to several
  thousand volts; current from milliamps to hundreds of amps. Typical instrument
  transformers: 10–50 V secondary, 0.1–5 A.
- **Switching power converters** — use transformer-based topologies (e.g., flyback)
  at 50 kHz to 1 MHz for isolation in medical and industrial equipment.
- **Audio and RF transformers** — signal-level; at RF, tuned transformers select a
  narrow frequency band.

### Transformer non-idealities

**What it is:** The simple turns-ratio model ignores several real effects:

- **Magnetizing inductance** — the primary draws current even with no secondary load
  (to maintain the magnetic flux in the core). This is a parallel inductance in the
  model. It means a transformer cannot pass DC — the primary looks like a short to DC
  (just winding resistance), but the secondary sees nothing.
- **Leakage inductance** — not all flux from the primary links to the secondary. The
  uncoupled portion is a series inductance that causes voltage drops under load and
  voltage spikes on switching edges.
- **Winding resistance, core losses, capacitance, magnetic coupling to surroundings**
  — all degrade performance in demanding applications.

Inductors depart significantly from ideal behavior; capacitors are much closer to
ideal in most circuit applications. These non-idealities are dealt with in Chapter 1x
and Chapter 9.

### Core material and frequency

High-frequency transformers (RF, switching supplies) must use special core materials
or construction to minimize core losses. Low-frequency transformers (50/60 Hz mains)
use large, heavy iron cores. The two kinds are generally not interchangeable.
