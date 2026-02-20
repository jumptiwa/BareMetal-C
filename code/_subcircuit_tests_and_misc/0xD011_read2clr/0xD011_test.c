#include <stdint.h>
#include <stdbool.h>

#define KEYPAD ((volatile const uint8_t * const)0xD011U)
#define UART ((volatile uint8_t * const)0xE040U)

void main(void){
    uint8_t k;
    while (true){
        k = *KEYPAD;
        *UART = k;
    }
}
