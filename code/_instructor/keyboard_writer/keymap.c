// WRITE to keyboard mapping ROM

#include <stdint.h>

#define KEYBOARD_BASE ((volatile uint8_t *)0xFF00U)

volatile uint8_t *k;

void write_byte(uint8_t code){
    *k = code | 0x80;
    k = k + 1;
}

void write_string(uint8_t *buffer){
    while (*buffer) {
        *k = *buffer | 0x80;
        k = k + 1;
        buffer = buffer + 1;
    }
}

void main(void){
    
    // first row
    k = KEYBOARD_BASE;
    write_string("`123456789-=");
    write_byte(8);  // backspace
    
    // second row

}
