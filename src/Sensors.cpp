#include "Sensors.h"

uint32_t get_x_sensor_value(uint32_t &value)
{
    value = lgGpioRead(lgGpioHandle, X_CONTACT_SENSOR_PIN);
}
uint32_t get_y_sensor_value(uint32_t &value)
{
    value = lgGpioRead(lgGpioHandle, Y_CONTACT_SENSOR_PIN);
}
uint32_t get_z_sensor_value(uint32_t &value)
{
    value = lgGpioRead(lgGpioHandle, Z_CONTACT_SENSOR_PIN);
}