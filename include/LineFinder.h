#ifndef _LINEFINDER_H
#define _LINEFINDER_H

#include <Arduino.h>
#include "util.h"

#define signalPinExtremLeft 2
#define signalPinLeft 4
#define signalPinRight 8
#define signalPinExtremRight 6

typedef enum
{
    TurnLeft = -2,
    Left = -1,
    Straight = 0,
    Right = 1,
    TurnRight = 2,
    Reverse = 5,
    LeftOrRight = 69,
    Error = 42
} ECatchLine;

class LineFinder
{
public:
    LineFinder();
    ECatchLine find(void);
    ECatchLine findCenter(void);
private:
    ECatchLine actualState;
};

#endif