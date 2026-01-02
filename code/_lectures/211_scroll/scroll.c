// 06-2
#include <stdbool.h>
#include <stdint.h>
#include "baremetal_binary.h"

#define STRIP_WRITE_ONLY ((volatile uint8_t *)0xE010U)
#define SHADOW ((uint8_t *)0x4010U)
#define COUNTER ((volatile uint16_t *)0x4000U)

void delay(uint16_t n) {
    volatile uint16_t *c = COUNTER;
    *c = 0;
    while (*c < n) {
        *c = *c + 1;
    }
}

void main(void){

    bool msb_previous, msb_next;
    uint8_t data;

    *(STRIP_WRITE_ONLY + 0) = *(SHADOW + 0) = B8(01010101);
    *(STRIP_WRITE_ONLY + 1) = *(SHADOW + 1) = B8(00110011);
    *(STRIP_WRITE_ONLY + 2) = *(SHADOW + 2) = B8(00001111);
    *(STRIP_WRITE_ONLY + 3) = *(SHADOW + 3) = B8(00000000);
    *(STRIP_WRITE_ONLY + 4) = *(SHADOW + 4) = B8(10101010);
    *(STRIP_WRITE_ONLY + 5) = *(SHADOW + 5) = B8(11001100);
    *(STRIP_WRITE_ONLY + 6) = *(SHADOW + 6) = B8(11110000);
    *(STRIP_WRITE_ONLY + 7) = *(SHADOW + 7) = B8(11111111);

    msb_next = false; // make compiler happy
    while (true) {

        for (int8_t i = 7; i >= 0; i = i - 1) {

            data = *(SHADOW + i);
            if (i == 7) {
                msb_previous = !!( *(SHADOW) & B8(10000000) );
            } else {
                msb_previous = msb_next;
            }

            msb_next = !!( data & B8(10000000) );
            *(SHADOW + i) = (data << 1) | msb_previous;
            *(STRIP_WRITE_ONLY + i) = *(SHADOW + i); 
        }
        delay(1000);
    }
}
