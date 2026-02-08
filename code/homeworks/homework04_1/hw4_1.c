#include <stdint.h>
#include <stdbool.h>
#include "baremetal_delay.h"

// DELAY TIME
#define DELAY (3000)

// VIEW
#define VIEW_DECIMAL ((volatile uint8_t * const)0xE800U)

void view_update(uint8_t value){
    // WRONG
    *VIEW_DECIMAL = value;
}

void main(void){
    while (true) {
        *VIEW_DECIMAL = 0x93U;
        baremetal_delay(DELAY);
        *VIEW_DECIMAL = 0x45U;
        baremetal_delay(DELAY);
        *VIEW_DECIMAL = 0x26U;
        baremetal_delay(DELAY);
        view_update(93);
        baremetal_delay(DELAY);
        view_update(45);
        baremetal_delay(DELAY);
        view_update(26);
        baremetal_delay(DELAY);
    }
}
