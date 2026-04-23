# Problems — Ch. 1.2 (Voltage, Current, Resistance)
*Art of Electronics, §1.2 in-chapter exercises*

---

## Exercise 1.7
**Problem:** (VOM circuit — see book for figure.) A voltmeter is built from a 50μA meter movement with 1kΩ internal resistance. Design a multi-range voltmeter for 1V, 10V, 100V full-scale ranges.

**My work:**

**Answer:**

---

## Exercise 1.8
**Problem:** (VOM — continued from 1.7.) Design the current ranges for the same meter movement: 1mA, 10mA, 100mA full-scale.

**My work:**

**Answer:**

---

## Exercise 1.9
**Problem:** (Leakage measurement.) A 50μA meter movement with 2kΩ internal resistance is used to measure the leakage of an electrolytic capacitor. Describe the measurement setup and expected readings.

**My work:**

**Answer:**

---

## Exercise 1.10
**Problem:** A voltage divider is constructed from two 10kΩ resistors driven by a 30V source. Find the Thévenin equivalent (V_Th, R_Th). Then find the power dissipated in each resistor when a 10kΩ load is connected across the output.

**My work:**

**Answer:**
- V_Th = 15V (voltage divider, R2/(R1+R2) = 0.5)
- R_Th = 10k || 10k = 5kΩ
- With 10k load: effective lower resistance = 10k || 10k = 5kΩ
- V_out = 30V × 5k/(10k+5k) = 10V
- P_R1 = (30-10)² / 10k = 40mW
- P_R2 = 10² / 10k = 10mW
- P_load = 10² / 10k = 10mW

---

## Exercise 1.11
**Problem:** Show that R_load = R_source maximizes the power delivered to the load for a given source resistance. (Note: requires calculus.)

**My work:**
Starting from the Thévenin equivalent:

    P_L = V_Th² * R_L / (R_Th + R_L)²

Let u = V_Th² * R_L, v = (R_Th + R_L)²

Quotient rule: dP/dR_L = (u'v - uv') / v²

    u' = V_Th²
    v' = 2(R_Th + R_L)

Numerator = V_Th²(R_Th + R_L)² - V_Th² * R_L * 2(R_Th + R_L)

Factor out (R_Th + R_L):

    = V_Th²(R_Th + R_L) - 2V_Th² * R_L
    = V_Th²(R_Th + R_L - 2R_L)
    = V_Th²(R_Th - R_L)

Set to zero → R_Th = R_L ✓

**Answer:** R_load = R_source (maximum power transfer theorem). At this point half the power is dissipated in R_source — efficiency is 50%. Useful for RF/audio power, not for signal fidelity.
