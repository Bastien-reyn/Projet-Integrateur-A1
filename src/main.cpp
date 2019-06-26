#include <Arduino.h>
#include "Robot.h"
#include "Map.h"
#include "MotorSpeedSensor.h"
#include "RadioSender.h"
#include "RadioReciever.h"
#include "IRsensor.h"

#define TAILLE_VOITURE 35

void updateMotorSpeedSensorRight();
void stop();
unsigned long time = 0;

Robot *robot;
//LineFinder *lineFinder;
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
String message = "";
ERobotState nextDirection;
double SpeedAvg = 0;
double nSpeed = 0;
IRsensor *irSensor;
int nombrePlaces = 0;
int dernierePlace = 0;
int placeTemp = 0;

// La fonction setup de l'Arduino
void setup()
{
    Serial.begin(9600);

#ifdef Sender
    time = millis();
    theMap = new Map('A', '8');
    Serial.println("");
    Serial.println(millis() - time);
    theMap->getTravel();
    delay(1000);
    state = FOLLOWING;
    robot = new Robot();
    //lineFinder = new LineFinder();
    irSensor = new IRsensor();

    motorSpeedSensor = new MotorSpeedSensor(updateMotorSpeedSensorRight);
#ifdef Sender
    sender = new RadioSender();
#endif
#ifdef Reciever
    reciever = new RadioReciever();
#endif

    Serial.print("init ");
    nextDirection = theMap->nextDirection();
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
    Serial.println(millis() - time);
    time = millis();
#endif

#ifdef Sender
    //sender->send(message);
    SpeedAvg += motorSpeedSensor->getSpeed();
    nSpeed++;
    state = robot->followLine();
    placeTemp = irSensor->taillePlace();
    if (placeTemp > TAILLE_VOITURE && state == ERobotState::FOLLOWING )
    {
        dernierePlace = placeTemp;
        nombrePlaces++;
    }
    if (state != ERobotState::FOLLOWING && millis() - lastTurn >= 400)
    {
        if (nextDirection == ERobotState::STOP)
        {
            stop();
        }

        state = robot->takeTurn(nextDirection);
        lastTurn = millis();
        nextDirection = theMap->nextDirection();
    }
    state = ERobotState::FOLLOWING;
#endif
#ifdef Reciever
    reciever->Recieve();
#endif
}

//update function for the attachInterrupt function of the MotorSpeedSensor
void updateMotorSpeedSensorRight()
{
    motorSpeedSensor->update();
}

void stop()
{
    #ifdef Sender
    robot->motorDriverMove(0, 0);
    String message = "Vitesse moyenne :";
    String message2 = "Nombre places : ";
    String message3 = "Taille Derniere Place";
    message += String(SpeedAvg / nSpeed);
    message2 += String(nombrePlaces);
    message3 += String(dernierePlace);
    sender -> send(message);
    sender -> send(message2);
    sender -> send(message3);
    Serial.println("STOOOOOOOOOOOOOOOOOOOOOOOP");
    while (1)
    {
        robot->motorDriverMove(0, 0);
    }
    #endif
}