#include <Arduino.h>
#include "Robot.h"
#include "Map.h"
#include "MotorSpeedSensor.h"
#include "RadioReciever.h"
#include "RadioSender.h"

unsigned long time = 0;

Robot *robot;
LineFinder* lineFinder;
MotorSpeedSensor* motorSpeedSensor;
Map *theMap;
RadioReciever *radiorecieve;
RadioSender *radiosender;

// La fonction setup de l'Arduino
void setup()
{
   Serial.begin(9600);

  radiosender = new RadioSender();
  Serial.print("init");
}

// La loop de l'Arduino
void loop()
{ 
  String oui = "salut";
  radiosender->Send(oui.c_str(), oui.length());
  Serial.println(" Fin");
  delay(1000);
}