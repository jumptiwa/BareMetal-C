#include <stdint.h>
#include <stdbool.h>
#include "baremetal_binary.h"

#define MATRIX_WIDTH (16)
#define MATRIX_BASE ((volatile uint8_t *)0xE020)

// MODEL state
uint8_t matrix[16];
uint8_t row, col;

// MODEL init
void model_init(void){
    model_clear();
    row = 3;
    col = 4;
    model_light_row_col(row, col);
}

// MODEL clear display
void model_clear(void){
    // clear all matrix
    for (uint8_t i = 0; i < MATRIX_WIDTH; i=i+1) {
        matrix[i] = B8(00000000);
    }
}

// MODEL light row, col
void model_light_row_col(uint8_t row, uint8_t col){
    matrix[col] = matrix[col] | (1U << row);
}

// MODEL off row, col
void model_off_row_col(uint8_t row, uint8_t col){
    matrix[col] = matrix[col] & ~(1U << row);
}

// VIEW update - transfer MODEL to VIEW
void update_view(){
    for (uint8_t i = 0; i < MATRIX_WIDTH; i=i+1) {
        *(MATRIX_BASE + i) = matrix[i];
    }
}
