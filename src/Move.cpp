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

case ExtremeLeft:
   correct -= 40;
  break;
 case Left:
   correct += 40;
  break; 

  case Straight:
    break;

  case Right:
   correct +=10;
  break;
  case ExtremeRight:
   correct += 40;
  break;
  case Reverse:
   correct = 70;
  break;
  case Error:
    Serial.println("Exception: there is one exception in LineFinder::find() a case does not fit the conditions");
  break;
  default:
    Serial.println("Error: LineFinder::find() return is not in the enumeration ");
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