# Electronics — Concept Progressions

## Ch. 1 — Foundations (Problems 1.7–1.9)
*New this session:*
- VOM meter movement — coil + magnet mechanism, 50μA full-scale deflection
- Shunt resistor — parallel bypass for current measurement, R_shunt = V_movement / I_shunt
- Series resistor — in-line drop for voltage measurement, R_series = (V_range - V_movement) / I_fullscale
- Voltmeter loading — DMM/VOM input resistance forms divider with circuit R_Th, pulls reading down
- 20,000 Ω/V spec — VOM input resistance = spec × range selected
- Leakage resistance — insulation modeled as large resistor; measured by series DMM + known source
- DMM as current sensor — high input resistance used as known series R to measure nA-range currents indirectly

*Previously covered:*
- Ohm's law (V=IR) — relates voltage, current, resistance
- KCL / KVL — conservation of charge and energy in circuits
- Resistors in series and parallel — combining resistances, shortcuts for mental math
- Power dissipation (P=IV, P=I²R, P=V²/R) — electrical energy to heat
- Voltage divider — most important circuit fragment, V_out = V_in * R2/(R1+R2)
- Voltage and current sources — ideal vs. real, internal resistance
- Thevenin equivalent — any two-terminal network = V_Th + R_Th in series
- Small-signal (dynamic) resistance — dV/dI, slope of V-I curve for nonlinear devices
- Circuit loading — R_load >> R_source to avoid voltage sag
- Sinusoidal signals — amplitude, frequency, phase, rms vs. peak
- Decibels — 20*log10(A2/A1), landmarks: 3/6/10/20 dB
- Logic levels — HIGH/LOW thresholds, 3.3V vs 5V families
- Capacitor fundamentals — Q=CV, I=C*dV/dt, U=½CV²
- Bypass (decoupling) capacitor — shorts high-freq noise to ground on power pins
- Coupling (blocking) capacitor — passes AC, blocks DC
- RC time constant — tau=RC, exponential charge/discharge, 5*tau rule
- RC differentiator — edge detector, V_out ~ RC * dV_in/dt
- RC integrator — averager, V_out ~ (1/RC) * integral(V_in)
- Inductor fundamentals — V=L*dI/dt, U=½LI², resists current changes
- Volt-second balance — average inductor voltage = 0 in steady state
- Transformer — turns ratio, voltage/current scaling, isolation
- Buck/boost converter preview — switching power conversion with inductors
- Diode V-I curve — forward drop ~0.6V (Si), ~0.3V (Schottky), nonlinear
- Rectification — half-wave, full-wave bridge, capacitor filtering
- Ripple voltage — delta_V = I_load / (f*C)
- Zener diode — voltage regulation via reverse breakdown, dynamic resistance
- Diode applications — clamps, limiters, OR gates, flyback protection
- Reactance — X_C = 1/(wC), X_L = wL, frequency-dependent opposition
- Complex impedance — Z = R + jX, generalized Ohm's law V=IZ
- RC lowpass filter — f_3dB = 1/(2*pi*RC), -20dB/decade rolloff
- RC highpass filter — same breakpoint, passes high blocks low
- LC resonance — f_0 = 1/(2*pi*sqrt(LC)), quality factor Q
- Power factor — cos(phi), reactive vs. real power
- AM radio — LC tuning + diode detector + RC smoothing (capstone circuit)
- Switches — SPST/SPDT/DPDT, momentary, rotary
- Relays — electromechanical and solid-state (SSR)
- Connectors — BNC, D-sub, headers, USB, edge connectors
- LEDs — forward drop 1.5-3.6V, series resistor sizing
- Variable components — potentiometers, varactors, trimmers
- SMT packages — 0402, 0603, 0805, 1206 sizing
