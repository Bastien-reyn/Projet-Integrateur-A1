#ifndef _MOVE_H
#define _MOVE_H

#include <Arduino.h>
#include "Grove_I2C_Motor_Driver.h"
#include "LineFinder.h"

class Move
{
public:
  Move();
  void motorDriver(ECatchLine);
  void motorDriverMove(int left, int right);
};

#endif