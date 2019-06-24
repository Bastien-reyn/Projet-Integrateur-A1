#define Sender
#include <Arduino.h>
#include "Robot.h"
#include "Map.h"
#include "MotorSpeedSensor.h"
#include "RadioSender.h"
#include "RadioReciever.h"

void updateMotorSpeedSensorRight();

unsigned long time = 0;

Robot *robot;
LineFinder *lineFinder;
MotorSpeedSensor *motorSpeedSensor;
Map *theMap;
#ifdef Sender
RadioSender *sender;
#endif
#ifdef Reciever
RadioReciever *reciever;
#endif
ERobotState state;
int left = 0;
int right = 0;
unsigned long lastTurn = 0;
String message = "salut";

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
    #ifdef Sender
    sender = new RadioSender();
    #endif
    #ifdef Reciever
    reciever = new RadioReciever();
    #endif
}

// La loop de l'Arduino
void loop()
{
#ifdef DEBUG
    Serial.print("Duree Boucle :");
#endif

#ifdef Sender
    Serial.println(millis() - time);
    time = millis();
sender->send(message);

/* 
    //(message.c_str(), message.length());
    //if (state == FOLLOWING)
    //{
        state = robot->followLine(lineFinder->find());
        //}

    if (state != ERobotState::FOLLOWING && millis() - lastTurn >= 150)
    {
        state = robot->takeTurn(state);
        lastTurn = millis();
    }
    */
#endif
    #ifdef Reciever
    reciever->Recieve();
    Serial.print(".");
    #endif
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