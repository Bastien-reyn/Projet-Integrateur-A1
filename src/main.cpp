#include <Arduino.h>
#include "Robot.h"
#include "Map.h"
#include "MotorSpeedSensor.h"
#include "RadioSender.h"

void updateMotorSpeedSensorRight();

unsigned long time = 0;

Robot *robot;
LineFinder* lineFinder;
MotorSpeedSensor* motorSpeedSensor;
Map *theMap;
RadioSender* sender;
ERobotState state;
  int left = 0;
	int right = 0;
  unsigned long lastTurn = 0;

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
  sender = new RadioSender();
}

// La loop de l'Arduino
void loop()
{ 
  #ifdef DEBUG
  Serial.print("Duree Boucle :");
  Serial.println( millis() - time );
  time = millis();
 #endif
  sender->send(String(motorSpeedSensor->getSpeed()).c_str());
  state = robot->followLine(lineFinder->find());

  if(state != ERobotState::FOLLOWING && state != LEFT_AND_RIGHT_TURN && millis() - lastTurn >= 500){
    lastTurn = millis();
    if (state == ERobotState::LEFT_TURN)
    {
      right = 70;
      left = -10;
    }
    else if (state == ERobotState::RIGHT_TURN)
    {
      left = 70;
      right = -10;
    }
    robot->motorDriverMove((left), (right));
    delay(150);
    while (lineFinder->find() != ECatchLine::Straight)
    {
      robot->motorDriverMove((left), (right));
    }
    state = FOLLOWING;
  }
}


//update function for the attachInterrupt function of the MotorSpeedSensor
void updateMotorSpeedSensorRight()
{
  motorSpeedSensor->update();
}