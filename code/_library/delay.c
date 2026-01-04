#include <stdint.h>
#include "instructor_addresses.h"
#include "baremetal_delay.h"

void delay(uint16_t n) {
    volatile uint16_t * const c = DELAY_COUNTER;
    *c = 0;
    while (*c < n) {
        *c = *c + 1;
    }
}
