# Ch. 1.4 — Capacitors and AC Circuits
*Art of Electronics, pp. 18–28 (§1.4.1–1.4.5)*

---

## 1.4.1 Capacitors

### What a Capacitor Is

**What it is:** A device with two wires sticking out of it (the old name was *condenser*). Basic form: a pair of closely-spaced metal plates separated by an insulating material (dielectric), as in the rolled-up "axial-film capacitor." A capacitor of C farads with V volts across its terminals stores Q coulombs of charge on one plate and −Q on the other.

**The math:**
```
Q = CV                              (1.13) — defining relation

I = C * dV/dt                       (1.15) — current is rate of charge change

U_C = (1/2) * C * V^2              (1.16) — stored energy, joules

C = 8.85e-14 * (ε * A / d)  F      (1.14) — parallel-plate formula
                                             ε = dielectric constant
                                             A = plate area (cm²)
                                             d = plate spacing (cm)
```

**Intuition:** A capacitor is more complicated than a resistor: current is not proportional to voltage — it is proportional to the *rate of change* of voltage. If you change the voltage across a farad by 1 V per second, you are supplying 1 amp. Conversely, if you supply 1 amp, its voltage changes by 1 V per second. A farad is enormous; you normally deal in microfarads (μF), nanofarads (nF), or picofarads (pF).

A 10 ms pulse of 1 mA into a 1 μF cap raises the voltage by 10 V — this follows directly from I = C dV/dt.

Energy is stored in internal electric fields, not dissipated as heat. Ideal capacitors cannot dissipate power because voltage and current are 90° out of phase.

**Bypass and coupling — the two dominant uses:** At DC, a capacitor is an open circuit (dV/dt = 0, so I = 0). At high frequency it looks like a short. This makes it ideal for:
- **Coupling (blocking):** Let a varying signal through while blocking its DC average.
- **Bypass (decoupling):** Suppress signals on a DC supply rail — it looks like a short at high frequency, shunting noise to ground.

**Where you see it in real hardware:** Nearly every circuit application. Bypass caps on every IC power pin (100 nF ceramic). Coupling caps between amplifier stages. Filter caps on ADC inputs. The book notes that bypass and coupling capacitors alone account for the vast majority of capacitors wired into the world's circuits.

> **Embedded tie-in:** Every MCU datasheet specifies bypass caps — 100 nF ceramic on each VDD pin, plus bulk electrolytic nearby. A 10 ms pulse of switching current into a 100 nF cap can shift the rail by 100 V unless a low-impedance bypass cap absorbs it locally.

---

### Capacitance: Parallel-Plate Formula

**What it is:** Capacitance is proportional to plate area and inversely proportional to spacing. To get large capacitance, you need a lot of area and close spacing — that is why capacitors are made by rolling up pairs of metal foils.

**The math:**
```
C = 8.85e-14 * (ε * A / d)  F
```
Example: 1 cm² plates, 1 mm separation → slightly less than 1 pF. You would need 100,000 of them to make 0.1 μF. Rolling and stacking is the practical solution.

---

### Capacitors in Parallel and Series

**The math:**
```
Parallel:  C_total = C1 + C2 + C3 + ...           (1.17)

Series:    C_total = 1 / (1/C1 + 1/C2 + 1/C3...)  (1.18)
           Two caps: C_total = C1*C2 / (C1 + C2)
```

**Intuition:** Parallel adds plate area → adds capacitance. Series adds dielectric gap → reduces capacitance. This is opposite to resistors.

**Exercise 1.15:** Derive the series formula. Hint: the two capacitors share a node with no external connection, so they must hold equal stored charges.

---

### Capacitor Types

**What it is:** Capacitors come in a wide variety of constructions. The photo (Figure 1.30) shows the range.

| Type | Key property | Application |
|------|-------------|-------------|
| Ceramic (C0G) | Stable vs. temp and voltage | Precision timing, RF |
| Ceramic (X7R) | ε ≈ 3000, small and cheap | General bypass and filter |
| Polyester/polycarbonate film | Low loss | Demanding analog |
| Polystyrene/polypropylene/Teflon/glass | Very low loss, stable | Precision circuits |
| Tantalum electrolytic | Polarized, compact, large value | Filter, bypass |
| Aluminum electrolytic | Polarized, largest values | Power-supply filtering |
| Mica | Very stable | RF, transmitting |
| Variable (air, ceramic) | Adjustable | Tuning |
| Varactor | Voltage-variable (diode junction) | VCO, PLL |

Ceramic and polyester types are for most noncritical applications. Tantalum and aluminum electrolytics for large capacitance. Aluminum electrolytics are used for power-supply filtering.

---

## 1.4.2 RC Circuits: V and I versus Time

### The Simple RC Discharge

**What it is:** A charged capacitor placed across a resistor discharges exponentially. This is the time-domain approach to RC circuits (the frequency-domain approach comes in §1.7).

**The math:**
```
Circuit equation:  C * dV/dt = -V/R          (1.19)

Solution (discharge):  V(t) = A * e^(-t/RC)  (1.20)

V0 is initial voltage; the cap discharges to 37% of V0 after one time constant.
```

**Intuition:** Current is proportional to remaining voltage (resistor equation). The slope of discharge is proportional to that current (capacitor equation). So the slope is proportional to the value itself — that is the definition of an exponential. Fast at first, slowing as voltage falls.

Figure 1.32 shows the discharge curve on both linear and logarithmic voltage axes. On log scale, exponential decay is a straight line — a useful diagnostic.

---

### The Time Constant

**What it is:** The product RC is the *time constant* of the circuit. For R in ohms and C in farads, RC is in seconds.

**The math:**
```
τ = RC

Example: 1 μF across 1.0 kΩ → τ = 1 ms
         If initially charged to 1.0 V → initial current is 1.0 mA
```

**Key values:**

| Time | Charging (% of Vf) | Discharging (% of V0) |
|------|-------------------|----------------------|
| 1τ   | 63%               | 37%                  |
| 5τ   | >99%              | <1%                  |

**5RC rule of thumb:** A capacitor charges or decays to within 1% of its final value in five time constants.

**Time to reach voltage V on the way to Vf:**
```
t = RC * log_e(Vf / (Vf - V))                (1.22)
```

---

### RC Charging Circuit

**What it is:** Battery (voltage Vf) in series with R, charging C. At t = 0 the battery connects.

**The math:**
```
I = C * dV/dt = (Vf - V_out) / R

Solution:  V_out = Vf * (1 - e^(-t/RC))      (1.21)

A = -Vf  (from initial condition V=0 at t=0)
```

**Intuition:** The slope is proportional to the remaining voltage (distance still to go). An exponential again — but now approaching Vf from below rather than decaying toward zero. Figure 1.34 shows the waveform; at t = RC it has reached 63% of Vf.

**Exercise 1.16:** Show that the rise time (10% to 90% of final value) is 2.2 RC.

---

### Decay to Equilibrium and Arbitrary Inputs

**What it is:** For arbitrary V_in(t), the RC circuit output is a weighted average of past input:

**The math:**
```
V(t) = (1/RC) * ∫[-∞ to t] V_in(τ) * e^(-(t-τ)/RC) dτ
```

**Intuition:** The RC circuit averages past history with an exponential weighting factor e^(−Δt/RC). Recent inputs count more than older ones. In practice you deal with this in the frequency domain (§1.7), not by evaluating the integral.

---

### Simplification by Thévenin Equivalents

**What it is:** More complex-looking RC circuits (e.g., Figure 1.36 with R1, R2, and C) can be reduced by forming the Thévenin equivalent of the voltage divider, then treating the result as a simple RC.

**Exercise 1.17:** In Figure 1.36, R1 = R2 = 10kΩ, C = 0.1 μF. Find V(t) and sketch it.

---

### Circuit Example: Time-Delay Circuit (Figure 1.37)

**What it is:** An RC network (15 kΩ, 1000 pF) between two CMOS buffers (SN74LVC1G17). The first buffer drives the RC with low source resistance. The RC output decays and causes the second buffer to switch 10 μs after the input transitions (an RC reaches 50% output after 0.7 RC).

**Intuition:** Buffer A presents a step to the RC. Buffer C does not switch until the RC output crosses the logic threshold. The result is a delayed version of the input edge. Used to delay a pulse so something else can happen first.

---

### Circuit Example: "One Minute of Power" (Figure 1.38)

**What it is:** RC timing circuit using C1 = 10 μF, R1 = 1 kΩ, R2 = 6.2 MΩ, R3 = 620 kΩ, R4 = 360 kΩ, and a TLC3702 comparator.

**How it works:**
- C1 is initially discharged; comparator output is at ground.
- Press START: C1 charges quickly (τ = R1·C1 ≈ 10 ms) to +5 V.
- Comparator switches output to +5 V.
- Release button: C1 discharges slowly through R2, τ = R2·C1 = 1 minute.
- Reference voltage is set to 1/e of V+ (≈ 1.8 V) by R3/R4 divider — so it takes exactly one time constant τ = R2·C1 for V_C1 to cross the reference.
- Comparator switches back to ground. Output was high for exactly 1 minute.

**Outputs (Figure 1.40):** LED (A), piezo buzzer (B), relay driving small loads (C), solid-state relay driving AC loads like air compressor (D).

**Why R1?** Without it, connecting the discharged cap to +5 V would demand dV/dt near infinite → enormous current spike. R1 limits peak current to ~5 mA.

**Where you see it in real hardware:** One-shot timers, power-off delays, inactivity timeouts in embedded systems. The comparator is the key "black box" here — covered in detail in Chapters 4 and 10.

---

## 1.4.3 Differentiators

### The Circuit

**What it is:** A circuit whose output is proportional to the time derivative of the input — V_out ∝ dV_in/dt.

**Step 1 — ideal but impractical (Figure 1.41A):** C in series with input. The current through C is I = C dV_in/dt. If you could use this current as output directly, you'd have a perfect differentiator. But there is no output terminal.

**Step 2 — practical approximation (Figure 1.41B):** Add a small resistor R from the low side of C to ground as a "current-sensing" resistor. Output is taken across R.

**The math:**
```
I = C * d(V_in - V_out)/dt = V_out / R

If R and C are small enough that dV_out/dt << dV_in/dt:

  C * dV_in/dt ≈ V_out / R

  V_out(t) ≈ RC * dV_in/dt
```

**Condition for good differentiation:** RC must be small — keep the product RC small, but not by making R too large (that would load the input). The frequency-domain criterion comes in §1.7.10.

**Intuition:** The capacitor passes fast changes and blocks slow ones. A step input produces a spike output (derivative of a step = impulse). A square wave in gives spikes at edges (Figure 1.42). Differentiators detect *transitions*, not levels.

**Where you see it in real hardware:** Edge detectors, pulse generators from clock edges, leading-edge detectors in digital systems. The leading-edge detector circuit (Figure 1.43) uses 100 pF, 10 kΩ (τ = 1 μs) between two CMOS buffers.

Figure 1.44 shows measured results at C = 1 pF, R = 50 Ω for input steps of 0.25/0.5/1.0 V/ns. At nanosecond speeds (4 ns/div scale), non-ideal behavior in components and test equipment becomes visible.

---

### Unintentional Capacitive Coupling

**What it is:** Differentiators appear uninvited when there is stray capacitance in the circuit — adjacent PCB traces, or a broken probe connection.

**Two cases (Figure 1.45):**
- Square wave on one trace coupling capacitively to a nearby signal line — looks like a differentiated square wave. Fix: terminate the source line or reduce its source impedance.
- Broken connection at a scope probe tip — the tiny stray capacitance plus 50 Ω scope input resistance forms an RC differentiator.

**Intuition:** Any capacitance in series with a resistance is a differentiator. Knowing this lets you diagnose unexpected spikes on oscilloscope traces.

---

## 1.4.4 Integrators

### The Circuit

**What it is:** A circuit whose output is proportional to the time integral of the input.

**Step 1 — ideal but requires current input (Figure 1.46A):** A capacitor with one side grounded. Input is a current I_in(t) = C dV/dt, so V(t) = ∫I_in dt. Perfect integrator, but only if the input is a current signal.

**Step 2 — practical approximation with voltage input (Figure 1.46B):** R in series with input, C from the junction to ground (output taken across C).

**The math:**
```
I = C * dV/dt = (V_in - V) / R

If V << V_in (keep RC large):

  C * dV/dt ≈ V_in / R

  V(t) = (1/RC) * ∫V_in(t) dt + constant
```

**Condition for good integration:** V_out << V_in. This means RC must be large. The frequency-domain version of this condition is in §1.7.10.

**Intuition:** Feed a square wave in → get a triangle wave out (Figure 1.47). The cap charges at approximately constant current (since V_out << V_in), producing a linear ramp — the integral of a constant. A better approximation as RC increases and V_out stays small relative to V_in.

**Where you see it in real hardware:** Anti-aliasing filters on ADC inputs (lowpass, same circuit), ripple filtering in power supplies, control systems, analog-to-digital conversion, and waveform generation. With op-amps (later chapters) you can build a true integrator without the V_out << V_in restriction.

**Exercise 1.18:** A current of 1 mA charges a 1 μF capacitor. How long does it take the ramp to reach 10 V?

---

### Ramp Generators

**What it is:** A constant current source charging a capacitor produces a perfectly linear voltage ramp — not an approximation.

**The math:**
```
I = C * dV/dt  →  V(t) = (I/C) * t

Example: 1 mA into 1 μF → ramp rises at 1000 V/s = 1 V/ms
```

**Intuition:** Constant current = constant dV/dt = straight line in voltage. The ramp stops when the current source "runs out of voltage" (hits its compliance limit). Compare Figure 1.49: a current source gives a straight ramp; an RC from a fixed voltage gives an exponential that is only approximately straight near the start.

**Where you see it in real hardware:** Analog oscilloscope timebase sweep, function generators, some ADC architectures (ramp ADC, dual-slope ADC), sawtooth oscillators.

---

## 1.4.5 Not Quite Perfect...

### Real Capacitor Non-Idealities

**What it is:** Real capacitors behave as ideal capacitors plus several parasitic elements. For most bypass and coupling applications these are second order — but they matter in demanding designs.

**Parasitic elements:**
```
Real cap = ideal C + series resistance (ESR) + series inductance (ESL)
         + frequency-dependent parallel resistance
```

**Series resistance (ESR):** Limits peak current delivery (important for bypass caps). Causes self-heating under AC current. Aluminum electrolytics have the highest ESR.

**Series inductance (ESL):** At high enough frequency the capacitor looks inductive — impedance increases above the self-resonant frequency (SRF). Above SRF, a bypass cap no longer bypasses. This is why RF circuits use very small ceramic caps.

**Dielectric absorption:** After charging to V0, discharging to 0 V, then removing the short — the voltage drifts back toward V0. The dielectric retains a "memory" of its previous charge state. Problematic in sample-and-hold circuits, precision integrators, and analog timing circuits. Rarely discussed in polite society.

**Intuition:** For 99% of bypass, coupling, and filtering work, treat capacitors as ideal. For precision ADC sample-and-hold, high-frequency bypassing (>10 MHz), or precision timing, the cap type matters — see Chapter 1x for detail.

**Where you see it in real hardware:** ESR of bulk electrolytic caps causes voltage ripple under load in power supplies. SRF determines which cap value to use for a given bypass frequency. Dielectric absorption limits accuracy of switched-capacitor ADCs and DACs.
