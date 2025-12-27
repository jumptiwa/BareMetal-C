#include <stdbool.h>
#include <stdint.h>

#define M_ADDR ((int16_t *)0x4000U)

void main (void) {
    int16_t a;
    a = -27;
    int16_t b = 54;
    int16_t *p = M_ADDR;

    *p = a * b;
}
