#define RECIEVE
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
#ifdef RECIEVE
RadioReciever *radioreciever;
#endif
#ifdef SEND
RadioSender *radiosender;
#endif

// La fonction setup de l'Arduino
void setup()
{
  Serial.begin(9600);
  #ifdef RECIEVE
  radioreciever = new RadioReciever();
  #endif
  #ifdef SEND
  radiosender = new RadioSender();
  #endif
  Serial.print("init");
}

// La loop de l'Arduino
void loop()
{ 
  #ifdef SEND
  String test = "coucou";
  radiosender->Send(test.c_str(),test.length());
  #endif
  #ifdef RECIEVE
  radioreciever->Recieve();
  #endif
  delay(100);
  Serial.print(".");

}