#include <stdint.h>
#include <stdbool.h>

// controller
#define KEYBOARD ((volatile const uint8_t * const)0xD020U)

// view
#define HEX_DISP ((volatile uint8_t * const)0xE808U)
// UART
#define UART ((volatile uint8_t * const)0xE040U)
// LED
#define LED ((volatile bool * const)0xE000U)

void main(void){

    uint8_t count = 0;
    uint8_t key;
    while (true) {
        key = *KEYBOARD;
        if (key & 0x80U) {
            *UART = key & 0x7FU;
            *HEX_DISP = key & 0x7FU;
            for (uint8_t i = 0; i < 4; i = i + 1){
                *(LED + i) = (i == count);
            }
            count = (count == 3)? 0 : count + 1;
        }
    }
}
