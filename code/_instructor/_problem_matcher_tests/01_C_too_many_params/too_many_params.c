/*
 * Problem Matcher Test Suite for SDCC
 * Memory Map: 0x4000 (Student RAM), 0xC000 (I/O)
 */

// [TEST CASE 4: Linker Error]
// Uncommenting the line below creates an "Undefined Global" error.
// Expected Behavior: Build fails, output shows "?ASlink-Warning-Undefined Global..."
// extern void missing_function(void); 

#define LED_PORT 0xC000

void delay(unsigned int count) {
    while (count--) {
        __asm__("nop");
    }
}

// [TEST CASE 1: Standard Compiler Error]
// Uncommenting the function below triggers "error 101: too many parameters"

void bad_function(void) {
    delay(100, 200); 
}


void main(void) {
    unsigned char *led = (unsigned char *)LED_PORT;
    
    // [TEST CASE 2: Syntax Error with Column]
    // Uncommenting the line below triggers "syntax error: token -> 'return' ; column 5"
    // return 0

    while (1) {
        *led = 0xFF; // Turn ON
        delay(5000);
        
        *led = 0x00; // Turn OFF
        
        // [TEST CASE 4 continued]
        // missing_function();
        
        delay(5000);
    }
}
