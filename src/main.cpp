#include <Arduino.h>
#include "Move.h"
#include "MotorSpeedSensor.h"

unsigned long time = 0;

Move *move;
MotorSpeedSensor* motorSpeedSensor;

void setup()
{
  Serial.begin(9600);

  move = new Move();

 
  Serial.print("init ");
  motorSpeedSensor = new MotorSpeedSensor();
}

void loop()
{ 
  Serial.println( millis() - time );
  time = millis();
 
 move->motorDriver();
  motorSpeedSensor->update();
motorSpeedSensor->getSpeed();
  //Serial.println();

}