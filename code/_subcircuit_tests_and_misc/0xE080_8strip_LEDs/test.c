#include <stdint.h>
#include <stdbool.h>

#define STRIP ((volatile uint8_t * const)0xE080U)

void main(void){
    for (uint8_t i = 0; i < 8; i = i+1) {
        *(STRIP + i) = 0x80 | i;
    }
    while(true){
    }
}
