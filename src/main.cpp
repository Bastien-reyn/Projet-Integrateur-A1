#include <Arduino.h>
#include "Robot.h"
#include "Map.h"
#include "MotorSpeedSensor.h"
#include "RadioSender.h"

void updateMotorSpeedSensorRight();
void stop();

unsigned long time = 0;

Robot *robot;
//LineFinder *lineFinder;
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
    state = FOLLOWING;
    robot = new Robot();
    //lineFinder = new LineFinder();

    motorSpeedSensor = new MotorSpeedSensor(updateMotorSpeedSensorRight);
    sender = new RadioSender();

    Serial.print("init ");
    nextDirection = theMap->nextDirection();
}

// La loop de l'Arduino
void loop()
{
#ifdef DEBUG
    Serial.print("Duree Boucle :");
    Serial.println(millis() - time);
    time = millis();
#endif
    state = robot->followLine();

    if (state != ERobotState::FOLLOWING && millis() - lastTurn >= 400)
    {
        state = robot->takeTurn(nextDirection);
        lastTurn = millis();
        nextDirection = theMap->nextDirection();
        if (nextDirection == ERobotState::STOP)
        {
            stop();
        }
    }
    state = ERobotState::FOLLOWING;
}

//update function for the attachInterrupt function of the MotorSpeedSensor
void updateMotorSpeedSensorRight()
{
    motorSpeedSensor->update();
}


void stop()
{
    Serial.println("STOOOOOOOOOOOOOOOOOOOOOOOP");
    while (1)
    {
            robot->motorDriverMove(0,0);
    }

}