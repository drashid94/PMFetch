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
#include <unistd.h>

class Control {
public:
    int calibrate();
    // more control functions to be added
};

int main()
{    
    // Motor motorUnitTest;
    // if (motorUnitTest.motorSetup() != 0)
    // {
    //     printf("Error: motor setup returned non-zero\n");
    //     return 0;
    // }
    
    // uint32_t mspeed = 450;
    // uint32_t pulses = 4300;
    // uint32_t input = 0;
    // for(;;)
    // {
    //     motorUnitTest.move(Z_MOTOR_PIN, Z_MOTOR_DIR_PIN, 0, pulses, mspeed);
    //     usleep(1000000);
    //     motorUnitTest.move(Z_MOTOR_PIN, Z_MOTOR_DIR_PIN, 1, pulses, mspeed);
    //     cin >> input;
    // }

    // //0 is extending

    // for(;;);
    uint32_t returnValue = SUCCESS;
    MedicineDatabase medData;
    Motor motorUnit;
    Grid grid{&motorUnit, &medData, GRID_DIM_X, GRID_DIM_Y, 5 /* X units */, 4 /* Y units */};

    if (motorUnit.motorSetup() != 0)
    {
        printf("Error: motor setup returned non-zero\n");
        return returnValue;
    }

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
    
   

    for(;;)
    {

        string medicationBarcode;
        string medicationName;
        std::string fetchOrReturn;

        printf("\"fetch\" or \"return\"? (lowercase, no whitespace) ");
        std::cin >> fetchOrReturn;

        if (fetchOrReturn == "fetch")
        {
            printf("Enter medicine name to fetch - ");
            cin>> medicationName;
            
            if (grid.fetchFromShelfByName(medicationName) == 1)
            {
                printf("Error");
            }
        }

        else if(fetchOrReturn == "return")//return
        {
            printf("Scan barcode - ");
            cin >> medicationBarcode;

            if (grid.returnToShelfByBarcode(medicationBarcode) == 1)
            {
                printf("Error");
            }
        }
        grid.moveXY(grid.currentCoord, {0,0});

    }

    return 0;
}
