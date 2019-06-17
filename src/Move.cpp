#include "Move.h"

#define I2C_ADDRESS 0x0f

int correct = 0;

LineFinder lineFinder;

Move::Move()
{

 // Serial.begin(9600);

  Serial.println(Motor.begin(I2C_ADDRESS));
}

void Move::motorDriver(ECatchLine state)
{

  switch (state)
  {

  case ECatchLine::TurnLeft:
    correct -= 40;
    break;
  case ECatchLine::Left:
    correct -= 10;
    break;
  case ECatchLine::Straight:
    break;
  case ECatchLine::Right:
    correct += 10;
    break;
  case ECatchLine::TurnRight:
    correct += 40;
    break;
  case ECatchLine::Reverse:
    //correct = 70;
    break;
  case ECatchLine::Error:
    Serial.println("Exception: there is one exception in LineFinder::find() a case does not fit the conditions");
    break;
  default:
    Serial.println("Error: LineFinder::find() return is not in the enumeration ");
    break;
  }

  if (correct > 70)
  {
    correct = 70;
  }
  else if (correct < -70)
  {
    correct = -70;
  }

  motorDriverMove((70 + correct), (70 - correct));
}

void Move::motorDriverMove(int left, int right)
{
  Motor.speed(MOTOR1, left);
  Motor.speed(MOTOR2, right);
}