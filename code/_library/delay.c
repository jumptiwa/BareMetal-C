#include <stdint.h>
#include "baremetal_delay.h"

void delay(uint16_t n) {
    volatile uint16_t * const c = COUNTER;
    *c = 0;
    while (*c < n) {
        *c = *c + 1;
    }
}
