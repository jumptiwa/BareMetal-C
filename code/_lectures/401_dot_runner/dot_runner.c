#include <stdint.h>
#include <stdbool.h>
#include "baremetal_binary.h"

// MODEL+VIEW
#define DISP_WIDTH (16)

// VIEW
#define MATRIX_BASE ((volatile uint8_t * const)0xE020U)
#define HEX_DISP ((volatile uint8_t * const)0xE808U)

// NMI handler monitor
#define IN_NMI_LED ((volatile bool *)0xE000U)

// CONTROLLER
#define KEYPAD ((volatile const uint8_t * const)0xD010U)

// UART debug output
#define UART_DATA_OUT ((volatile uint8_t *)0xE040U)

// MODEL-CONTROLLER message
typedef enum {
    NONE, STOP, LEFT, RIGHT, UP, DOWN
} command;

typedef struct {
    uint8_t row, col;
    command cmd;
} model_t;

void model_init(model_t *mp){
    mp->row = 4;
    mp->col = 7;
    mp->cmd = STOP;
}

void model_update(model_t *mp, command c){
    // avoid paying stack tax
    static uint8_t new_row, new_col;
    static command new_cmd;
    new_cmd = (c == NONE) ? mp->cmd : c;
    new_row = mp->row;
    new_col = mp->col;
    switch (new_cmd){
        case STOP:  break;
        case LEFT:  new_col = (mp->col == 0)? DISP_WIDTH -1 : mp->col - 1;
                    break;
        case RIGHT: new_col = (mp->col >= DISP_WIDTH -1)? 0 : mp->col + 1;
                    break;
        case DOWN:  new_row = (mp->row == 7)? 0 : mp->row + 1;
                    break;
        case UP:    new_row = (mp->row == 0)? 7 : mp->row - 1;
                    break;
        default:    break;
    }
    // update state
    mp->cmd = new_cmd;
    mp->row = new_row;
    mp->col = new_col;
}

// VIEW
void view_update(model_t *mp){
    for(uint8_t i = 0; i < DISP_WIDTH; i = i + 1){
        *(MATRIX_BASE + i) = (mp->col == i)? 1U << (7 - mp->row) : 0;
    }
    *HEX_DISP = (mp->row << 4) | mp->col;
}

// CONTROLLER
command controller_read(void){
    static uint8_t key;
    static command c;
    key = *KEYPAD;
    if (! (key & B8(10000000)) ){
        return NONE;    // no new keypress
    }
    // valid key
    switch (key & B8(01111111)){
        case B8(00010001):  c = UP;     // UP
                            break;
        case B8(00100000):  c = LEFT;   // LEFT
                            break;
        case B8(00100001):  c = STOP;   // STOP
                            break;
        case B8(00100010):  c = RIGHT;  // RIGHT
                            break;
        case B8(00110001):  c = DOWN;   // DOWN
                            break;
        default:            c = NONE;
                            break; 
    }
    return c;
}

void nmi_handler(void) __critical __interrupt {
    // we declare them all as static to avoid stack allocation
    static bool busy = false;
    static bool initialized = false;
    static model_t m;
    static model_t *mp = &m;
    static command c;

    if (busy) {
        return; // we cannot afford to do a second interrupt
    }

    busy = true;
    *IN_NMI_LED = true;
    if (!initialized) {
        model_init(mp);
        initialized = true;
        busy = false;
        *IN_NMI_LED = false;
        return;
    }
    // CONTROLLER read and MODEL update
    c = controller_read();
    model_update(mp, c);
    view_update(mp);
    busy = false;
    *IN_NMI_LED = false;
    return;
}

void main(void){
    while (true) {
    }
}
