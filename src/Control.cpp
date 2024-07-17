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
#include <limits>

using namespace std;

class Control
{
public:
    Control();
    uint32_t calibrate(void);
    uint32_t control(void);
    uint32_t bcodeControl(void);
    void liftPlaceRoutine(void);
    void readyForInput(bool isReady);
private:
    Motor motorUnit;
    MedicineDatabase medData;
    vector<string> fetchQueue;
    uint32_t gpioHandle;
    Grid grid{&motorUnit, &medData, GRID_DIM_X, GRID_DIM_Y, GRID_UNIT_MAX_COL /* X units */, GRID_UNIT_MAX_ROW /* Y units */};    

};

Control::Control()
{
    fetchQueue.resize(FETCH_QUEUE_MAX_SIZE);
}

void Control::readyForInput(bool isReady)
{
    lgGpioWrite(gpioHandle, LED_GREEN_PIN, isReady);
    lgGpioWrite(gpioHandle, LED_RED_PIN, !isReady);
}

uint32_t Control::calibrate(void)
{
    uint32_t returnValue = SUCCESS;
    //Calibrate Z
    grid.retractZ();

    grid.moveXY({GRID_UNIT_MAX_COL,GRID_UNIT_MAX_ROW}, {0,0}, true /* polling on */);
    grid.moveXY({0,0}, {GRID_UNIT_MAX_COL-1,GRID_UNIT_MAX_ROW-1}, true /* polling on */);
    pthread_t ptid;
    motorUnit.move(Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, DOWN, 10600, 200, false, &ptid);
    pthread_join(ptid, NULL);
    pthread_t ptidx;
    motorUnit.move(X_MOTOR_PIN, X_MOTOR_DIR_PIN, RIGHT, 30, 1000, false, &ptidx);
    pthread_join(ptidx, NULL);

    grid.currentCoord = {0,0};
    return returnValue;

}

void Control::liftPlaceRoutine(void)
{
        grid.extendZ();
        grid.containerLiftOrPlace(true);
        grid.retractZ();
        usleep(500000);
        grid.extendZ();
        grid.containerLiftOrPlace(false);
        grid.retractZ();
        usleep(500000);
}

uint32_t Control::bcodeControl(void)
{
    uint32_t returnValue = SUCCESS;

    if (motorUnit.pinSetup() != 0)
    {
        printf("Error: motor setup returned non-zero\n");
        returnValue = 1;
        return returnValue;
    }
    sensorPinSetup(motorUnit.h);
    gpioHandle = motorUnit.getGpioHandle();
    usleep(1000000);
    //3750


                                
    // pthread_t ptid;
    // motorUnit.move(Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, DOWN, 300, 200, false, &ptid);
    // pthread_join(ptid, NULL);
    // grid.retractZ();
    // grid.containerLiftOrPlace(false);
    // for(;;)
    // {
    //     grid.extendZ();
    //     grid.containerLiftOrPlace(true);
    //     grid.retractZ();

    //     grid.extendZ();
    //     grid.containerLiftOrPlace(false);
    //     grid.retractZ();
    // }

    // for(;;){}


   //   bool contactSens;
   //   for(;;)
   // {
   //       get_y_sensor_value(contactSens);
   //       std::cout << contactSens << "\n";
   //   }
   //   for(;;){}
    // grid.moveXY({0,0}, {0,1}, false);
    // for(;;)
    // {
    //     grid.moveXY({0,0}, {0,1}, false);
    //     usleep(1000000);
    //     grid.moveXY({0,1}, {0,0}, false);
    //     usleep(1000000);
    //     // grid.moveXY({0,0}, {0,1}, false);
    //     // usleep(1000000);
    //     // grid.moveXY({1,0}, {0,0}, false);
    //     // usleep(1000000);
    // }

    // string barcodeTest;
    // grid.getInputBarcode(&barcodeTest, 5);
    // cout << "Barcode: " << barcodeTest << "\n";

    // grid.moveXY({0,0}, {0,1}, false);
    // grid.extendZ();
    // grid.moveXY({0,0}, {2,0}, false);
    // grid.retractZ();
    // pthread_t ptid;
    // motorUnit.move(X_MOTOR_PIN, X_MOTOR_DIR_PIN, RIGHT, 2300, 500, false, &ptid);
    // pthread_join(ptid, NULL);
    
    // grid.moveXY({0,0}, {0,1}, false);
    // usleep(1000000);
    // grid.moveXY({1,0}, {1,1}, false);
    // usleep(1000000);
    // grid.moveXY({1,1}, {2,1}, false);
    // usleep(1000000);
    // grid.moveXY({2,1}, {2,2}, false);
    // usleep(1000000);
    // grid.moveXY({2,2}, {3,2}, false);
    // usleep(1000000);
    // grid.moveXY({3,2}, {3,3}, false);
    // usleep(1000000);
    // grid.moveXY({3,3}, {4,3}, false);
    // usleep(1000000);
    // grid.moveXY({4,3}, {0,0}, false);

    // grid.moveXY({3,3}, {0,3}, false);



    // grid.moveXY({0,3}, {1,3}, false);
    // usleep(1000000);
    // grid.moveXY({1,3}, {2,3}, false);
    // usleep(1000000);
    // grid.moveXY({2,3}, {3,3}, false);
    // usleep(1000000);
    // grid.moveXY({3,3}, {4,3}, false);
    // usleep(1000000);
    // grid.moveXY({0,0}, {0,3}, false);
    // usleep(5000000);    
    // grid.moveXY({0,3}, {0,0}, false); 
    
    //Up down routine with pickup
    // for(;;)
    // {
    //     grid.extendZ()ABC-123
    ;
    //     grid.containerLiftOrPlace(true);
    //     grid.retractZ();
    //     usleep(500000);
    //     grid.extendZ();
    //     grid.containerLiftOrPlace(false);
    //     grid.retractZ();

    //     grid.moveXY({0,0}, {0,3}, false);

    //     grid.extendZ();
    //     grid.containerLiftOrPlace(true);
    //     grid.retractZ();
    //     usleep(500000);
    //     grid.extendZ();
    //     grid.containerLiftOrPlace(false);
    //     grid.retractZ();

    //     grid.moveXY({0,3}, {0,0}, false);
    //     usleep(500000);
    // }    
    // grid.retractZ();

    // for(;;)
    // {
    //     liftPlaceRoutine();
    //     grid.moveXY({4,3}, {0,3}, false);
    //     usleep(3000000);
    //     liftPlaceRoutine();
    //     usleep(3000000);
    //     grid.moveXY({0,3}, {4,3}, false);        
    // }

    
    // grid.moveXY({0,3}, {1,1}, false);
    // usleep(500000);
    // grid.extendZ();
    // grid.containerLiftOrPlace(false);
    // grid.retractZ();

    // grid.moveXY({0,0}, {0,1}, false);
    // grid.extendZ();
    // usleep(1000000);
    // grid.moveXY({2,2}, {0,2}, false);
    // grid.moveXY({4,0}, {4,3}, false);
    // grid.moveXY({4,3}, {0,3}, false);
    // grid.moveXY({0,0}, {2,3}, false);
    // liftPlaceRoutine();
    // grid.moveXY({2,3}, {0,3}, false);
    // calibrate();
    
    // grid.moveXY({4,3}, {0,3}, false);
    // liftPlaceRoutine();
    // grid.moveXY({0,0}, {0,3}, false);
    // usleep(10000000);
    // grid.moveXY({0,3}, {4,3}, false);
    // grid.moveXY({1,0}, {0,0}, false);
    //grid.extendZ();
    // // liftPlaceRoutine();
    //for(;;){ } 


    std::cout << "Initial Calibration\n";
    calibrate();
    std::cout << "Calibration complete!\n";
    readyForInput(true);
    std::string bcodeCommand;
    readyForInput(false);
    
    for(;;)
    {
        std::cout << "Please scan barcodes to begin\n";


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
            readyForInput(true);
            if(grid.getInputBarcode(&bcode, 20, false, false) != SUCCESS)
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
            readyForInput(false);

        }
        /* Single Fetch */
        else if(bcodeCommand == "A-0030-Z")
        {
            string bcode;
            std::cout << "Fetching next scanned barcode";
            readyForInput(true);
            if(grid.getInputBarcode(&bcode, 20, false, false) != SUCCESS)
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
            readyForInput(false);
        }
        /* Multi Fetch */
        else if(bcodeCommand == "A-0040-Z")
        {
            string bcode;
            std::cout << "Fetching multiple barcodes\n";
            int fetchQueueSize = 0;           
            readyForInput(true);
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

            readyForInput(false);
            std::cout << "Fetch queue has been created\nStarting fetches\n";
            for(int i = 0; i < fetchQueueSize; i++)
            {
                grid.fetchFromShelfByBarcode(fetchQueue[i]);
            }

        }
        else if(bcodeCommand == "A-0050-Z") // Return
        {
            // calibrate();
            grid.returnToShelf();
            cout << "Return sequence complete\n";
        }
        else if(bcodeCommand == "A-0060-Z") // Force return
        {
            grid.forceReturn();
            cout << "Force return complete\n";
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
            // calibrate();
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
