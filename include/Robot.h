#ifndef _ROBOT_H
#define _ROBOT_H

#include <Arduino.h>
#include "Grove_I2C_Motor_Driver.h"
#include "util.h"
#include "LineFinder.h"


typedef enum {
    FOLLOWING,
    LEFT_TURN,
    RIGHT_TURN,
    LEFT_AND_RIGHT_TURN
} ERobotState;

class Robot
{
private:
    int _correct;
    LineFinder* lineFinder;
public:
    Robot();
    ERobotState followLine(ECatchLine);
    void motorDriverMove(int left, int right);
};



#endif