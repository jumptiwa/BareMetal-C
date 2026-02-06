#include <stdint.h>
#include <stdbool.h>
#include "baremetal_binary.h"

// MODEL+VIEW
#define DISP_WIDTH (16)

// VIEW
#define MATRIX_BASE ((volatile uint8_t * const)0xE020U)
#define HEX_DISP ((volatile uint8_t * const)0xE808U)
#define TICK_LED ((volatile bool *)0xE000U)

// CONTROLLER
#define KEYPAD ((volatile const uint8_t * const)0xD010U)

// UART debug output
#define UART_DATA_OUT ((volatile uint8_t *)0xE040U)

// MODEL-CONTROLLER message
typedef enum {
    NONE, STOP, LEFT, RIGHT, UP, DOWN
} command;

typedef enum {
    STOP, LEFT, RIGHT, UP, DOWN
} direction;

typedef struct {
    uint8_t row, col;
    //uint8_t prev_row, prev_col;
    direction dir;
} model_t;

void model_init(model_t *mp){
    mp->row = 4;
    mp->col = 7;
    //mp->prev_row = 4;
    //mp->prev_col = 7;
    mp->dir = STOP;
}

void model_update(model_t *mp, command c){
    // avoid paying stack tax
    static uint8_t new_row, new_col;
    static direction new_dir; 
    switch (c){
        case STOP:  new_row = mp->row;
                    new_col = mp->col;
                    new_dir = STOP;
                    break;
        case LEFT:  new_row = mp->row;
                    new_col = (mp->col == 0)? DISP_WIDTH -1 : mp->col - 1;
                    break;
        case RIGHT: new_row = mp->row;
                    new_col = (mp->col >= DISP_WIDTH -1)? 0 : mp->col + 1;
                    break;
        case UP:    new_col = mp->col;
                    new_row = (mp->row == 7)? 0 : mp->row + 1;
                    break;
        case DOWN:  new_col = mp->col;
                    new_row = (mp->row == 0)? 7 : mp->row - 1;
                    break;
        default:    break;
    }
    // update state
    mp->dir = c;
    //mp->prev_row = mp->row;
    //mp->prev_col = mp->col;
    mp->row = new_row;
    mp->col = new_col;
}

// VIEW
void view_update(model_t *mp){
    for(uint8_t i = 0; i < DISP_WIDTH; i = i + 1){
        *(MATRIX_BASE + i) = (mp->col == i)? 1U << (7 - mp->row) : 0;
    }
}

// CONTROLLER
command controller_read(void){
    static uint8_t key;
    static command c;
    key = *KEYPAD;
    if (key & B8(10000000)){
        // valid key

    }
    return c;
}

void nmi_handler(void) __critical __interrupt {
    // we declare them all as static to avoid paying stack allocation
    static bool busy = false;
    static bool initialized = false;
    static model_t m;
    static model_t *mp = &m;

    if (busy) {
        return; // we cannot afford to do a second interrupt
    }
    if (!initialized) {
        model_init(mp);
        initialized = true;
        busy = false;
        return;
    }
    // CONTROLLER read and MODEL update
    model_update(mp, controller_read());
    view_update(mp);
    busy = false;
    return;
}
