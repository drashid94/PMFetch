#ifndef SENSORS_H
#define SENSORS_H

#include <lgpio.h>
#include <stdint.h>
#include "errors.hpp"
#include "defines.hpp"

uint32_t sensorPinSetup(uint32_t lGpioHandle);
uint32_t get_x_sensor_value(bool &value);
uint32_t get_y_sensor_value(bool &value);
uint32_t get_z_sensor_value(bool &value);

#endif