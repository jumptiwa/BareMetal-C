#include <stdint.h>
#include <stdbool.h>
#include "baremetal_binary.h"
#include "baremetal_delay.h"

#define RELAY ((volatile uint8_t *)0xFFF0U)
#define COPY ((uint8_t *)0x4100U)

void dn(void){
    baremetal_delay(2000);
}

void scroll_up(void){
    uint8_t d = *RELAY;
    *RELAY = (d << 1) | !!( d & B8(10000000) );
}

void scroll_down(void){
    uint8_t d = *RELAY;
    *RELAY = ((d & 1) << 7) | (d >> 1);
}

void main(void) {

    while(true) {
        *RELAY = B8(10101100);
        dn();
        *RELAY = ~(*RELAY);
        dn();
        *RELAY = B8(00000011);
        dn();
        for (uint8_t i = 0; i < 8; i = i+1) {
            scroll_up();
            dn();
        }
        dn();
        for (uint8_t i = 0; i < 8; i = i+1) {
            scroll_down();
            dn();
        }
        dn();
        *RELAY = B8(11111111);
        dn();
        *RELAY = 0;
        dn();
    }

}
