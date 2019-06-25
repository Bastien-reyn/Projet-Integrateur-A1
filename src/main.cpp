#include <Arduino.h>
#include "Robot.h"
#include "Map.h"
#include "MotorSpeedSensor.h"
#include "RadioSender.h"
#include "IRsensor.h"

/* void updateMotorSpeedSensorRight();

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
*/
IRsensor* sensor;

// La fonction setup de l'Arduino
void setup()
{
    Serial.begin(9600);

  /*   time = millis();
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
    */
    sensor = new IRsensor();
}

// La loop de l'Arduino
void loop()
{
#ifdef DEBUG
    Serial.print("Duree Boucle :");
    Serial.println(millis() - time);
    time = millis();
#endif
    /*message = String(motorSpeedSensor->getSpeed());
    sender->send(message.c_str(), message.length());
    //if (state == FOLLOWING)
    //{
        state = robot->followLine(lineFinder->find());
        //}

    if (state != ERobotState::FOLLOWING && millis() - lastTurn >= 150)
    {
        state = robot->takeTurn(state);
        lastTurn = millis();
    }*///////
    /*
    robot->followCenterLinePID(lineFinder->findCenter());
    Serial.print("test");
    sender->send(String(robot->_correct).c_str());*/
    float taille = sensor->taillePlace();
    if (taille>10)
    {
        Serial.println(String(taille) );

    }
    delay(200);

}

//update function for the attachInterrupt function of the MotorSpeedSensor
/* void updateMotorSpeedSensorRight()
{
    motorSpeedSensor->update();
}
*/