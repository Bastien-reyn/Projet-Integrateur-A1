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
    LEFT_AND_RIGHT_TURN,
    STOP
} ERobotState;

class Robot
{
private:
    LineFinder* lineFinder;
    ECatchLine actualLineState;
    unsigned long lastCorrectionTime;
    int lastTurn;
    int lastError;
    int error;
    int baseErrorTime;
    int baseError;
    int turning;
    int lasttimeturn;
public:
    int _correct;
    Robot();
    void correct(int correction);
    ERobotState followLine();
    ERobotState takeTurn(ERobotState state);
    void motorDriverMove(int left, int right);
    ERobotState followCenterLinePID(ECatchLine state);
    void correctPID(int);
};



#endif