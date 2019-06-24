#include <Arduino.h>
#include "Robot.h"
#include "Map.h"
#include "MotorSpeedSensor.h"
#include "RadioSender.h"

void updateMotorSpeedSensorRight();
void stop();

unsigned long time = 0;

Robot *robot;
LineFinder *lineFinder;
MotorSpeedSensor *motorSpeedSensor;
Map *theMap;
RadioSender *sender;
ERobotState state;
int left = 0;
int right = 0;
unsigned long lastTurn = 0;
String message = "";
ERobotState nextDirection;

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

    motorSpeedSensor = new MotorSpeedSensor(updateMotorSpeedSensorRight);
    sender = new RadioSender();
    
    nextDirection = theMap->nextDirection();
    nextDirection = theMap->nextDirection();
    nextDirection = theMap->nextDirection();
    nextDirection = theMap->nextDirection();
    nextDirection = theMap->nextDirection();

    Serial.print("init ");
}

// La loop de l'Arduino
void loop()
{
#ifdef DEBUG
    Serial.print("Duree Boucle :");
    Serial.println(millis() - time);
    time = millis();
#endif
    //message = String(motorSpeedSensor->getSpeed());
    //sender->send(message.c_str(), message.length());
    //if (state == FOLLOWING)
    //{
        state = robot->followLine(lineFinder->find());
        //}

    if (state != ERobotState::FOLLOWING && millis() - lastTurn >= 150)
    {
        state = robot->takeTurn(nextDirection);
        lastTurn = millis();
        nextDirection = theMap->nextDirection();
        if (nextDirection == ERobotState::STOP)
        {
            stop();
        }
        
    }
    /*
    robot->followCenterLinePID(lineFinder->findCenter());
    Serial.print("test");
    sender->send(String(robot->_correct).c_str());*/
}

//update function for the attachInterrupt function of the MotorSpeedSensor
void updateMotorSpeedSensorRight()
{
    motorSpeedSensor->update();
}

/*bool verifyTurn(ERobotState state, ERobotState turn)
{
}*/


void stop()
{
    while (1)
    {
            robot->motorDriverMove(0,0);
    }

}