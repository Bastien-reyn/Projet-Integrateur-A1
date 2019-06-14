#include <Arduino.h>
#include "Move.h"
#include "Map.h"
#include "MotorSpeedSensor.h"

unsigned long time = 0;

Move *move;
MotorSpeedSensor* motorSpeedSensor;
Map *theMap;

// La fonction setup de l'Arduino
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

// La loop de l'Arduino
void loop()
{ 
  //Serial.println( millis() - time );
  time = millis();
 
  move->motorDriver();
  
  motorSpeedSensor->update();
  Serial.println(motorSpeedSensor->getSpeed());

}