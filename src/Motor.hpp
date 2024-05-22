#ifndef MOTOR_H
#define MOTOR_H

#include <lgpio.h>
#include <stdint>

// Define motor pin constants
#define X_MOTOR_PIN 13
#define Y_MOTOR_PIN 16
#define Z_MOTOR_PIN 26

// Define motor direction pin constants
#define X_MOTOR_DIR_PIN 19
#define Y_MOTOR_DIR_PIN 20

class Motor
{
    public:
        Motor();
        // Function to move a motor
        void move(uint32_t handle, uint32_t motorPin, uint32_t motorDirPin, uint32_t direction, uint32_t lift);
        uint32_t motorSetup();

    private:
        int h; //gpioHandle for lgpio
};

#endif // MOTOR_H