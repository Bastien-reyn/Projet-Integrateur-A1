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

  move->motorDriver();
  Serial.print("init ");
  motorSpeedSensor = new MotorSpeedSensor();
}

void loop()
{
  time = millis();
  //Serial.println(time);

  
  motorSpeedSensor->update();

  Serial.println(motorSpeedSensor->getSpeed());

}