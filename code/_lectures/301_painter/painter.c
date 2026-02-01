#include <stdint.h>
#include <stdbool.h>
#include "baremetal_binary.h"

// VIEW
#define MATRIX_WIDTH (16)
#define MATRIX_BASE ((volatile uint8_t *)0xE020U)
#define HEX_DISP ((volatile uint8_t *)0xE800U)
#define COLOR_DISP ((volatile bool *)0xE000U)

// CONTROLLER
#define KEYPAD ((volatile uint8_t *)0xD010U)

// UART debug output
#define UART_DATA_OUT ((volatile uint8_t *)0xE040U)

// typedefs of enum's and struct's
typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    TOGGLE_COLOR
} command;

typedef struct {
    uint8_t matrix[16];
    uint8_t row, col;
    uint8_t color; // 0 = black, 1 = yellow
} model_t;

// MODEL functions
void model_paint_row_col(model_t *mp, uint8_t row, uint8_t col, uint8_t color){ 
    if (color) { // we only support 0=black and 1=yellow now
        // set dot, don't touch others
        mp->matrix[col] = mp->matrix[col] | (1U << row);
    } else {
        // clear dot, don't touch others
        mp->matrix[col] = mp->matrix[col] & ~(1U << row);
    }
}

void model_init(model_t *mp){
    for (uint8_t i = 0; i < MATRIX_WIDTH; i=i+1) {
        mp->matrix[i] = B8(00000000);
    }
    mp->row = 3;
    mp->col = 4;
    mp->color = 1;
    model_paint_row_col(mp, mp->row, mp->col, mp->color);
}

// MODEL move or switch color
void model_update(model_t *mp, command c) {

    // declare new necessary stuff
    uint8_t new_row   = mp->row;
    uint8_t new_col   = mp->col;
    uint8_t new_color = mp->color;
    // we don't copy matrix. it's not needed

    switch (c) {
        case DOWN:  new_row = (mp->row == 0) ? mp->row : mp->row - 1;
                    break;
        case UP:    new_row = (mp->row == 7) ? mp->row : mp->row + 1;
                    break;
        case LEFT:  new_col = (mp->col == 0) ? mp->col : mp->col - 1;
                    break;
        case RIGHT: new_col = (mp->col == (MATRIX_WIDTH-1)) ? mp->col: mp->col + 1;
                    break;
        case TOGGLE_COLOR:  
                    new_color = !mp->color;
                    break;
        default:    break;
    }

    // state <= next_state
    mp->row      = new_row;
    mp->col      = new_col;
    mp->color    = new_color;
    // update model
    model_paint_row_col(mp, mp->row, mp->col, mp->color);
}

// VIEW update - transfer MODEL to VIEW
void update_view(const model_t *mp){
    for (uint8_t i = 0; i < MATRIX_WIDTH; i=i+1) {
        *(MATRIX_BASE + i) = mp->matrix[i];
    }
    *(HEX_DISP +1) = mp->row;
    *(HEX_DISP)    = mp->col;
    *(COLOR_DISP)  = mp->color;
}

// CONTROLLER
void read_keypad_and_model_update(model_t *mp){
    uint8_t key = *KEYPAD;  // remember KEYPAD is read2clear
    if (key & B8(10000000)) {
        // key is valid, strip valid bit
        key = key & B8(01111111);
        *UART_DATA_OUT = key;
    } else {
        // key is not valid, return
        return;
    }
    switch (key) {
        case B8(00010001) : // row 1 col 1, UP arrow
                            model_update(mp, UP);
                            break;
        case B8(00100000) : // row 2 col 0, LEFT arrow
                            model_update(mp, LEFT);
                            break;
        case B8(00100010) : // row 2 col 2, RIGHT arrow
                            model_update(mp, RIGHT);
                            break;
        case B8(00110001) : // row 3 col 1, DOWN arrow
                            model_update(mp, DOWN);
                            break;
        case B8(00110011) : // row 3 col 3, TOGGLE_COLOR
                            model_update(mp, TOGGLE_COLOR);
                            break;
        default:            break;
    }
}

void main(void){
    model_t m;
    model_t *mp = &m;
    model_init(mp);
    while (true) {
        read_keypad_and_model_update(mp);
        update_view(mp);
    }
}
