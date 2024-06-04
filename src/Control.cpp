/*- 'Main'
 - calibration func
*/

//#include "Grid.h"
#include "motor.hpp"

class Control {
public:
    int calibrate();
    // more control functions to be added
};

int main()
{
    Motor motorUnit;

    if (motorUnit.motorSetup() != 0)
    {
        // ERROR
        return;
    }
    //int h = lgGpiochipOpen(4); // open /dev/gpiochip0

   
    lgChipInfo_t cInfo;

    // TODO should following line be in motorSetup()?
    // int status = lgGpioGetChipInfo(h, &cInfo);

    // if (status == LG_OKAY)
    // {
    //     // printf("lines=%d name=%s label=%s\n",
    //     // cInfo.lines, cInfo.name, cInfo.label);
    // }
    // else
    // {
    //     printf("Did not successfully\n");
    // }

    // lgLineInfo_t lInfo;
    // for(int gpio = 0; gpio < 54; gpio++)
    // {
    //     status = lgGpioGetLineInfo(h, gpio, &lInfo);

    //     if (status == LG_OKAY)
    //     {
    //         printf("lFlags=%d name=%s user=%s\n",
    //         lInfo.lFlags, lInfo.name, lInfo.user);
    //     }
    // }
 

    uint32_t x_location;
    uint32_t y_location;
    
    // get function selection from ui
    // call appropriate grid function 

    for(;;)
    {
        uint32_t next_x;
        uint32_t next_y;
        char* moveOrExtend;

        printf("\"move\" or \"extend\"? (lowercase, no whitespace) ");
        std::cin >> moveOrExtend;

        if (moveOrExtend == "move");
        {
            printf("Enter x coordinate: ");
            std::cin >> next_x;
            printf("Enter y coordinate: ");
            std::cin >> next_y;

            if (next_x > gridmaxy || next_y > gridmaxx)
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
            x_location = next_x;
            y_location = next_y;

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

#endif // CONTROL_H
