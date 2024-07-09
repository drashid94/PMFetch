#include "Sensors.h"

static uint32_t lgGpioHandle;

uint32_t sensorPinSetup(uint32_t lGpioHandle)
{
    lgGpioHandle = lGpioHandle;
    return SUCCESS;
}

uint32_t get_x_sensor_value(bool &value)
{
    value = lgGpioRead(lgGpioHandle, X_CONTACT_SENSOR_PIN);
    return SUCCESS;
}
uint32_t get_y_sensor_value(bool &value)
{
    value = lgGpioRead(lgGpioHandle, Y_CONTACT_SENSOR_PIN);
    return SUCCESS;
}
uint32_t get_z_sensor_value(bool &value)
{
    value = lgGpioRead(lgGpioHandle, Z_CONTACT_SENSOR_PIN);
    return SUCCESS;
}