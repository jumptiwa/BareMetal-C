#include <stdbool.h>
#include <stdint.h>

#define LED0 ((volatile bool *)0xE000U)


void main(void) {

    volatile bool *led; 
    led = LED0;

    while (true) {
        *led = true;
        *led = false;
    }

}
