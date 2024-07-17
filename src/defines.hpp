#ifndef DEFINES_H
#define DEFINES_H

// IRL PARAMS
#define GRID_DIM_X 100 //X dimension of shelf in cm
#define GRID_DIM_Y 50 //Y dimensions of shelf in cm
#define LIFT_AMOUNT_CM 6 // Amount to lift container in cm

#define GRID_UNIT_MAX_COL 5
#define GRID_UNIT_MAX_ROW 4

#define RIGHT 0
#define UP 1   /// keith changed this from a 0 to 1
#define LEFT 1
#define DOWN 0 /// keith changed this from a 1 to 0
#define EXTEND 1
#define RETRACT 0

#define Y_MOTOR_SPEED 200
#define X_MOTOR_SPEED 1000
#define Z_MOTOR_SPEED 350	

#define NUM_RETURN_LOCATIONS 3
#define FETCH_QUEUE_MAX_SIZE 36

struct ShelfCoord
{
    int x;
    int y;
};

#define SUCCESS 0


#define EXIT_POINT EXIT_LABEL:
#define EXIT_FUNCTION(ret, err) ret = err; \
                                goto EXIT_LABEL
#define EXIT_FUNCTION_NOVAL goto EXIT_LABEL

// struct for positions - x and y variables
#endif