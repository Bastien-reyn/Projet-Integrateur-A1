#include <Arduino.h>
#include "Robot.h"
#include "Map.h"
#include "MotorSpeedSensor.h"

void updateMotorSpeedSensorRight();

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
  delay(1000);

  robot = new Robot();
  lineFinder = new LineFinder();


  Serial.print("init ");
  motorSpeedSensor = new MotorSpeedSensor(updateMotorSpeedSensorRight);
}

// La loop de l'Arduino
void loop()
{ 
  #ifdef DEBUG
  Serial.print("Duree Boucle :");
  Serial.println( millis() - time );
  time = millis();
 #endif
  Serial.println(motorSpeedSensor->getSpeed());
  robot->followLine(lineFinder->find());
  

}


//update function for the attachInterrupt function of the MotorSpeedSensor
void updateMotorSpeedSensorRight()
{
  motorSpeedSensor->update();
}