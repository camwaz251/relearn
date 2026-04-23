# Review of Chapter 1 — Foundations
*Art of Electronics, pp. 68–70*

This is a quick-reference summary. Use the per-section notes for detail.

---

## A. Voltage and Current
- Current (I): rate of charge flow; measured in amperes.
- Voltage (V): potential difference between two points; the driving force for current.
- KCL: sum of currents into any node = sum out. (Conservation of charge.)
- KVL: sum of voltages around any closed loop = 0. (Conservation of energy.)

## B. Signal Types and Amplitude
- Sinewaves: V_rms = V_peak/√2. Only for sinewaves.
- Decibels: +3dB = ×2 power. +6dB = ×2 voltage. +20dB = ×10 voltage.
- Square waves: V_rms = V_peak (no √2 factor).

## C. Resistors
- V = IR (Ohm's law). P = IV = I²R = V²/R.
- Series: R_total = R1 + R2. Parallel: R_total = R1||R2 = (R1R2)/(R1+R2).
- Voltage divider: V_out = V_in × R2/(R1+R2).
- Thévenin: any two-terminal resistive network = V_Th + R_Th in series.

## D. Capacitors
- I = C·dV/dt. Open at DC, short at high frequency.
- τ = RC. 5τ to settle. Charge to 63% in 1τ.
- Lowpass: R series + C to ground. f_3dB = 1/(2πRC).
- Highpass: C series + R to ground. Same f_3dB.

## E. Inductors
- V = L·dI/dt. Short at DC, open at high frequency.
- Dual of capacitor. Stores energy in magnetic field.
- Volt-second balance governs switching converter operation.

## F. Diodes
- Forward biased: V_f ≈ 0.6V (silicon). Conducts.
- Reverse biased: blocks until breakdown.
- Zener: operates in controlled reverse breakdown at V_Z.
- Flyback diode: across every inductive load, always.

## G. Impedance
- Z_C = 1/(jωC). Z_L = jωL. Z_R = R.
- Generalized Ohm's law: V = IZ.
- Generalized voltage divider: V_out = V_in × Z2/(Z1+Z2).
- |Z_C| = X_C = 1/(2πfC). |Z_L| = X_L = 2πfL.

## H. Resonance
- f_0 = 1/(2π√LC). Inductive and capacitive reactances cancel.
- Series LC: minimum impedance at f_0 (trap).
- Parallel LC: maximum impedance at f_0 (tank).
- Q = f_0/Δf_3dB. Higher Q = sharper resonance.

## I. Key Rules of Thumb
- Keep R_load ≥ 10× R_source to minimize loading.
- Bypass cap on every VDD pin (100nF ceramic).
- Flyback diode on every inductive load.
- Debounce every mechanical switch (5–20ms RC or software).
- Anti-aliasing filter cutoff ≤ half the ADC sample rate.
- LED always needs a series current-limiting resistor.
