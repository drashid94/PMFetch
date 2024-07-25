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
    bool sensorPushed;
} MovementInfo;

Motor::Motor() { }

static void motorRampUp(MovementInfo *movementInfo)
{
    uint32_t motorPin = movementInfo->motorPin; 
    uint32_t pulses = movementInfo->pulses;
    uint32_t motorSpeedFinal = movementInfo->motorSpeed;
    bool pollSensor = movementInfo->pollSensor;

    uint32_t segments = 20;
    uint32_t numPulsesPerSeg = pulses/segments;
    uint32_t motorSpeed = (segments+1)*motorSpeedFinal/4;

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
                    std::cout << "Contact Sensor on " << ((motorPin == 13) ? "x" : "y") << " pushed\nExiting rampUp function\n";
                    movementInfo->sensorPushed = true;
                    return;
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
        if(motorSpeed < motorSpeedFinal) motorSpeed = motorSpeedFinal;
    }
    // std::cout << "Final Motor Speed Reached during ramp up: " << motorSpeed << "ramp pulses : " << pulses << "\n";
}

static void motorFlatRampUp(MovementInfo * movementInfo)
{
    bool pollSensor = movementInfo->pollSensor;
    for(int i = 0; i < 5; i++)
    {
        if(pollSensor)
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
                std::cout << "Contact Sensor pushed\nExiting rampUp function\n";
                movementInfo->sensorPushed = true;
                return;
            }
        }
        lgGpioWrite(lgGpioHandle, motorPin, 1);
        usleep(1800);
        lgGpioWrite(lgGpioHandle, motorPin, 0);
        usleep(1800);
    }

    for(int i = 0; i < 5; i++)
    {
        if(pollSensor)
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
                std::cout << "Contact Sensor pushed\nExiting rampUp function\n";
                movementInfo->sensorPushed = true;
                return;
            }
        }
        lgGpioWrite(lgGpioHandle, motorPin, 1);
        usleep(1600);
        lgGpioWrite(lgGpioHandle, motorPin, 0);
        usleep(1600);
    }

    for(int i = 0; i < 5; i++)
    {
        if(pollSensor)
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
                std::cout << "Contact Sensor pushed\nExiting rampUp function\n";
                movementInfo->sensorPushed = true;
                return;
            }
        }
        lgGpioWrite(lgGpioHandle, motorPin, 1);
        usleep(1400);
        lgGpioWrite(lgGpioHandle, motorPin, 0);
        usleep(1400);
    }

    for(int i = 0; i < 5; i++)
    {
        if(pollSensor)
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
                std::cout << "Contact Sensor pushed\nExiting rampUp function\n";
                movementInfo->sensorPushed = true;
                return;
            }
        }
        lgGpioWrite(lgGpioHandle, motorPin, 1);
        usleep(1200);
        lgGpioWrite(lgGpioHandle, motorPin, 0);
        usleep(1200);
    }

    for(int i = 0; i < 5; i++)
    {
        if(pollSensor)
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
                std::cout << "Contact Sensor pushed\nExiting rampUp function\n";
                movementInfo->sensorPushed = true;
                return;
            }
        }
        lgGpioWrite(lgGpioHandle, motorPin, 1);
        usleep(1000);
        lgGpioWrite(lgGpioHandle, motorPin, 0);
        usleep(1000);
    }
}

static void motorRampDown(MovementInfo * movementInfo)
{
    uint32_t motorPin = movementInfo->motorPin; 
    uint32_t pulses = movementInfo->pulses;
    uint32_t motorSpeed = movementInfo->motorSpeed;
    bool pollSensor = movementInfo->pollSensor;

    uint32_t segments = 20;
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
                    std::cout << "Contact Sensor on " << ((motorPin == 13) ? "x" : "y") << " pushed\nExiting rampDown function\n";
                    movementInfo->sensorPushed = true;
                    return;
                }
                pollCounter = 0;
            }
            lgGpioWrite(lgGpioHandle, motorPin, 1);
            usleep(motorSpeed);
            lgGpioWrite(lgGpioHandle, motorPin, 0);
            usleep(motorSpeed);
            pollCounter++;
        }
        motorSpeed += motorSpeed/10;
    }
    // std::cout << "Final Motor Speed Reached during ramp down: " << motorSpeed << "ramp pulses : " << pulses << "\n";
}

static void motorFlatRampDown(MovementInfo * movementInfo)
{
    bool pollSensor = movementInfo->pollSensor;
    uint32_t motorSpeed = movementInfo.motorSpeed;
    for(int i = 0; i < 5; i++)
    {
        if(pollSensor)
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
                std::cout << "Contact Sensor pushed\nExiting rampUp function\n";
                movementInfo->sensorPushed = true;
                return;
            }
        }
        lgGpioWrite(lgGpioHandle, motorPin, 1);
        usleep(1000);
        lgGpioWrite(lgGpioHandle, motorPin, 0);
        usleep(1000);
    }

    for(int i = 0; i < 5; i++)
    {
        if(pollSensor)
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
                std::cout << "Contact Sensor pushed\nExiting rampUp function\n";
                movementInfo->sensorPushed = true;
                return;
            }
        }
        lgGpioWrite(lgGpioHandle, motorPin, 1);
        usleep(1200);
        lgGpioWrite(lgGpioHandle, motorPin, 0);
        usleep(1200);
    }

    for(int i = 0; i < 5; i++)
    {
        if(pollSensor)
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
                std::cout << "Contact Sensor pushed\nExiting rampUp function\n";
                movementInfo->sensorPushed = true;
                return;
            }
        }
        lgGpioWrite(lgGpioHandle, motorPin, 1);
        usleep(1400);
        lgGpioWrite(lgGpioHandle, motorPin, 0);
        usleep(1400);
    }

    for(int i = 0; i < 5; i++)
    {
        if(pollSensor)
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
                std::cout << "Contact Sensor pushed\nExiting rampUp function\n";
                movementInfo->sensorPushed = true;
                return;
            }
        }
        lgGpioWrite(lgGpioHandle, motorPin, 1);
        usleep(1600);
        lgGpioWrite(lgGpioHandle, motorPin, 0);
        usleep(1600);
    }

    for(int i = 0; i < 5; i++)
    {
        if(pollSensor)
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
                std::cout << "Contact Sensor pushed\nExiting rampUp function\n";
                movementInfo->sensorPushed = true;
                return;
            }
        }
        lgGpioWrite(lgGpioHandle, motorPin, 1);
        usleep(1800);
        lgGpioWrite(lgGpioHandle, motorPin, 0);
        usleep(1800);
    }
}

void *moveFuncFlat(void * moveParams)
{
    MovementInfo *movementInfo;
    movementInfo = (MovementInfo*)moveParams;
    uint32_t motorPin = movementInfo->motorPin;     
    uint32_t pulsesTotal = movementInfo->pulses;
    uint32_t motorSpeed = movementInfo->motorSpeed;
    bool pollSensor = movementInfo->pollSensor;
    uint32_t pollCounter = 0;

    uint32_t rampPulses = 25;

    motorFlatRampUp(movementInfo);

    if(movementInfo->sensorPushed) pthread_exit(NULL);

    for(uint32_t i = 0; i < pulsesTotal - 2*rampPulses; i++)
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
                // std::cout << "Contact Sensor on " << ((motorPin == 13) ? "x" : "y") << " pushed\nExiting movement function\n";
                pthread_exit(NULL);
            }
            pollCounter = 0;
        }
        lgGpioWrite(lgGpioHandle, motorPin, 1);
        usleep(motorSpeed);
        lgGpioWrite(lgGpioHandle, motorPin, 0);
        usleep(motorSpeed);
        pollCounter++;
    }
    motorFlatRampDown(movementInfo);
    pthread_exit(NULL);

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

    uint32_t rampPulses = .1 * pulsesTotal;
    movementInfo->pulses = rampPulses/2;
    motorRampUp(movementInfo);
    if(movementInfo->sensorPushed) pthread_exit(NULL);
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
                // std::cout << "Contact Sensor on " << ((motorPin == 13) ? "x" : "y") << " pushed\nExiting movement function\n";
                pthread_exit(NULL);
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
    // std::cout << "Movement function called\n";
    // std::cout << "Motor: MotorPin: " << motorPin << " Direction: " << direction << "\n";
    lgGpioWrite(h, motorDirPin, direction);
    usleep(10000);
    // std::cout << "Motor: Pulses: " << pulses << "\n";
    // std::cout << "Creating thread\n";
    MovementInfo *mInfo = new MovementInfo{motorPin, motorDirPin, direction, pulses, motorSpeed, pollSensor, false};
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
    status = lgGpioClaimOutput(h, 0, LED_GREEN_PIN, 0);
    if(status != LG_OKAY) { EXIT_FUNCTION(returnValue, ERROR_MOTOR_GPIO_CLAIM_OUT); }
    status = lgGpioClaimOutput(h, 0, LED_RED_PIN, 0);
    if(status != LG_OKAY) { EXIT_FUNCTION(returnValue, ERROR_MOTOR_GPIO_CLAIM_OUT); }
    EXIT_POINT
    return returnValue;

}