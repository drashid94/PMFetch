#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "Motor.hpp"
#include "errors.hpp"
#include "defines.hpp"
#include <iostream>
#include "Sensors.h"

static uint32_t lgGpioHandle;

typedef struct MovementInfo
{
    uint32_t motorPin; 
    uint32_t motorDirPin; 
    uint32_t direction; 
    uint32_t pulses;
    uint32_t motorSpeed;
    bool pollSensor;
} MovementInfo;

Motor::Motor() { }

static void motorRampUp(MovementInfo *movementInfo)
{
    uint32_t motorPin = movementInfo->motorPin; 
    uint32_t pulses = movementInfo->pulses;
    uint32_t motorSpeedFinal = movementInfo->motorSpeed;
    bool pollSensor = movementInfo->pollSensor;

    uint32_t segments = 10;
    uint32_t numPulsesPerSeg = pulses/segments;
    uint32_t motorSpeed = 10*motorSpeedFinal;

    uint32_t pollCounter = 0;
    for(uint32_t i = 0; i < segments; i++)
    {
        for(uint32_t i = 0; i < numPulsesPerSeg; i++)
        {
            if(pollSensor && pollCounter > 4)
            {
                bool contactVal = 0;
                if(motorPin == X_MOTOR_PIN)
                    get_x_sensor_value(contactVal);
                if(motorPin == Y_MOTOR_PIN)
                    get_y_sensor_value(contactVal);
                if(motorPin == Z_MOTOR_PIN)
                    get_z_sensor_value(contactVal);
                if(contactVal)
                {
                    std::cout << "Contact Sensor Pushed\nExiting movement function\n";
                    break;
                }
                pollCounter = 0;
            }
            lgGpioWrite(lgGpioHandle, motorPin, 1);
            usleep(motorSpeed);
            lgGpioWrite(lgGpioHandle, motorPin, 0);
            usleep(motorSpeed);
            pollCounter++;
        }
        motorSpeed -= motorSpeedFinal;
    }
    std::cout << "Final Motor Speed Reached during ramp up: " << motorSpeed << "\n";
}

void motorRampDown(MovementInfo * movementInfo)
{
    uint32_t motorPin = movementInfo->motorPin; 
    uint32_t pulses = movementInfo->pulses;
    uint32_t motorSpeed = movementInfo->motorSpeed;
    bool pollSensor = movementInfo->pollSensor;

    uint32_t segments = 10;
    uint32_t numPulsesPerSeg = pulses/segments;
    uint32_t pollCounter = 0;
    for(uint32_t i = 0; i < segments; i++)
    {
        for(uint32_t i = 0; i < numPulsesPerSeg; i++)
        {
            if(pollSensor && pollCounter > 4)
            {
                bool contactVal = 0;
                if(motorPin == X_MOTOR_PIN)
                    get_x_sensor_value(contactVal);
                if(motorPin == Y_MOTOR_PIN)
                    get_y_sensor_value(contactVal);
                if(motorPin == Z_MOTOR_PIN)
                    get_z_sensor_value(contactVal);
                if(contactVal)
                {
                    std::cout << "Contact Sensor Pushed\nExiting movement function\n";
                    break;
                }
                pollCounter = 0;
            }
            lgGpioWrite(lgGpioHandle, motorPin, 1);
            usleep(motorSpeed);
            lgGpioWrite(lgGpioHandle, motorPin, 0);
            usleep(motorSpeed);
            pollCounter++;
        }
        motorSpeed += motorSpeed;
    }
    std::cout << "Final Motor Speed Reached during ramp down: " << motorSpeed << "\n";
}

void *moveFunc(void * moveParams)
{
    MovementInfo *movementInfo;
    movementInfo = (MovementInfo*)moveParams;
    uint32_t motorPin = movementInfo->motorPin;     
    uint32_t pulsesTotal = movementInfo->pulses;
    uint32_t motorSpeed = movementInfo->motorSpeed;
    bool pollSensor = movementInfo->pollSensor;
    uint32_t pollCounter = 0;
    std::cout << "Creating " << pulsesTotal << " total pulses\n";

    uint32_t rampPulses = .2 * pulsesTotal;
    movementInfo->pulses = rampPulses/2;
    motorRampUp(movementInfo);
    for(uint32_t i = 0; i < pulsesTotal - rampPulses; i++)
    {
        if(pollSensor && pollCounter > 4)
        {
            bool contactVal = 0;
            if(motorPin == X_MOTOR_PIN)
                get_x_sensor_value(contactVal);
            if(motorPin == Y_MOTOR_PIN)
                get_y_sensor_value(contactVal);
            if(motorPin == Z_MOTOR_PIN)
                get_z_sensor_value(contactVal);
            if(contactVal)
            {
                std::cout << "Contact Sensor Pushed\nExiting movement function\n";
                break;
            }
            pollCounter = 0;
        }
        lgGpioWrite(lgGpioHandle, motorPin, 1);
        usleep(motorSpeed);
        lgGpioWrite(lgGpioHandle, motorPin, 0);
        usleep(motorSpeed);
        pollCounter++;
    }    
    motorRampDown(movementInfo);
    pthread_exit(NULL);
}

uint32_t Motor::move(uint32_t motorPin, uint32_t motorDirPin, uint32_t direction, uint32_t pulses, uint32_t motorSpeed, bool pollSensor, pthread_t *ptid)
{    
    printf("Movement function called\n");
    printf("Motor: MotorPin: %d Direction: %d\n", motorPin, direction);
    lgGpioWrite(h, motorDirPin, direction);
    usleep(10000);
    printf("Motor: Pulses: %d\n", pulses);
    std::cout << "Creating thread\n";
    MovementInfo *mInfo = new MovementInfo{motorPin, motorDirPin, direction, pulses, motorSpeed, pollSensor};
    pthread_create(ptid, NULL, &moveFunc, (void*)mInfo);

    return SUCCESS;
}

uint32_t Motor::pinSetup()
{
    uint32_t returnValue = SUCCESS;
    uint32_t status;
    std::cout << "Running Motor Setup Routine\n";
    h = lgGpiochipOpen(4); // open /dev/gpiochip0
    if (h < 0) { EXIT_FUNCTION(returnValue, ERROR_MOTOR_GPIO_CHIP_OPEN); }
    lgGpioHandle = h;
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
    status = lgGpioClaimOutput(h, 0, Z_MOTOR_DIR_PIN, 0);
    if(status != LG_OKAY) { EXIT_FUNCTION(returnValue, ERROR_MOTOR_GPIO_CLAIM_OUT); }
    status = lgGpioClaimInput(h, 0, X_CONTACT_SENSOR_PIN);
    if(status != LG_OKAY) { EXIT_FUNCTION(returnValue, ERROR_MOTOR_GPIO_CLAIM_OUT); }
    status = lgGpioClaimInput(h, 0, Y_CONTACT_SENSOR_PIN);
    if(status != LG_OKAY) { EXIT_FUNCTION(returnValue, ERROR_MOTOR_GPIO_CLAIM_OUT); }
    status = lgGpioClaimInput(h, 0, Z_CONTACT_SENSOR_PIN);
    if(status != LG_OKAY) { EXIT_FUNCTION(returnValue, ERROR_MOTOR_GPIO_CLAIM_OUT); }
    EXIT_POINT
    return returnValue;

}