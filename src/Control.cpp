/*- 'Main'
 - calibration func
*/

#ifndef CONTROL_H
#define CONTROL_H

//#include "Grid.h"
#include "errors.hpp"

class Control {
public:
    ErrorCode calibrate();
    // more control functions to be added
};

#endif // CONTROL_H
