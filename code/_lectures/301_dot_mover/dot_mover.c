#include <stdint.h>
#include <stdbool.h>
#include "baremetal_binary.h"

// VIEW
#define MATRIX_WIDTH (16)
#define MATRIX_BASE ((volatile uint8_t *)0xE020)

// CONTROLLER
#define KEYPAD ((volatile uint8_t *)0xD010U)

// UART debug output
#define UART_DATA_OUT ((volatile uint8_t *)0xE040U)

// MODEL state and prototypes:
uint8_t matrix[16];
uint8_t row, col;

void model_set_row_col(uint8_t row, uint8_t col);
void model_clear_row_col(uint8_t row, uint8_t col);

// MODEL init
void model_init(void){
    for (uint8_t i = 0; i < MATRIX_WIDTH; i=i+1) {
        matrix[i] = B8(00000000);
    }
    row = 3;
    col = 4;
    model_set_row_col(row, col);
}

// MODEL set row, col
void model_set_row_col(uint8_t row, uint8_t col){
    matrix[col] = matrix[col] | (1U << row);
}

// MODEL clear row, col
void model_clear_row_col(uint8_t row, uint8_t col){
    matrix[col] = matrix[col] & ~(1U << row);
}

// MODEL move
typedef enum {
    NONE, UP, DOWN, LEFT, RIGHT
} direction;

void model_move(direction d) {
//    uint8_t new_row = row;
//    uint8_t new_col = col;
    uint8_t new_row, new_col;
    switch (d) {
        case NONE:  new_row = row;
                    new_col = col;
                    break;
        case DOWN:  new_col = col;
                    new_row = (row == 0) ? row : row - 1;
                    break;
        case UP:    new_col = col;
                    new_row = (row == 7) ? row : row + 1;
                    break;
        case LEFT:  new_col = (col == 0) ? col : col - 1;
                    new_row = row;
                    break;
        case RIGHT: new_col = (col == (MATRIX_WIDTH-1)) ? col: col + 1;
                    new_row = row;
                    break;
    }
    if ( !((new_row) == row && (new_col == col)) ) {
        model_clear_row_col(row, col);
        model_set_row_col(new_row, new_col);
    }
    row = new_row;
    col = new_col;
}

// VIEW update - transfer MODEL to VIEW
void update_view(void){
    for (uint8_t i = 0; i < MATRIX_WIDTH; i=i+1) {
        *(MATRIX_BASE + i) = matrix[i];
    }
}

// CONTROLLER
void read_keypad_and_update_model(void){
    uint8_t key = *KEYPAD;
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
                            model_move(UP);
                            break;
        case B8(00100000) : // row 2 col 0, LEFT arrow
                            model_move(LEFT);
                            break;
        case B8(00100010) : // row 2 col 2, RIGHT arrow
                            model_move(RIGHT);
                            break;
        case B8(00110001) : // row 3 col 1, DOWN arrow
                            model_move(DOWN);
                            break; 
    }
}

void main(void){
    model_init();
    while (true) {
        read_keypad_and_update_model();
        update_view();
    }
}
