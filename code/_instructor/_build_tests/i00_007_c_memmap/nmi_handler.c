#include <stdbool.h>
#include <stdint.h>

#define NMI_COUNT 0x0064U

void nmi_handler (void) __critical __interrupt {
  volatile uint8_t *count = (volatile uint8_t *) NMI_COUNT;

  *count = *count + 1;
}
