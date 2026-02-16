// WRITE to keyboard mapping ROM

#include <stdint.h>

#define KEYBOARD_BASE ((volatile uint8_t *)0xFF00U)

// non-printable ASCII
#define ESCAPE (0x1BU)
#define BACKSPACE (0x08U)
#define TAB (0x09U)
#define CR (0x0DU)
// NON-STANDARD BELOW
// ============
// USE 0x10 1C 1D 1E 1F for UP, DOWN, LEFT, RIGHT arrows respectively
// ============
#define SHIFT (0x10U)
#define UP (0x1CU)
#define DOWN (0x1DU)
#define LEFT (0x1EU)
#define RIGHT (0x1FU)
// ============
// USE 0x14 01 02 03 for CAPSLOCK, CONTROL, OPTION, COMMAND
// ============
#define CAPSLOCK (0x14U)
#define CONTROL (0x01U)
#define OPTION (0x02U)
#define COMMAND (0x03U)

volatile uint8_t *k;

void write_empty(void){
    *k = 0x00;
    k = k + 1;
}

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
    write_byte(ESCAPE);
    write_string("~!@#$%^&*()_+\\");
    write_byte(BACKSPACE);
    
    // second row
    k = KEYBOARD_BASE + 0x10;
    write_string("{`1234567890-=|}");

    // third row
    k = KEYBOARD_BASE + 0x20;
    write_byte(TAB);
    write_string("QWERTYUIOP[]{");

    // fourth row
    k = KEYBOARD_BASE + 0x30;
    write_byte(CAPSLOCK);
    write_string("ASDFGHJKL;:'\"");
    write_byte(CR);

    // fifth row
    k = KEYBOARD_BASE + 0x40;
    write_byte(SHIFT);
    write_string("ZXCVBNM,./?");
    write_byte(SHIFT);
    write_byte(UP);

    // sixth row
    k = KEYBOARD_BASE + 0x50;
    write_byte(CONTROL);
    write_byte(OPTION);
    write_byte(COMMAND);
    write_string("       <>");
    write_byte(LEFT);
    write_byte(DOWN);
    write_byte(RIGHT);
}
