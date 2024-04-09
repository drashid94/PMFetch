#include <iostream>
#include <stdlib.h>
#include <lgpio.h>
#include <unistd.h>

uint32_t XMotorPin = 13;
uint32_t YMotorPin = 16;
uint32_t ZMotorPin = 26;
uint32_t XMotorDirPin = 19;
uint32_t YMotorDirPin = 20;

uint32_t motorSpeedX = 5000;
uint32_t motorSpeedY = 500;
uint32_t motorSpeedZ = 5000;
uint32_t pulsesPerUnitX = 400;
uint32_t pulsesPerUnitY = 1200;
uint32_t pulsesPerUnitZ = 100;

void move(uint32_t h, uint32_t motorPin, uint32_t motorDirPin, uint32_t direction)
{
    uint32_t pulseCount = 0;
    uint32_t motorSpeed = 0;

    if(motorPin == XMotorPin) 
    { 
        motorSpeed = motorSpeedX;
        pulseCount = pulsesPerUnitX;
    }
    else if (motorPin == YMotorPin)
    {
        motorSpeed = motorSpeedY;
        pulseCount = pulsesPerUnitY;
    }
    else if (motorPin == ZMotorPin)
    {
        motorSpeed = motorSpeedZ;
        pulseCount = pulsesPerUnitZ;
    }

    lgGpioWrite(h, motorDirPin, direction);
    usleep(10);

    for(uint32_t i = 0; i < pulseCount; i++)
    {
        lgGpioWrite(h, motorPin, 1);
        usleep(motorSpeed);
        lgGpioWrite(h, motorPin, 0);
        usleep(motorSpeed);
    }
}

int main()
{
    int h = lgGpiochipOpen(4); // open /dev/gpiochip0

    if (h >= 0)
    {
        printf("Opened Chip Successfully!\n");
    }
    else
    {
        printf("Failed to open GPIO chip\n");
    }

    lgChipInfo_t cInfo;

    int status = lgGpioGetChipInfo(h, &cInfo);

    if (status == LG_OKAY)
    {
        printf("lines=%d name=%s label=%s\n",
        cInfo.lines, cInfo.name, cInfo.label);
    }
    else
    {
        printf("Did not successfully\n");
    }

    lgLineInfo_t lInfo;
    for(int gpio = 0; gpio < 54; gpio++)
    {
        status = lgGpioGetLineInfo(h, gpio, &lInfo);

        if (status == LG_OKAY)
        {
            printf("lFlags=%d name=%s user=%s\n",
            lInfo.lFlags, lInfo.name, lInfo.user);
        }
    }
    
    status = lgGpioClaimOutput(h, 0, XMotorPin, 0);
    if(status != LG_OKAY) { printf("Error: status non 0\n"); }
    status = lgGpioClaimOutput(h, 0, XMotorDirPin, 0);
    if(status != LG_OKAY) { printf("Error: status non 0\n"); }
    status = lgGpioClaimOutput(h, 0, YMotorPin, 0);
    if(status != LG_OKAY) { printf("Error: status non 0\n"); }
    status = lgGpioClaimOutput(h, 0, YMotorDirPin, 0);
    if(status != LG_OKAY) { printf("Error: status non 0\n"); }
    status = lgGpioClaimOutput(h, 0, ZMotorPin, 0);
    if(status != LG_OKAY) { printf("Error: status non 0\n"); }

    char sel;
    char dir;
    uint32_t motorPin = 0;
    uint32_t motorDirPin = 0;

    printf("Select Motor\n");
    std::cin >> sel;
    std::cin >> dir;
    printf("Read %c and %c\n", sel, dir);

    if(sel == 'x')
    {
        motorPin = XMotorPin;
        motorDirPin = XMotorDirPin;
    }
    else if (sel == 'y')
    {
        motorPin = YMotorPin;
        motorDirPin = YMotorDirPin;
    }
    else if(sel == 'z')
    {
        motorPin = ZMotorPin;
        motorDirPin = ZMotorDirPin;
    }

    



    
    return 0;
}