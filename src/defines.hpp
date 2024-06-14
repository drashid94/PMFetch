#ifndef DEFINES_H
#define DEFINES_H

// IRL PARAMS
#define GRID_DIM_X 100 //X dimension of shelf in cm
#define GRID_DIM_Y 50 //Y dimensions of shelf in cm
#define LIFT_AMOUNT_CM 6 // Amount to lift container in cm

#define GRID_MAX_X 5
#define GRID_MAX_Y 5

struct ShelfCoord
{
    uint8_t x;
    uint8_t y;
};

#define SUCCESS 0
#define EXIT_POINT EXIT_LABEL:
#define EXIT_FUNCTION(ret, err) ret = err; \
                                goto EXIT_LABEL
#define EXIT_FUNCTION_NOVAL goto EXIT_LABEL

// struct for positions - x and y variables
#endif