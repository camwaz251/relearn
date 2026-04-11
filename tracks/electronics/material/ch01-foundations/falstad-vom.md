# Falstad Lab — VOM Loading (Problem 1.7)

**Goal:** See voltmeter loading in action by building the two circuits from 1.7.

---

## Circuit 1 — Real Source with Internal Resistance

**Build:**
- 1V DC source in series with 10k resistor (this models a "real" source with internal R)
- 20k resistor from the output node to ground (this is your voltmeter)

**Measure:** voltage across the 20k.

**Expected:** 0.667V (not 1V — the meter is loading the source)

---

## Circuit 2 — Voltage Divider with Meter Load

**Build:**
- 1V stiff source into a 10k–10k voltage divider
- 20k resistor from the middle node to ground (voltmeter)

**Measure:** voltage across the 20k.

**Expected:** 0.4V

**Then:** remove the 20k and measure the unloaded middle node.

**Expected:** 0.5V

**Observe:** the voltage jumps when the meter is disconnected — that's loading disappearing.

---

## Key Takeaway

The 20k "voltmeter" forms a voltage divider with the circuit's Thevenin resistance every time you probe a node. Lower R_Th relative to the meter = more accurate reading. This is why DMMs use 10MΩ input resistance — it dwarfs almost any R_Th you'll encounter.
