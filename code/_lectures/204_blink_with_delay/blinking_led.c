#include <stdbool.h>
#include <stdint.h>

#define LED0 ((volatile bool *)0xE000U)
#define COUNTER ((volatile uint16_t *)0x40F0U)

void main(void) {

    volatile uint16_t *c = COUNTER;
    volatile bool *led = LED0;

    while (true) {
        *led = true;
        *c = 0;
        while (*c < 4000) {
            *c = *c + 1;
        }
        *led = false;
        *c = 0;
        while (*c < 4000) {
            *c = *c + 1;
        }
    }
}
