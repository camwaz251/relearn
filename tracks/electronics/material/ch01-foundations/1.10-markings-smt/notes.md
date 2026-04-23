# Ch. 1.10 — A Parting Shot: Confusing Markings and Itty-Bitty Components
*Art of Electronics, pp. 64–66 (§1.10–1.10.1)*

---

## 1.10 Confusing Component Markings

**What it is:** A frank warning that component markings are inconsistently applied,
ambiguous, and sometimes absent — especially on capacitors and small SMT parts.

**The problem in detail:**

Capacitors are the worst offenders. Two specific traps from the book:

1. **Integer vs. exponent notation.** The value "470" printed on a ceramic cap can mean
   either 470 pF (integer) or 47 × 10⁰ = 47 pF (exponent). The book's example (Fig.
   1.130): a square cap marked 470K is 470 pF ±10% (K = 10% tolerance); a round cap
   also marked 470K is 47 pF ±10%. Same marking, different value.

2. **SMT ceramics often have no markings at all.** Manufacturers simply dispense with
   them on small package sizes.

3. **Date codes masquerade as part numbers.** ICs carry both a part number (e.g.,
   UA7812) and a 4-digit date code in yyww format (e.g., UC7924 = 24th week of 1979).
   The date code can be mistaken for a separate part number. The book shows three ICs
   each carrying both, and notes this causes real confusion on the bench.

4. **Short alphanumeric codes replace full part numbers** as components shrink. For
   example, National's LMV981 op-amp in SOT23 package is marked "A78A"; the smaller
   SC70 version says "A77"; the microSMD version prints a single letter "A" (or "H"
   if lead-free). That is all you get — you must already know what you're looking for.

**Intuition:** The markings problem compounds as parts shrink. At some package sizes
there is simply not enough surface area for anything meaningful. When debugging an
unknown board, do not trust the marking alone — cross-reference the schematic,
the BOM, or the package context.

**Where you see it in real hardware:** Any rework or reverse-engineering situation.
Also common when hand-populating a PCB from bulk tape: pulled parts look identical
and their markings require a loupe and a datasheet.

---

## 1.10.1 Surface-Mount Technology: The Joy and the Pain

**What it is:** SMT components are soldered directly to pads on the PCB surface — no
holes drilled, no leads passing through. They are electrically superior (low
inductance, compact) but nearly impossible to prototype on breadboard.

**Package size reference (from Fig. 1.132):**

```
Package name    Inch size         Metric name    Dimensions (approx.)
01005           0.016" × 0.008"   0402 metric    0.4 mm × 0.2 mm
0201            0.024" × 0.012"   0603 metric    ~0.6 mm × 0.3 mm
0402            0.040" × 0.020"   1005 metric    1.0 mm × 0.5 mm
```

The 01005 (inch) is the book's "greatest insult to the experimenter": 200 µm ×
400 µm — not much thicker than a human hair, and indistinguishable from dust.

**Contrast with through-hole ("leaded") components:** Resistors and capacitors with
axial leads, or ICs in DIP packages, plug into breadboard and are easy to handle.
SMT requires either reflow soldering or hot-air rework — neither of which works on
a breadboard.

**Workarounds the book mentions:**
- SMT-to-DIP adapter carriers (Bellin Dynamic Systems, Capital Advanced Technologies,
  Aries) let you mount an SMT IC on a fake DIP footprint. Useful for prototyping.
- Dense SMT packages (e.g., BGA — ball-grid array) have no leads at all, only bumps
  on the underside, and require reflow equipment. No practical workaround for
  home/bench use.

**The trend:** The majority of new components are offered only in surface-mount
packages. Through-hole versions are increasingly legacy. This is a problem for
basement experimenters and students.

**Intuition:** SMT exists because PCB area and signal integrity matter more in
production than hand-solderability. Low-inductance pads improve high-frequency
performance. The flip side is that the hobby/prototype workflow gets harder every
year as through-hole options disappear.

**Where you see it in real hardware:** Every modern PCB — phones, microcontroller
dev boards, power supplies. Fig. 1.131 shows a corner of a cellphone PCB: small
ceramic resistors and capacitors, ICs with ball-grid connects on the underside, and
Lilliputian connectors. Fig. 1.133 shows the full variety: connectors, switches,
trimmer pots, inductors, resistors, capacitors, crystals, fuses — all in SMT.

**Embedded/firmware tie-in:** When you spec a microcontroller or peripheral for a
new board design, check package availability early. A part that exists only in a
0.4 mm-pitch BGA is not hand-solderable and requires a stencil + reflow oven. For
prototype-friendly designs, prefer TQFP, SOIC, or QFN packages where possible —
they can be hot-air soldered by hand. Also: SMT bypass capacitors (0402 or 0603)
are the norm on every power rail of every MCU — understanding their package is
relevant to reading any schematic or layout you will work with.
