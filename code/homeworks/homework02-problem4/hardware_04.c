#include <stdbool.h>
#include <stdint.h>

#define LED0 ((volatile bool *)0xE000)
#define LED1 ((volatile bool *)0xE001)
#define LED2 ((volatile bool *)0xE002)
#define LED3 ((volatile bool *)0xE003)

void delay(void) {
    for (volatile int i = 0; i < 100000; i++);
}

int main(void) {

    volatile bool *led_seq[] = {
        LED1,   // E001
        LED2,   // E002
        LED0,   // E000
        LED3,   // E003
        LED2,   // E002
        LED0    // E000
    };

    int i = 0;

    while (true) {
        *led_seq[i] = true;
        delay();
        *led_seq[i] = false;
        delay();

        i = (i + 1) % 6;   // loop forever
    }
}
