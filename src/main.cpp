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
RadioReciever *radioreciever;
RadioSender *radiosender;

// La fonction setup de l'Arduino
void setup()
{
   Serial.begin(9600);
radioreciever = new RadioReciever();
  radiosender = new RadioSender();
  Serial.print("init");
}

// La loop de l'Arduino
void loop()
{ 
  String test = "coucou";
  radiosender->Send(test.c_str(),test.length());
  //radioreciever->Recieve();
  delay(100);
  Serial.print(".");

}