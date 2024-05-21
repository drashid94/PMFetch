#ifndef MOTOR_H
#define MOTOR_H

#include <lgpio.h>

// Define motor pin constants
#define X_MOTOR_PIN 13
#define Y_MOTOR_PIN 16
#define Z_MOTOR_PIN 26

// Define motor direction pin constants
#define X_MOTOR_DIR_PIN 19
#define Y_MOTOR_DIR_PIN 20

// Define motor speeds in microseconds
#define MOTOR_SPEED_X 1000
#define MOTOR_SPEED_Y 250
#define MOTOR_SPEED_Z 6000

// Define movement parameters
#define PULSES_PER_UNIT_X 1500
#define PULSES_PER_UNIT_Y 1200
#define PULSES_PER_LIFT_Y 3600
#define PULSES_PER_FULL_STEP_Y 17850
#define PULSES_PER_UNIT_Z 100

// Function to move a motor
void move(uint32_t handle, uint32_t motorPin, uint32_t motorDirPin, uint32_t direction, uint32_t lift);

#endif // MOTOR_H