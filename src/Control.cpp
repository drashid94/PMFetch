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
#include "Sensors.h"
#include <ncurses.h>

using namespace std;

class Control
{
public:
    Control();
    uint32_t calibrate(void);
    uint32_t control(void);
    uint32_t bcodeControl(void);
private:
    Motor motorUnit;
    MedicineDatabase medData;
    vector<string> fetchQueue;
    Grid grid{&motorUnit, &medData, GRID_DIM_X, GRID_DIM_Y, GRID_UNIT_MAX_COL /* X units */, GRID_UNIT_MAX_ROW /* Y units */};    

};

Control::Control()
{
    fetchQueue.resize(FETCH_QUEUE_MAX_SIZE);
}

uint32_t Control::calibrate(void)
{
    uint32_t returnValue = SUCCESS;
    
    grid.moveXY({GRID_UNIT_MAX_COL-1,GRID_UNIT_MAX_ROW-1}, {0,0}, true /* polling on */);

    //Calibrate Z
    // grid.retractZ();

    grid.currentCoord = {0,0};
    return returnValue;

}

uint32_t Control::bcodeControl(void)
{
    uint32_t returnValue;

    if (motorUnit.pinSetup() != 0)
    {
        printf("Error: motor setup returned non-zero\n");
        return returnValue;
    }
    sensorPinSetup(motorUnit.h);    

    /* Testing Code */
     // grid.moveXY({0,0}, {2,1}, false);
     // for(;;)
     // {
     //    int asdf;
     //    grid.moveXY({1,1}, {1,0}, false);
     //    cin >> asdf;
     //    grid.moveXY({1,0}, {1,1}, false);
     //    cin >> asdf;
     // }
    // for(;;);

    /* --------------------------------------------------    */

    std::cout << "Initial Calibration\n";
    calibrate();

    std::cout << "Calibration complete!\n";

    std::string bcodeCommand;
    
    for(;;)
    {
        cout << "Please scan barcodes to begin\n";

        std::cin >> bcodeCommand;

        /* Setting up */
        if(bcodeCommand == "A-0010-Z")
        {
            //Add item to the shelf
            std::cout << "Setting up the shelf\n";
            grid.shelfSetupByBarcode();

        }
        /* Delete */
        else if(bcodeCommand == "A-0020-Z")
        {
            string bcode;
            std::cout << "Deleting next scanned medication\n";
            if(getInputBarcode(&bcode, 20) != SUCCESS)
            {
                std::cout << "Operation timeout\n";
                continue;
            }

            if (bcode == "A-0080-Z")
            {
                std::cout << "Delete cancelled\n";
                continue;
            }

            grid.deleteFromShelf(bcode);

        }
        /* Single Fetch */
        else if(bcodeCommand == "A-0030-Z")
        {
            string bcode;
            std::cout << "Fetching next scanned barcode";
            if(getInputBarcode(&bcode, 20) != SUCCESS)
            {
                std::cout << "Operation timeout\n";
                continue;
            }

            if (bcode == "A-0080-Z")
            {
                std::cout << "Fetch cancelled\n";
                continue;
            }

            grid.fetchFromShelfByBarcode(bcode);
        }
        /* Multi Fetch */
        else if(bcodeCommand == "A-0040-Z")
        {
            string bcode;
            std::cout << "Fetching multiple barcodes\n";
            int fetchQueueSize = 0;           
            for(int i = 0; i < FETCH_QUEUE_MAX_SIZE; i++)
            {                
                std::cin >> bcode;
                if(grid.isMedValid(bcode) == SUCCESS)
                {
                    fetchQueue[i] = bcode;
                    fetchQueueSize++;
                }
                else if(bcode == "A-0040-Z") break;
                else
                {
                    std::cout << "Unrecognized barcode entered: " << bcode << "\n";
                }                                
            }

            std::cout << "Fetch queue has been created\nStarting fetches\n";
            for(int i = 0; i < fetchQueueSize; i++)
            {
                grid.fetchFromShelfByBarcode(fetchQueue[i]);
            }

        }
        else if(bcodeCommand == "A-0050-Z") // Return
        {
            grid.returnToShelf();
            cout << "Return sequence complete\n";
        }
        else if(bcodeCommand == "A-0060-Z")
        {

        }
        else if(bcodeCommand == "A-0070-Z")
        {
            
        }
        else if(bcodeCommand == "A-0080-Z") // Cancel selection
        {
            // does nothing
        }
        else if(bcodeCommand == "A-0090-Z") // Calibrate
        {
            calibrate(); 
        }
        else if(bcodeCommand == "A-0100-Z") // printGrid
        {
            grid.printGrid();    
        }
        else if(grid.isMedValid(bcodeCommand) == SUCCESS)
        {
            grid.fetchFromShelfByBarcode(bcodeCommand);
        }
    }



}

int main()
{    
    cout << "Main function\n";
    Control controlUnit;
    controlUnit.bcodeControl();
    return 0;
}
