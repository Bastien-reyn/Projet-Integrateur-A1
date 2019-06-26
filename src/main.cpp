#include <Arduino.h>
#include "Robot.h"
#include "Map.h"
#include "MotorSpeedSensor.h"
#include "RadioSender.h"
#include "RadioReciever.h"
#include "IRsensor.h"

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
unsigned int nSpeed;
IRsensor *irSensor;
int nombrePlaces = 0;

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
    int TaillePlace=irSensor->taillePlace();
    if (TaillePlace != 0)
    {
        nombrePlaces++;
        sender ->send(String (TaillePlace));
    }
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
#endif
#ifdef Reciever
    reciever->Recieve();
    Serial.print(".");
#endif
}

//update function for the attachInterrupt function of the MotorSpeedSensor
void updateMotorSpeedSensorRight()
{
    motorSpeedSensor->update();
}

void stop()
{
    String message = "Vitesse moyenne :";
    String message2 = "Nombre places : ";
    message += String(SpeedAvg / nSpeed);
    message2 += String(nombrePlaces);
    Serial.println("STOOOOOOOOOOOOOOOOOOOOOOOP");
    sender->send(message2);
    sender->send(message);
    while (1)
    {
        robot->motorDriverMove(0, 0);
    }
}