#include <stdint.h>
#include <stdbool.h>

// VIEW
#define VIEW_PERIOD ((volatile uint8_t * const)0xE800U)
#define VIEW_LIGHT  ((volatile bool    * const)0xE000U)

// CONTROLLER
#define CONTROLLER_PLUS  ((volatile const bool * const)0xD007U)
#define CONTROLLER_MINUS ((volatile const bool * const)0xD006U)

// MODEL
typedef struct {
    bool light;
    uint8_t period;
    uint8_t count;
} model_t;

typedef enum {
    NONE, PLUS, MINUS
} command;

void model_init(model_t *mp){
    mp->count = 0;
    // ADD CODE
}

void model_update(model_t *mp, command c){
    switch (c) {
        case MINUS: mp->count = 1; // WRONG
                    break;
        case PLUS:  mp->count = 2; // WRONG
                    break;
        case NONE:  mp->count = 0; // WRONG
                    break;
        default:    break;
    }
}

// VIEW
void view_update(const model_t *mp){
    // update light
    *VIEW_LIGHT = mp->light;
    // ADD CODE
    *VIEW_PERIOD = 0x99U; // WRONG
}

// CONTROLLER
command controller_read(void){
    command c;
    c = NONE; // WRONG
    return c;
}

void main(void){
    model_t m;
    model_t *mp = &m;
    command c;
    model_init(mp);
    while (true) {
        // VIEW  UPDATE
        view_update(mp);
        // CONTROLLER
        c = controller_read();
        // MODEL UPDATE
        model_update(mp, c);
    }
}
