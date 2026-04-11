# Ch. 1 — Problems

---

### Problem 1: Sensor Calibration Table

**Context:** ADC peripherals return raw integer counts. Firmware converts these to engineering units (voltage, temperature, pressure) using a known scale.

**Thought process:**
1. What am I producing? A formatted table: raw ADC count in one column, corresponding voltage in another.
2. What do I know? ADC range is 0–1023 (10-bit). Reference voltage is 3.3V. Voltage = count × 3.3 / 1023.
3. What C mechanism fits? A `for` loop iterating over count values. `printf` with format specifiers for alignment. Float arithmetic for the conversion.
4. Edge cases? Integer division would give 0 for most values — must use float division. Decide on step size (every count? every 100?).

Write a program that prints a table of ADC counts (0 to 1023, stepping by 64) and their corresponding voltages (0.0V to 3.3V). Use `#define` for the max count and reference voltage. Format the output in neat columns with one decimal place for voltage.

---

### Problem 2: UART Echo with Stats

**Context:** A common first test for any serial interface: echo back every byte received, and when the stream ends, report statistics. This is the embedded equivalent of `wc`.

**Thought process:**
1. What am I producing? A program that reads stdin byte-by-byte, echoes it, and at EOF prints counts of bytes, words, and lines.
2. What do I know? `getchar()` returns `int` (for EOF). A word boundary is whitespace → non-whitespace transition. A line ends at `'\n'`.
3. What C mechanism fits? `while` loop with `getchar`. State variable (`in_word` / `out_word`) tracked with `#define` constants. `if-else` for classification.
4. Edge cases? Empty input (zero everything). File that doesn't end with `'\n'`. Multiple spaces between words. `getchar` must go in `int`, not `char`.

Write a program that reads from stdin, echoes each character to stdout with `putchar`, and after EOF prints the total number of characters, words, and lines. Use `#define IN 1` and `#define OUT 0` for word-state tracking. Test with: `echo "hello world" | ./echo_stats` and by redirecting a file.

---

### Problem 3: Command Byte Classifier

**Context:** Protocol parsers often classify incoming bytes — is this a hex digit for an address field? A letter for a command? Whitespace delimiter? This is the first step in any parser.

**Thought process:**
1. What am I producing? A program that reads input and counts how many bytes fall into each category: digit (0–9), letter (a–z, A–Z), whitespace, other.
2. What do I know? Characters have numeric values. `c - '0'` gives digit value. Can test ranges: `c >= 'a' && c <= 'z'`. Need arrays to accumulate counts.
3. What C mechanism fits? `if`/`else if` chain for classification. An `int` array for digit counts (`ndigit[10]`), plus individual counters for letters, whitespace, other.
4. Edge cases? Don't forget both upper and lowercase letters. Tab and space are both whitespace. `'\n'` is whitespace too.

Write a program that reads input until EOF and prints:
- Count of each digit (0–9) separately (use an array of 10 ints)
- Total letter count
- Total whitespace count
- Total "other" count

Use character arithmetic (`c - '0'`) to index into the digit array. Test with varied input.

---

### Problem 4: Integer Power Utility

**Context:** Embedded systems use power-of-2 math constantly — bit shifts, register field widths, buffer sizes. A power function exercises function definition and call-by-value.

**Thought process:**
1. What am I producing? A `power(base, exp)` function and a main that prints a table of values.
2. What do I know? `base^exp` = multiply base by itself exp times. K&R's version uses a `for` loop counting down.
3. What C mechanism fits? Function with prototype. `for` loop in the function body. Call from `main()` in a loop to build a table.
4. Edge cases? `exp == 0` should return 1. Negative exponents not handled (integer only). Call by value means the function can modify its copy of `exp` freely — K&R exploits this.

Write a function `int power(int base, int exp)` that returns `base` raised to `exp` (non-negative only). In `main()`, print a table showing `2^n` and `3^n` for n = 0 to 10 in aligned columns. The function should use K&R's trick: decrement `exp` directly (it's a copy — call by value makes this safe).

---

### Problem 5: Longest Serial Message

**Context:** A serial log contains messages of varying length. Finding the longest message is a common diagnostic — it tells you if something is exceeding buffer limits.

**Thought process:**
1. What am I producing? A program that reads lines from stdin and prints the longest one.
2. What do I know? Need a `getline`-style function to read into a char array. Need a `copy` function to save the longest so far. Track max length seen.
3. What C mechanism fits? Two char arrays: `line` (current) and `longest` (best so far). A `getline` function that reads chars until `'\n'` or EOF, null-terminates, returns length. A `copy` function. External or local variables for tracking.
4. Edge cases? Lines longer than the buffer — `getline` must stop at max and still work. Empty input. Last line may not have `'\n'`.

Write a program with:
- `int getline(char s[], int lim)` — reads one line into `s`, max `lim-1` chars, null-terminates, returns length
- `void copy(char to[], char from[])` — copies string from `from` to `to`
- `main()` that uses these to find and print the longest input line

Use `#define MAXLINE 1000` for buffer size. Test with multi-line input (pipe a file or use heredoc).
