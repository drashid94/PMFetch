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

    // if (motorUnit.motorSetup() != 0)
    // {
    //     printf("Error: motor setup returned non-zero\n");
    //     return returnValue;
    // }

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
            else
            {
                continue;
            }
        }

        else //return
        {
            printf("Scan barcode - ");
            cin >> medicationBarcode;

            if (grid.returnToShelfByBarcode(medicationBarcode) == 1)
            {
                printf("Error");
            }
            else
            {
                continue;
            }
        }

    }

    return 0;
}
