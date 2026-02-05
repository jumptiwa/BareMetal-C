# C99 Coding Guidelines for `Bare-Metal C` Course using `SDCC`

### **1. Macros & Preprocessor**
*Rationale: The preprocessor is a text substitution tool. Strict syntax prevents precedence errors and side effects.*

* **Rule 1.1: Parenthesize Macro Replacements.**
  * All macro values must be enclosed in `( )`.
  * **Bad:** `#define OFFSET 0x10U + 0x02U`
  * **Good:** `#define OFFSET (0x10U + 0x02U)`
  * **Good:** `#define BASE_ADDR ((volatile uint8_t *) 0x8000U)`

* **Rule 1.2: "`U`" Suffix Usage.**
  * **Use `U` for Bit-level Data:** Hardware addresses, bit masks, and patterns must use the `U` suffix (Unsigned 16-bit) to prevent sign-extension bugs.
    * *Example:* `0x8000U`, `0xFFU`, `(1U << 15)`
  * **No Suffix for Counts:** Simple loop counters and scalar amounts do not need a suffix.
    * *Example:* `i < 10`, `delay(5000)`

* **Rule 1.3: No Parameterized Macros.**
  * Use `static inline` functions instead to avoid side-effect bugs.
  * **Bad:** `#define ADDR_OFFSET(x) (BASE + x)`
  * **Good:** `static inline uint8_t* get_addr(uint8_t x) { return BASE + x; }`

---

### **2. Data Types & Precision**
*Rationale: Z80 `int` size varies by compiler. Explicit types prevent ambiguity. The C99 standard does not specify whether `char` by itself should be `signed` or `unsigned`; avoid using `char` as well.*

* **Rule 2.1: Use `<stdint.h>` types.**
  * **Forbidden:** Never use standard `int`, `short`, or `long`, and `char`.
  * **For `char`:** Use `uint8_t` instead of `char`. It is guaranteed to be 8-bit unsigned.
  * **Addresses:** Always use `uint16_t` (Z80 address bus is 16-bit).
  * **Unsigned Data:** Use `uint8_t` for 8-bit values and `uint16_t` for 16-bit values.
  * **Signed Data:** Use `int8_t` or `int16_t` **only** when dealing with signed data (2's complement  number), whether for calculation or reading from IO address.

* **Rule 2.2: Use `bool` from `<stdbool.h>`.**
  * Use `true` / `false` for logic flags.
* **Rule 2.3: Avoid Floating Point.**
  * The Z80 has no FPU. Floats are emulated and prohibitively slow.

---

### **3. Memory Mapped I/O (MMIO)**
*Rationale: "Writing to IO" is simply writing to a specific memory address.*

* **Rule 3.1: The `volatile` keyword is mandatory.**
  * Any pointer interacting with hardware *must* be `volatile` so the compiler does not optimize away the access.

* **Rule 3.2: Define Hardware Addresses via Macros.**
  * Never use magic numbers. Define addresses as fully cast pointers in a single macro.
  * **Format:** `#define NAME ((volatile type *) addressU)`
  * **Good:**
    ```C
    #define LED_PORT  ((volatile uint8_t *) 0x4000U)
    *LED_PORT = 0xFFU; 
    ```

---

### **4. Memory Management**
*Rationale: Memory is finite (SRAM) and there is no OS.*

* **Rule 4.1: No Dynamic Memory.**
  * **Forbidden:** `malloc()`, `calloc()`, `free()`.

* **Rule 4.2: Use `const` for Read-Only Data.**
  * Lookup tables (e.g., fonts) should be `const` to save RAM.

---

### **5. Functions & Control Flow**
*Rationale: The Z80 stack is small and easy to overflow.*

* **Rule 5.1: No Recursion.**
  * Functions must not call themselves.

* **Rule 5.2: Infinite Main Loop.**
  * Embedded programs never exit. `main()` must end with `while(true)`.

* **Rule 5.3: Keep Functions Short.**
  * Aim for < 30 lines per function.

* **Rule 5.4: Named Parameter Prototypes.**
  * Function prototypes must include **argument names** alongside data types. This clarifies the purpose of each argument (Self-Documentation) and enables better IDE support.
  
  * **Bad:** `void lcd_set_cursor(uint8_t, uint8_t);`
  * **Good:** `void lcd_set_cursor(uint8_t row, uint8_t col);`

* **Rule 5.5: Switch Default Break.**
  * The `default` clause in a `switch` statement must always end with a `break;`. This prevents accidental fall-through if new cases are added later (Defensive Coding).
  * **Bad:** `default: err = 1; }`
  * **Good:** `default: err = 1; break; }`
  
---

### **6. Bit Manipulation**
*Rationale: Hardware control requires changing specific bits without affecting others.*

* **Rule 6.1: Use Explicit Shifts.**
  * Use standard shifts with unsigned constants: `(1U << 3)`. Avoid bit-fields.

* **Rule 6.2: Read-Modify-Write.**
  * **Set Bit 3:** `*PORT = *PORT | (1U << 3);`
  * **Clear Bit 3:** `*PORT = *PORT & (~(1U << 3));`

---

### **7. SDCC Specific Constraints**
*Rationale: SDCC optimizations are tailored for 8-bit systems.*

* **Rule 7.1: Variable Declaration.**
  * Declare variables at the top of the function block.
  * *Exception:* Loop iterators may be declared in `for` loops: `for (uint8_t i = 0; ...)`

* **Rule 7.2: Large Arrays.**
  * Large arrays must be `static` or global to avoid stack overflow.

* **Rule 7.3: Assembly.**
  * Do not use in-line assembly `__asm__`, except for `__asm__("nop");`.

---

### **8. Operator Use & Clarity**
*Rationale: Explicit operations prevent ambiguity and ensure the read-modify-write cycle is visible.*

* **Rule 8.1: Prohibit Composite Assignments.**
  * Do not use `+=`, `-=`, `&=`, `<<=`, `++`, or `--`. The long form is clearer.
  * **Bad Examples:** 1. `d++;` 2. `m <<= 2;` 3. `k ^= 0x70U;`
  * **Good Examples:** 1. `d = d + 1;` 2. `m = m << 2;` 3. `k = k ^ 0x70U;`

---

### **Sample "Perfect" Student Code**

```C
/*
 * Hardware: Z80 simulated with memory mapped LED at 0x8000
 * Goal: Blink LED
 */

#include <stdint.h>
#include <stdbool.h>

// Rule 3.2: Defined as macro with cast. 
// Rule 1.2: Address is a bit-pattern, so use U suffix.
#define IO_LED       ((volatile uint8_t *) 0x8000U)

void delay_loops(uint16_t count) {
    while (count > 0) {
        // Rule 8.1: Explicit subtraction (no count--)
        count = count - 1;

        // Rule 7.3: NOP for delay
        __asm__("nop");
    }
}

void main(void) {
    uint8_t pattern = 0x01U;

    // Rule 5.2: Infinite Super Loop
    while (true) {
        // 1. Write to Data Bus
        *IO_LED = pattern;

        // 2. Wait
        // Rule 1.2: '5000' is a count/scalar, so NO U suffix.
        delay_loops(5000);

        // 3. Logic: Shift pattern left
        if (pattern == 0x80U) {
            pattern = 0x01U;
        } else {
            // Rule 8.1: Explicit shift
            pattern = pattern << 1;
        }
    }
}
```

---

### **9. Read the `C99 Style Guide`**

**Read** the [**C99 Style Guide**](./C99-style-guide.md) next.
