#include <Arduino.h>
#include "Robot.h"
#include "Map.h"
#include "MotorSpeedSensor.h"
#include "RadioReciever.h"

unsigned long time = 0;

Robot *robot;
LineFinder* lineFinder;
MotorSpeedSensor* motorSpeedSensor;
Map *theMap;
RadioReciever *radiorecieve;

// La fonction setup de l'Arduino
void setup()
{
   Serial.begin(9600);

  radiorecieve = new RadioReciever();
  Serial.print("init");
}

// La loop de l'Arduino
void loop()
{ 

  radiorecieve->Recieve();
  delay(100);
  Serial.print("Fin");

}