# Ch. 1.4 — Capacitors and AC Circuits
*Art of Electronics, pp. 18–28 (§1.4.1–1.4.5)*

---

## 1.4.1 Capacitors

### Fundamentals

**What they are:** Two conductors separated by an insulator (dielectric). Store energy in an electric field. The second most common passive component.

**The math:**
```
Q = CV                    (charge stored)
I = C * dV/dt             (current is proportional to rate of voltage change)
U = ½CV²                  (stored energy in joules)
```

**Intuition:** A capacitor resists *changes in voltage*. It takes current to change the voltage — the bigger the cap, or the faster you want to change V, the more current you need. At DC (dV/dt = 0): open circuit (no current flows). At high frequency (fast dV/dt): near short circuit (large current flows for small V changes).

**Combining caps:**
```
Parallel: C_total = C1 + C2 + ...          (opposite of resistors)
Series:   1/C_total = 1/C1 + 1/C2 + ...
```
Parallel plates add area → add capacitance. Series adds gap → reduces capacitance.

### Capacitor Types

| Type | Value range | Key property | Use |
|------|------------|--------------|-----|
| Ceramic (MLCC) | 1pF–100μF | Small, cheap, stable | Bypass, coupling, filter |
| Electrolytic (Al) | 1μF–10,000μF | Large values, polarized | Bulk storage, filter |
| Tantalum | 1μF–1000μF | Polarized, compact | Bypass, filter |
| Film (polyester/polypropylene) | 1nF–100μF | Low loss, accurate | Audio, precision timing |

**Gotchas:**
- Electrolytics are polarized — reverse bias destroys them.
- Ceramic caps lose capacitance under DC bias (X5R/X7R vs C0G: C0G is stable).
- Electrolytics have high ESR (equivalent series resistance) — matters for ripple filtering.

### Bypass and Coupling — The Two Most Common Uses

**Bypass (decoupling):** Cap from power pin to ground. At high frequencies it looks like a short, shunting power supply noise to ground and providing a local charge reservoir for fast current transients.

**Coupling (blocking):** Cap in series with signal path. Blocks DC bias, passes AC. Acts as a highpass filter — must be large enough that its reactance is small at the lowest signal frequency.

> **Embedded tie-in:** Every MCU datasheet specifies bypass caps — typically 100nF ceramic on each VDD pin, plus a bulk 10μF electrolytic nearby. Without them, fast switching currents cause ground bounce and supply droop, corrupting logic. Place them physically close to the IC pin — the inductance of the PCB trace matters.

---

## 1.4.2 RC Circuits: V and I versus Time

### The Time Constant

**The math:**
```
τ = RC                                    (time constant, seconds)

Charging (V0=0, charging to Vf):
  V(t) = Vf * (1 - e^(-t/RC))

Discharging (from V0 to 0):
  V(t) = V0 * e^(-t/RC)
```

**Key values:**

| Time | Charging (% of Vf) | Discharging (% of V0) |
|------|-------------------|----------------------|
| 1τ   | 63%               | 37%                  |
| 2τ   | 86%               | 14%                  |
| 3τ   | 95%               | 5%                   |
| 5τ   | 99.3%             | 0.7%                 |

**5τ rule:** After 5 time constants, the cap is settled to >99%. Use this for "fully charged/discharged."

**Intuition:** The exponential shape comes from the fact that the charging current decreases as the cap approaches its final voltage (less voltage across R = less current). Fast at first, slow near the end — like filling a balloon.

**Where you see it:** Button debouncing (RC ≈ 5–20ms), power-on reset delay, ADC sample-and-hold settling, inrush current limiting.

---

## 1.4.3 Differentiators

### The Circuit

R in series with signal input, C from junction to output (or equivalently: C in series, R to ground — actually this is the highpass). Wait — let me be precise:

**Time-domain differentiator:** C in series, R to ground. For RC << signal period:
```
V_out ≈ RC * dV_in/dt
```

**Intuition:** Feed in a square wave → get spikes at the edges (derivative of a step is an impulse). The cap passes fast changes, blocks slow ones. In the frequency domain, this is a highpass filter — same circuit, two valid perspectives.

**Where you see it:** Edge detection, trigger circuits, detecting transitions in serial data streams. Unintentional differentiation: capacitive coupling between adjacent PCB traces acts as a differentiator, causing crosstalk spikes.

---

## 1.4.4 Integrators

### The Circuit

R in series with signal input, C from junction to ground. For V_out << V_in:
```
V_out ≈ (1/RC) * ∫V_in dt
```

**Intuition:** Feed in a square wave → get a triangle (cap charges and discharges linearly at approximately constant current). The cap averages out rapid changes, keeping only the slow trend. In the frequency domain, this is a lowpass filter.

**Where you see it:** Ripple filtering in power supplies, ADC input anti-aliasing, ramp generators (constant current into cap = linear voltage ramp, used in many ADC architectures), integrating ADCs.

> **Falstad suggestion:** Build an RC lowpass (R in series, C to ground). Drive with a square wave. Vary R and C. Swap positions to make a highpass. Watch the output shape change.

---

## 1.4.5 Not Quite Perfect...

### Real Capacitor Limitations

**ESR (equivalent series resistance):** Every real capacitor has a small series resistance. Limits how fast it can supply current (for bypass caps). Causes self-heating under AC current. Electrolytics: ESR = 0.1–1Ω. Ceramics: ESR < 10mΩ.

**ESL (equivalent series inductance):** The leads and internal structure have inductance. At high enough frequency, the capacitor starts to look inductive — its impedance increases above the self-resonant frequency (SRF). Above SRF, a bypass cap no longer bypasses.

**Dielectric absorption:** After being charged and then discharged, some dielectric materials slowly release a small charge — the cap "remembers" its previous voltage. Relevant for sample-and-hold circuits and precision timing.

**Leakage:** No dielectric is perfect. Electrolytics can have significant leakage current (μA to mA). Ceramics and films are much better.

**Intuition:** For most bypass and filtering applications, these non-idealities are second-order. But for precision ADC inputs, audio sample-and-hold, or high-frequency switching (>10MHz), you must choose cap type carefully.
