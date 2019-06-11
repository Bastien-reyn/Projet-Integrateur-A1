#ifndef _MOVE_H
#define _MOVE_H

#include <Arduino.h>
#include "Grove_I2C_Motor_Driver.h"

class Move{
    public:
  Move();
  void motorDriver(void);
  void motorDriverMove(int left, int right);
};

#endif