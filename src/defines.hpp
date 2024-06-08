#ifndef DEFINES_H
#define DEFINES_H

// IRL PARAMS
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

// struct for positions - x and y variables
#endif