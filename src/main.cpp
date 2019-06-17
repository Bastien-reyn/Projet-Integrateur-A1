#include <Arduino.h>
#include "Robot.h"
#include "Map.h"
#include "MotorSpeedSensor.h"

unsigned long time = 0;

Robot *robot;
LineFinder* lineFinder;
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

  robot = new Robot();
  lineFinder = new LineFinder();


  Serial.print("init ");
  motorSpeedSensor = new MotorSpeedSensor();
}

// La loop de l'Arduino
void loop()
{ 
  Serial.print("Duree Boucle :");
  Serial.println( millis() - time );
  time = millis();
 
  robot->followLine(lineFinder->find());
  
  motorSpeedSensor->update();
  Serial.println(motorSpeedSensor->getSpeed());

}