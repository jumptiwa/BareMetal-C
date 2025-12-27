#include <stdbool.h>
#include <stdint.h>

#define ADDR_START 0x4010U
#define ADDR_END   0xBFF0U

void main(void) {
  volatile uint16_t *p = (volatile uint8_t *) ADDR_START;

  for (p = ((volatile uint16_t *) ADDR_START); p < ((volatile uint16_t *) ADDR_END); p = p+8) {
    *p = p;
  }    

  while (true) {
  }
}
