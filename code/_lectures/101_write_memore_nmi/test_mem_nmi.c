#include <stdint.h>

#define ADDR0 0x0060U
#define ADDR1 0x0062U

#define NMI_COUNT 0x0064U

void nmi_handler(void) __critical __interrupt {
  volatile uint8_t *count = (volatile uint8_t *) NMI_COUNT;

  *count = *count + 1;
}

void main(void) {
  volatile uint8_t *count0 = (volatile uint8_t *) ADDR0;
  volatile uint8_t *count1 = (volatile uint8_t *) ADDR1;
  
  *count0 = 0;
  *count1 = 0;

  while (1) {
    for (uint8_t i = 0; i < 3; i = i + 1) {
      *count1 = *count1 + 1;
    }
    *count0 = *count0 + 1;  
  }
}
