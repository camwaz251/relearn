# Ch. 1.8 — Putting It All Together: An AM Radio
*Art of Electronics, pp. 55–56 (§1.8)*

---

### The AM Signal

**What it is:** AM transmission takes an audio waveform f(t) and uses it to vary the amplitude of a high-frequency RF carrier. The transmitted signal is:

```
V(t) = [A + f(t)] * sin(2π f_c t)
```

f_c is the station's carrier frequency (AM band: 520–1720 kHz). The constant A is added to f(t) so that the coefficient [A + f(t)] is never negative — no phase reversal of the carrier. The audio frequencies run roughly 20 Hz–5 kHz; the carrier is ~1 MHz. You are literally seeing a 1 MHz waveform whose amplitude wiggles at audio rates.

**The math:** The envelope of V(t) is [A + f(t)]. The receiver's job is to extract that envelope and throw away the carrier.

**Intuition:** The carrier is the vehicle; the audio is the passenger. Detection means reading the passenger out without caring about the vehicle's oscillation.

**Where you see it in real hardware:** AM broadcast radio, AM aviation comms (still widely used), ASK (amplitude-shift keying) in RFID and infrared remotes — same envelope-detection principle.

---

### The Crystal Set — Simplest AM Receiver (Figure 1.114)

**What it is:** The "crystal set" of yesteryear. A passive circuit that can receive AM with no power supply — just an antenna, an LC tank, a diode, and a couple of passives. The book calls it the simplest AM radio.

**The circuit, block by block:**

```
Antenna → [parallel LC tank: variable C1 + L] → point X
                                                      |
                                                   Diode D (point X to point Y)
                                                      |
                                              R1 (Y to ground) || C2 (Y to ground)
                                                      |
                                             Audio amplifier → Speaker
```

1. **Antenna** — picks up every AM station simultaneously plus 60 Hz powerline noise and any other RF. The bare antenna is a superposition of everything in the air.

2. **Parallel LC tank (variable C1 + L)** — tuned to the desired station's carrier frequency by adjusting C1. At resonance, the tank presents maximum impedance, so the selected frequency dominates the voltage across it. All other frequencies see a low impedance and are suppressed. The amplitude of the selected station at the tank output is Q times larger than what the bare antenna sees.

3. **Diode D** — half-wave rectifier. Passes only the positive half-cycles of the modulated carrier (§1.6.2). The output is a series of positive humps whose peaks trace the envelope of the AM signal — the audio waveform.

4. **R1** — provides a DC return path so the diode has a load to drive. It must be light (high resistance) to avoid loading down the LC tank and degrading Q.

5. **C2** — storage capacitor (§1.7.16B). Smooths the rectified carrier so the output follows the slow audio envelope instead of bouncing at 1 MHz.

**The math:** Time constant R1·C2 must satisfy two constraints simultaneously:

```
1/f_carrier  <<  R1*C2  <<  1/f_audio_max

~1 μs        <<  R1*C2  <<  ~200 μs
```

Long compared to the carrier period (~1 μs at 1 MHz) → the capacitor doesn't discharge between carrier cycles, so the RF is smoothed out.

Short compared to the audio period (~200 μs at 5 kHz) → the capacitor can follow the slowly-varying envelope.

**Intuition:** C2 is a low-pass filter on top of the half-wave rectifier. It holds the peak of each carrier cycle and sags just enough between cycles to track the audio. Too large: C2 can't follow the audio (the output is a flat DC). Too small: C2 discharges between carrier cycles and the RF ripple rides through.

**Where you see it in real hardware:** Envelope detectors in AM receivers, AM demodulators in ICs (e.g., SA602), peak detectors in audio level meters, back-EMF detection in motor controllers, signal envelope tracking in AGC (automatic gain control) circuits.

---

### Why the LC Tank Amplifies — the Q Factor

**What it is:** When the LC tank is connected to the antenna, the amplitude of the selected station becomes *larger* than what the bare antenna delivers. The book explicitly notes this and attributes it to the resonant circuit's high Q storing energy from multiple cycles of the signal.

**The math:** Voltage at the tank at resonance:

```
V_tank = Q * V_antenna
```

Q is the quality factor of the LC tank (ratio of energy stored to energy dissipated per cycle).

**Intuition:** The tank is a flywheel for charge. Each incoming carrier cycle adds a little energy; because losses are low (high Q), the stored energy builds up over many cycles until the steady-state amplitude is Q times the driving amplitude. This is exactly why connecting the LC to the antenna makes the signal larger, not smaller.

**Where you see it in real hardware:** Crystal oscillators exploit Q > 10,000 for frequency stability. RF front-end matching networks use resonant tanks for impedance transformation. Bandpass filters in radio IFs (intermediate frequency stages) use Q to set selectivity.

---

### Oscilloscope Observations (Figures 1.115 and 1.116)

**What it is:** The book describes probing two points in the circuit and shows actual oscilloscope captures.

**Point "X" — antenna terminal (Figure 1.115, vertical: 1 V/div, horizontal: 4 ms/div):**

- Bare antenna (open circuit, top trace): large, messy signal dominated by 60 Hz powerline pickup. All AM stations appear simultaneously as a dense blob of RF noise.
- With LC tank connected to ground (bottom trace): the 60 Hz low-frequency junk disappears — the LC looks like very low impedance at 60 Hz (§1.7, Figure 1.107), so it shorts it out. The ~1 MHz radiofrequency carrier now appears as a solid filled area (the carrier oscillates too fast to see individual cycles at 4 ms/div). The amplitude is *larger* than the bare antenna because the high-Q tank is storing energy.

**Point "Y" — after the diode and R1·C2 filter (Figure 1.116, vertical: 1 V/div, horizontal: 1 ms/div):**

- With R1 only (top trace, no C2): the rectified waveform. The ~1 MHz carrier appears as solid black (too fast to resolve). The envelope — the audio signal — is visible as the amplitude modulation on the carrier.
- With R1 + C2 (bottom trace): the carrier is smoothed away. The output is the audio envelope directly — a clean, slowly-varying waveform ready for the audio amplifier.

**Intuition:** The scope pictures are the clearest demonstration of what each block does. The LC kills the noise and selects the station. The diode creates the one-sided waveform. C2 strips off the carrier and leaves the audio.

---

### The BNC Cable Anecdote

The book describes a classroom demonstration: probe point "X" with a BNC cable (~30 pF/ft) going to a 'scope input. The BNC cable's capacitance adds to C1, lowering the resonant frequency — the radio tunes to a different station. Do it right and it changes languages (from English to Spanish). Use a standard 'scope probe (~10 pF) instead and there's no change: the capacitance is small enough to not shift the resonant frequency meaningfully.

**Intuition:** This is a direct demonstration that stray capacitance matters at RF. Any conductor near a high-Q resonant circuit can detune it. In embedded design: be careful routing traces near LC oscillators, clock circuits, or RF front ends.

---

### The Audio Amplifier

The book notes the audio amplifier block is needed but not covered until Chapter 2 (discrete transistors) and Chapter 4 (op-amps). It is shown in the schematic as a triangle driving a speaker.

**Embedded tie-in:** In a microcontroller-based AM receiver (e.g., software-defined radio periphery), the envelope detector output feeds an ADC. The firmware then does digital audio processing — filtering, volume control, decompression — in software. The analog front end (LC tank + diode + RC) is identical; only the back end changes.

---

### Every Ch. 1 Concept in One Circuit

| Ch. 1 Topic | Where It Appears |
|---|---|
| Voltage divider / Thévenin | Antenna source impedance loads the LC tank; affects Q |
| RC time constant | R1·C2 envelope filter |
| Capacitors / inductors | LC tank for station selection |
| Resonance | LC at f_c picks the station; Q sets gain and selectivity |
| Diode rectification (§1.6.2) | Half-wave detection of the carrier |
| Storage capacitor (§1.7.16B) | C2 smoothing |
| Q factor | Voltage gain at the tank; selectivity |
| Thévenin generalized (§1.7.17) | Complex impedance of the LC as seen by the antenna |
