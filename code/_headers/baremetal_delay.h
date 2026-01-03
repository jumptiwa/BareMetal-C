#ifndef BAREMETAL_DELAY_H
#define BAREMETAL_DELAY_H

#include <stdint.h>

#define COUNTER ((volatile uint16_t * const)0x41FEU)

void delay(uint16_t n);

#endif // BAREMETAL_DELAY_H
