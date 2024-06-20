/*- 'Main'
 - calibration func
*/

//#include "Grid.h"
#include "Motor.hpp"
#include "Grid.hpp"
#include <stdlib.h>
#include <iostream>
#include "defines.hpp"
#include <string.h>

class Control {
public:
    int calibrate();
    // more control functions to be added
};

int main()
{
    uint32_t returnValue = SUCCESS;
    MedicineDatabase medData;
    Motor motorUnit;
    Grid grid{&motorUnit, &medData, GRID_DIM_X, GRID_DIM_Y, 5 /* X units */, 4 /* Y units */};

    if (motorUnit.motorSetup() != 0)
    {
        printf("Error: motor setup returned non-zero\n");
        return returnValue;
    }

    grid.moveXY({0,0}, {3,3});
    grid.moveXY({3,3}, {0,0});
    //Test grid functions
    grid.printGrid();
    grid.shelfSetup();
    grid.printGrid();

    //Test movement
    // ShelfCoord curr {1,0};
    // ShelfCoord dest {0,0};
    // cout << "Moving to dest\n";
    // grid.moveXY(curr, dest);
    // cout << "Current Coord: (" << grid.currentCoord.x << "," << grid.currentCoord.y << ")\n";
    // cout << "Moving back\n";
    // // grid.moveXY(curr, dest);
    // cout << "Current Coord: (" << grid.currentCoord.x << "," << grid.currentCoord.y << ")\n";
    
    if(grid.gridContainers[1][1].occupied)
    {
        // Medicine med = grid.gridContainers[1][1].med;
        grid.fetchFromShelf(grid.gridContainers[1][1].med);
    }
    else
    {
        cout << "Not occ\n";
    }

    grid.returnToShelf(grid.gridContainers[1][1].med);

    grid.moveXY(grid.currentCoord, {0,0});

    // get function selection from ui
    // call appropriate grid function 
    return returnValue;

    for(;;)
    {

        uint32_t next_x;
        uint32_t next_y;
        std::string moveOrExtend;

        printf("\"move\" or \"extend\"? (lowercase, no whitespace) ");
        std::cin >> moveOrExtend;

        if (moveOrExtend == "move")
        {
            printf("Enter x coordinate: ");
            std::cin >> next_x;
            printf("Enter y coordinate: ");
            std::cin >> next_y;

            if (next_x > GRID_MAX_X || next_y > GRID_MAX_Y)
            {
                printf("Out of bounds");
                //error message
                continue;
            }

            // TO DO Complete the following -
            //Move in x direction
            // TO DO calculate pulses and speed, then move
            // motorUnit.move(X_MOTOR_PIN, Y_MOTOR_DIR_PIN, uint32_t direction, uint32_t pulses, uint32_t motorSpeed)

            //Move in y direction
            // TO DO calculate pulses and speed
            //motorUnit.move(Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, uint32_t direction, uint32_t pulses, uint32_t motorSpeed)

            // Update current x and y coordinates
            // x_location = next_x;
            // y_location = next_y;

        }
        else // extend Z
        {
        //     //Extend Z
        //     motorUnit.move(h, Z_MOTOR_PIN, Y_MOTOR_DIR_PIN, 0, 0);
        //     // Lift on Y
        //     motorUnit.move(h, Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, 1, 1);
        //     // Retract Z
        //     motorUnit.move(h, Z_MOTOR_PIN, Y_MOTOR_DIR_PIN, 0, 0);
        //     // Move Y Full Step
        //     motorUnit.move(h, Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, dir, 0);
        //     // Move along X 
        //     motorUnit.move(h, X_MOTOR_PIN, X_MOTOR_DIR_PIN, !dir, 0);
        //     motorUnit.move(h, X_MOTOR_PIN, X_MOTOR_DIR_PIN, !dir, 0);
        //     // Extend Z
        //     motorUnit.move(h, Z_MOTOR_PIN, Y_MOTOR_DIR_PIN, 0, 0);
        //     // Put down box
        //     motorUnit.move(h, Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, 0, 1);
        //     // Retract Z
        //     motorUnit.move(h, Z_MOTOR_PIN, Y_MOTOR_DIR_PIN, 0, 0);
        }

    }

    return 0;
}
