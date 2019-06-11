#include "Move.h"
#include "LineFinder.h"

#define I2C_ADDRESS 0x0f

int correct = 0;

LineFinder lineFinder;

Move::Move(){ 
  
  Serial.begin(9600);
  
  Serial.println(Motor.begin(I2C_ADDRESS));
}

void Move::motorDriver(void){

switch (lineFinder.find())
{
case ExtremeRight:
   correct += 40;
  break;
case ExtremeLeft:
   correct -= 40;
  break;
  case Right:
   correct +=10;
  break;
  case Left:
   correct += 40;
  break;
  case Reverse:
   correct += 70;
  break;
default:
    Serial.println("Erreur return LineFinder::find()");
  break;
}

if(correct >70 || correct < -70){
  correct =70;
}

  motorDriverMove( (70 + correct) , (70 - correct ));
}


void Move::motorDriverMove(int left, int right) {
  Motor.speed(MOTOR1, left);
  Motor.speed(MOTOR2, right);
}