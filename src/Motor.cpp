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