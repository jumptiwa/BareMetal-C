#include <stdbool.h>
#include <stdint.h>

#define ADDR0 0x0060U
#define ADDR1 0x0062U

void main(void) {
  volatile uint8_t *count0 = (volatile uint8_t *) ADDR0;
  volatile uint8_t *count1 = (volatile uint8_t *) ADDR1;
  
  *count0 = 0;
  *count1 = 0;

  while (true) {
    for (uint8_t i = 0; i < 3; i = i + 1) {
      *count1 = *count1 + 1;
    }
    *count0 = *count0 + 1;  
  }
}
