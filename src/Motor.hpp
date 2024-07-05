#ifndef MOTOR_H
#define MOTOR_H

#include <lgpio.h>
#include <stdint.h>
#include "errors.hpp"

// Define motor pin constants
#define X_MOTOR_PIN 13
#define Y_MOTOR_PIN 16
#define Z_MOTOR_PIN 26

// Define motor direction pin constants
#define X_MOTOR_DIR_PIN 19
#define Y_MOTOR_DIR_PIN 20
#define Z_MOTOR_DIR_PIN 21

// TODO Define pulses_per_centimeter x and y. Placeholder values rn
#define X_PULSES_PER_CENTIMETER 2
#define Y_PULSES_PER_CENTIMETER 2

class Motor
{
    public:
        Motor();
        // Function to move a motor
        uint32_t move(uint32_t motorPin, uint32_t motorDirPin, uint32_t direction, uint32_t pulses, uint32_t motorSpeed);
        //void move(uint32_t handle, uint32_t motorPin, uint32_t motorDirPin, uint32_t direction, uint32_t lift);
        uint32_t motorSetup();

    private:
        int h; //gpioHandle for lgpio
};

#endif // MOTOR_H