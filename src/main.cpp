#include <Arduino.h>
#include "Move.h"
#include "MotorSpeedSensor.h"

unsigned long time = 0;

Move *move;
MotorSpeedSensor* motorSpeedSensor;

/*
  ////////////////////////////////////////////////////////////////////////////speedCapteur
  const int motorSpeedPin = 5;
  int motorSpeedEtat =0 ;

  boolean nPresence[100];
  const char nEncoche = 20;
  const float rayon = 0.068;

  float vitesse(void);
  boolean presence(void);
*/

void setup()
{
  Serial.begin(9600);

  move = new Move();
  /* 
    ////////////////////////////////////////////////////////////////////////////speedCapteur
  pinMode(motorSpeedPin, INPUT);
  for (int n = 0; n < 100; n++)
    nPresence[n] == 0;
*/
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
