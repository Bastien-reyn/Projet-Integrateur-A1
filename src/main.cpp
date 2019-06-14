#include <Arduino.h>
#include "Move.h"
#include "Map.h"
#include "MotorSpeedSensor.h"

unsigned long time = 0;

Move *move;
MotorSpeedSensor* motorSpeedSensor;
Map *theMap;

void setup()
{
  Serial.begin(9600);

  time = millis();
  theMap = new Map();
  Serial.println("");
  Serial.println(millis() - time);
  theMap->getTravel();
  delay(10000);

  move = new Move();

  Serial.print("init ");
  motorSpeedSensor = new MotorSpeedSensor();
}

void loop()
{ 
  Serial.print("Duree Boucle :");
  Serial.println( millis() - time );
  time = millis();
 
  move->motorDriver();
  
  motorSpeedSensor->update();
  Serial.println(motorSpeedSensor->getSpeed());

}