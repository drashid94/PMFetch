#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "Motor.hpp"
#include "errors.hpp"
#include "defines.hpp"

// void move(uint32_t h, uint32_t motorPin, uint32_t motorDirPin, uint32_t direction, uint32_t lift)
// {
//     uint32_t pulseCount = 0;
//     uint32_t motorSpeed = 0;

//     if(motorPin == X_MOTOR_PIN) 
//     { 
//         motorSpeed = MOTOR_SPEED_X;
//         pulseCount = PULSES_PER_UNIT_X;
//     }
//     else if (motorPin == Y_MOTOR_PIN)
//     {
//         if(lift)
//         {
//             pulseCount = PULSES_PER_LIFT_Y;
//         }
//         else
//         {            
//             pulseCount = PULSES_PER_FULL_STEP_Y;
//         }
//         motorSpeed = MOTOR_SPEED_Y;
//     }
//     else if (motorPin == Z_MOTOR_PIN)
//     {
//         motorSpeed = MOTOR_SPEED_Z;
//         pulseCount = PULSES_PER_UNIT_Z;
//     }

//     if(motorPin != Z_MOTOR_PIN)
//     {
//         lgGpioWrite(h, motorDirPin, direction);
//         usleep(10);
//     }

//     for(uint32_t i = 0; i < pulseCount; i++)
//     {
//         lgGpioWrite(h, motorPin, 1);
//         usleep(motorSpeed);
//         lgGpioWrite(h, motorPin, 0);
//         usleep(motorSpeed);
//     }
// }



// int main()
// {
//     int h = lgGpiochipOpen(4); // open /dev/gpiochip0

//     if (h >= 0)
//     {
//         printf("Opened Chip Successfully!\n");
//     }
//     else
//     {
//         printf("Failed to open GPIO chip\n");
//     }

//     lgChipInfo_t cInfo;

//     int status = lgGpioGetChipInfo(h, &cInfo);

//     if (status == LG_OKAY)
//     {
//         // printf("lines=%d name=%s label=%s\n",
//         // cInfo.lines, cInfo.name, cInfo.label);
//     }
//     else
//     {
//         printf("Did not successfully\n");
//     }

//     // lgLineInfo_t lInfo;
//     // for(int gpio = 0; gpio < 54; gpio++)
//     // {
//     //     status = lgGpioGetLineInfo(h, gpio, &lInfo);

//     //     if (status == LG_OKAY)
//     //     {
//     //         printf("lFlags=%d name=%s user=%s\n",
//     //         lInfo.lFlags, lInfo.name, lInfo.user);
//     //     }
//     // }
    
//     status = lgGpioClaimOutput(h, 0, X_MOTOR_PIN, 0);
//     if(status != LG_OKAY) { printf("Error: status non 0\n"); }
//     status = lgGpioClaimOutput(h, 0, X_MOTOR_DIR_PIN, 0);
//     if(status != LG_OKAY) { printf("Error: status non 0\n"); }
//     status = lgGpioClaimOutput(h, 0, Y_MOTOR_PIN, 0);
//     if(status != LG_OKAY) { printf("Error: status non 0\n"); }
//     status = lgGpioClaimOutput(h, 0, Y_MOTOR_DIR_PIN, 0);
//     if(status != LG_OKAY) { printf("Error: status non 0\n"); }
//     status = lgGpioClaimOutput(h, 0, Z_MOTOR_PIN, 0);
//     if(status != LG_OKAY) { printf("Error: status non 0\n"); }

//     char sel;
//     uint32_t dir;
//     uint32_t motorPin = 0;
//     uint32_t motorDirPin = 0;
//     uint32_t lift = 0;
//     for(;;)
//     {
//         printf("Enter Charactor Command \nx (Move X Motor)\ny (Move Y Motor)\nz (Move Z Motor)\nr (Start Demo Routine)\n");
//         std::cin >> sel;
//         printf("Enter Direction Command \n1 (Positive Direction) \n0 (Negative Direction)\n");
//         std::cin >> dir;
//         lift = 0;
//         printf("Read %c and %d\n", sel, dir);

//         if(sel == 'x')
//         {
//             motorPin = X_MOTOR_PIN;
//             motorDirPin = X_MOTOR_DIR_PIN;
//         }
//         else if (sel == 'y')
//         {
//             motorPin = Y_MOTOR_PIN;
//             motorDirPin = Y_MOTOR_DIR_PIN;
//         }
//         else if(sel == 'z')
//         {
//             motorPin = Z_MOTOR_PIN;
//         }
//         else if(sel == 'l')
//         {
//             motorPin = Y_MOTOR_PIN;
//             motorDirPin = Y_MOTOR_DIR_PIN;
//             lift = 1;
//         }
//         else if(sel == 'r')
//         {
//             //Extend Z
//             move(h, Z_MOTOR_PIN, Y_MOTOR_DIR_PIN, 0, 0);
//             // Lift on Y
//             move(h, Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, 1, 1);
//             // Retract Z
//             move(h, Z_MOTOR_PIN, Y_MOTOR_DIR_PIN, 0, 0);
//             // Move Y Full Step
//             move(h, Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, dir, 0);
//             // Move along X 
//             move(h, X_MOTOR_PIN, X_MOTOR_DIR_PIN, !dir, 0);
//             move(h, X_MOTOR_PIN, X_MOTOR_DIR_PIN, !dir, 0);
//             // Extend Z
//             move(h, Z_MOTOR_PIN, Y_MOTOR_DIR_PIN, 0, 0);
//             // Put down box
//             move(h, Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, 0, 1);
//             // Retract Z
//             move(h, Z_MOTOR_PIN, Y_MOTOR_DIR_PIN, 0, 0);
//         }
//         else if(sel == 'u')
//         {

//         }
//         if(sel != 'r' && sel != 'u')
//         {
//             // printf("motorPin: %d\nmotorDirPin: %d\n", motorPin, motorDirPin);
//             move(h, motorPin, motorDirPin, dir, lift);
//         }

//     }

//     return 0;
// }


Motor::Motor() { }

uint32_t Motor::move(uint32_t motorPin, uint32_t motorDirPin, uint32_t direction, uint32_t pulses, uint32_t motorSpeed)
{
    //Dont do if Z motor
    if(motorPin != Z_MOTOR_PIN)
    {
        lgGpioWrite(h, motorDirPin, direction);
        usleep(10);
    }
    for(uint32_t i = 0; i < pulses; i++)
    {
        lgGpioWrite(h, motorPin, 1);
        usleep(motorSpeed);
        lgGpioWrite(h, motorPin, 0);
        usleep(motorSpeed);
    }
}

uint32_t Motor::motorSetup()
{
    uint32_t returnValue = SUCCESS;
    h = lgGpiochipOpen(4); // open /dev/gpiochip0

    if (h < 0) { EXIT_FUNCTION(returnValue, ERROR_MOTOR_GPIO_CHIP_OPEN); }
    
    status = lgGpioClaimOutput(h, 0, X_MOTOR_PIN, 0);
    if(status != LG_OKAY) { EXIT_FUNCTION(returnValue, ERROR_MOTOR_GPIO_CLAIM_OUT); }
    status = lgGpioClaimOutput(h, 0, X_MOTOR_DIR_PIN, 0);
    if(status != LG_OKAY) { EXIT_FUNCTION(returnValue, ERROR_MOTOR_GPIO_CLAIM_OUT); }
    status = lgGpioClaimOutput(h, 0, Y_MOTOR_PIN, 0);
    if(status != LG_OKAY) { EXIT_FUNCTION(returnValue, ERROR_MOTOR_GPIO_CLAIM_OUT); }
    status = lgGpioClaimOutput(h, 0, Y_MOTOR_DIR_PIN, 0);
    if(status != LG_OKAY) { EXIT_FUNCTION(returnValue, ERROR_MOTOR_GPIO_CLAIM_OUT); }
    status = lgGpioClaimOutput(h, 0, Z_MOTOR_PIN, 0);
    if(status != LG_OKAY) { EXIT_FUNCTION(returnValue, ERROR_MOTOR_GPIO_CLAIM_OUT); }

    EXIT_POINT
    return returnValue;

}