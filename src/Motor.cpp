#include <iostream>
#include <stdlib.h>
#include <lgpio.h>
#include <unistd.h>

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
    
    status = lgGpioClaimOutput(h, 0, 13, 0);
    for(;;)
    {
        status = lgGpioWrite(h, 13, 1);
        usleep(5000);
        status = lgGpioWrite(h, 13, 0);
        usleep(5000);
    }
    
    return 0;
}