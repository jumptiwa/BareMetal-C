#include <stdint.h>
#include <stdbool.h>

#define BYTE_HEX ((volatile uint8_t * const)0xE808U)
#define PLUS_KEY ((volatile const bool * const)0xD007U)
#define MINUS_KEY ((volatile const bool * const)0xD006U)

void main(void){
    uint8_t d = 0x10U;
    while (true) {
        *BYTE_HEX = d;
        if (*PLUS_KEY) {
            d = (d == 0xFFU)? d : d + 1;
        } else if (*MINUS_KEY) {
            d = (d == 0)? d : d - 1;
        }
    }
}
