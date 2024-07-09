#ifndef MOTOR_H
#define MOTOR_H

#include <lgpio.h>
#include <stdint.h>
#include "errors.hpp"
#include "defines.hpp"

// Define motor pin constants
#define X_CONTACT_SENSOR_PIN 5
#define Y_CONTACT_SENSOR_PIN 6
#define Z_CONTACT_SENSOR_PIN 12

uint32_t get_x_sensor_value(uint32_t &value);
uint32_t get_y_sensor_value(uint32_t &value);
uint32_t get_z_sensor_value(uint32_t &value);

#endif