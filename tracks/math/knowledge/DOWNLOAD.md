# Paul's Online Math Notes — PDF Downloads

All files go in `tracks/math/knowledge/` relative to the repo root.
PDFs are excluded from git (see `.gitignore`).

Download each file with curl. The `Referer` header is required — the site blocks direct downloads without it.

---

## One-liner setup (run from repo root)

```bash
mkdir -p tracks/math/knowledge/{cheat-sheets,algebra-trig-review,algebra,calculus,differential-equations}
```

---

## Algebra/Trig Review

Referer: `https://tutorial.math.lamar.edu/Classes/CalcI/CalcI.aspx`

```bash
UA="Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36"
REF="https://tutorial.math.lamar.edu/Classes/CalcI/CalcI.aspx"
BASE="https://tutorial.math.lamar.edu"
DEST="tracks/math/knowledge/algebra-trig-review"

curl -A "$UA" -H "Referer: $REF" "$BASE/GetFile.aspx?file=B,12,N" -o "$DEST/notes.pdf"
curl -A "$UA" -H "Referer: $REF" "$BASE/GetFile.aspx?file=B,12,P" -o "$DEST/practice-problems.pdf"
```

---

## Algebra

Referer: `https://tutorial.math.lamar.edu/Classes/Alg/Alg.aspx`

```bash
UA="Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36"
REF="https://tutorial.math.lamar.edu/Classes/Alg/Alg.aspx"
BASE="https://tutorial.math.lamar.edu"
DEST="tracks/math/knowledge/algebra"

curl -A "$UA" -H "Referer: $REF" "$BASE/GetFile.aspx?file=B,9,N" -o "$DEST/notes.pdf"
curl -A "$UA" -H "Referer: $REF" "$BASE/GetFile.aspx?file=B,9,P" -o "$DEST/practice-problems.pdf"
curl -A "$UA" -H "Referer: $REF" "$BASE/GetFile.aspx?file=B,9,S" -o "$DEST/practice-solutions.pdf"
curl -A "$UA" -H "Referer: $REF" "$BASE/GetFile.aspx?file=B,9,A" -o "$DEST/assignment-problems.pdf"
```

---

## Calculus (I + II + III combined)

Referer: `https://tutorial.math.lamar.edu/Classes/CalcI/CalcI.aspx`

```bash
UA="Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36"
REF="https://tutorial.math.lamar.edu/Classes/CalcI/CalcI.aspx"
BASE="https://tutorial.math.lamar.edu"
DEST="tracks/math/knowledge/calculus"

curl -A "$UA" -H "Referer: $REF" "$BASE/GetFile.aspx?file=B,20,N" -o "$DEST/notes.pdf"
curl -A "$UA" -H "Referer: $REF" "$BASE/GetFile.aspx?file=B,20,P" -o "$DEST/practice-problems.pdf"
curl -A "$UA" -H "Referer: $REF" "$BASE/GetFile.aspx?file=B,20,S" -o "$DEST/practice-solutions.pdf"
curl -A "$UA" -H "Referer: $REF" "$BASE/GetFile.aspx?file=B,20,A" -o "$DEST/assignment-problems.pdf"
```

---

## Differential Equations

Referer: `https://tutorial.math.lamar.edu/Classes/DE/DE.aspx`

```bash
UA="Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36"
REF="https://tutorial.math.lamar.edu/Classes/DE/DE.aspx"
BASE="https://tutorial.math.lamar.edu"
DEST="tracks/math/knowledge/differential-equations"

curl -A "$UA" -H "Referer: $REF" "$BASE/GetFile.aspx?file=B,1,N" -o "$DEST/notes.pdf"
```

---

## Cheat Sheets

Referer: `https://tutorial.math.lamar.edu/Extras/CheatSheets_Tables.aspx`

```bash
UA="Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36"
REF="https://tutorial.math.lamar.edu/Extras/CheatSheets_Tables.aspx"
BASE="https://tutorial.math.lamar.edu"
DEST="tracks/math/knowledge/cheat-sheets"

curl -A "$UA" -H "Referer: $REF" "$BASE/getfile.aspx?file=B,30,N" -o "$DEST/algebra-cheat-sheet.pdf"
curl -A "$UA" -H "Referer: $REF" "$BASE/getfile.aspx?file=B,32,N" -o "$DEST/trig-cheat-sheet.pdf"
curl -A "$UA" -H "Referer: $REF" "$BASE/getfile.aspx?file=B,40,N" -o "$DEST/calculus-complete-cheat-sheet.pdf"
curl -A "$UA" -H "Referer: $REF" "$BASE/getfile.aspx?file=B,34,N" -o "$DEST/common-derivatives-integrals.pdf"
curl -A "$UA" -H "Referer: $REF" "$BASE/getfile.aspx?file=B,36,N" -o "$DEST/laplace-transforms-table.pdf"
```
