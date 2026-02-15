#include <stdint.h>
#include <stdbool.h>

// controller
#define KEYBOARD ((volatile const uint8_t * const)0xD020U)

// view
#define HEX_DISP ((volatile uint8_t * const)0xE808U)

void main(void){

    uint8_t key;
    while (true) {
        key = *KEYBOARD;
        if (key & 0x80U) {
            *HEX_DISP = key & 0x7FU;
        }
    }
}
