#include <iostream>
#include <stdlib.h>
#include <lgpio.h>
#include <unistd.h>

uint32_t XMotorPin = 13;
uint32_t YMotorPin = 16;
uint32_t ZMotorPin = 26;
uint32_t XMotorDirPin = 19;
uint32_t YMotorDirPin = 20;

uint32_t motorSpeedX = 1000;
uint32_t motorSpeedY = 250;
uint32_t motorSpeedZ = 6000;
uint32_t pulsesPerUnitX = 1500;
uint32_t pulsesPerUnitY = 1200;
uint32_t pulsesPerLiftY = 3600;
uint32_t pulsesPerFullStepY = 17850;
uint32_t pulsesPerUnitZ = 100;

void move(uint32_t h, uint32_t motorPin, uint32_t motorDirPin, uint32_t direction, uint32_t lift)
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
        if(lift)
        {
            pulseCount = pulsesPerLiftY;
        }
        else
        {            
            pulseCount = pulsesPerFullStepY;
        }
        motorSpeed = motorSpeedY;
    }
    else if (motorPin == ZMotorPin)
    {
        motorSpeed = motorSpeedZ;
        pulseCount = pulsesPerUnitZ;
    }

    if(motorPin != ZMotorPin)
    {
        lgGpioWrite(h, motorDirPin, direction);
        usleep(10);
    }

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
        // printf("lines=%d name=%s label=%s\n",
        // cInfo.lines, cInfo.name, cInfo.label);
    }
    else
    {
        printf("Did not successfully\n");
    }

    // lgLineInfo_t lInfo;
    // for(int gpio = 0; gpio < 54; gpio++)
    // {
    //     status = lgGpioGetLineInfo(h, gpio, &lInfo);

    //     if (status == LG_OKAY)
    //     {
    //         printf("lFlags=%d name=%s user=%s\n",
    //         lInfo.lFlags, lInfo.name, lInfo.user);
    //     }
    // }
    
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
    uint32_t dir;
    uint32_t motorPin = 0;
    uint32_t motorDirPin = 0;
    uint32_t lift = 0;
    for(;;)
    {
        printf("Enter Charactor Command \nx (Move X Motor)\ny (Move Y Motor)\nz (Move Z Motor)\nr (Start Demo Routine)\n");
        std::cin >> sel;
        printf("Enter Direction Command \n1 (Positive Direction) \n0 (Negative Direction)\n");
        std::cin >> dir;
        lift = 0;
        printf("Read %c and %d\n", sel, dir);

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
        }
        else if(sel == 'l')
        {
            motorPin = YMotorPin;
            motorDirPin = YMotorDirPin;
            lift = 1;
        }
        else if(sel == 'r')
        {
            //Extend Z
            move(h, ZMotorPin, YMotorDirPin, 0, 0);
            // Lift on Y
            move(h, YMotorPin, YMotorDirPin, 1, 1);
            // Retract Z
            move(h, ZMotorPin, YMotorDirPin, 0, 0);
            // Move Y Full Step
            move(h, YMotorPin, YMotorDirPin, dir, 0);
            // Move along X 
            move(h, XMotorPin, XMotorDirPin, !dir, 0);
            move(h, XMotorPin, XMotorDirPin, !dir, 0);
            // Extend Z
            move(h, ZMotorPin, YMotorDirPin, 0, 0);
            // Put down box
            move(h, YMotorPin, YMotorDirPin, 0, 1);
            // Retract Z
            move(h, ZMotorPin, YMotorDirPin, 0, 0);
        }
        else if(sel == 'u')
        {

        }
        if(sel != 'r' && sel != 'u')
        {
            // printf("motorPin: %d\nmotorDirPin: %d\n", motorPin, motorDirPin);
            move(h, motorPin, motorDirPin, dir, lift);
        }

    }

    return 0;
}