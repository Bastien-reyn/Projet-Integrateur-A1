#include "LineFinder.h"

// Cette fonction va initialiser les pins de l'Arduino
LineFinder::LineFinder() 
{
    Serial.begin(9600);

    pinMode(signalPinExtremLeft, INPUT);
    pinMode(signalPinLeft, INPUT);
    pinMode(signalPinRight, INPUT);
    pinMode(signalPinExtremRight, INPUT);
}

// Cette fonction va récupérer les entrées des capteurs suiveurs de ligne 
ECatchLine LineFinder::find(void) 
{
    bool boolExtremeLeft = (digitalRead(signalPinExtremLeft) == HIGH) ? true : false;
    bool boolLeft = (digitalRead(signalPinLeft) == HIGH) ? true : false;
    bool boolRight = (digitalRead(signalPinRight) == HIGH) ? true : false;
    bool boolExtremeRight = (digitalRead(signalPinExtremRight) == HIGH) ? true : false;

    if (boolExtremeLeft && !boolExtremeRight)
    {
        #ifdef DEBUG
        Serial.println("Turn left");
        #endif
        return (ECatchLine::TurnLeft);
    }
    else if (boolExtremeRight)
    {
        #ifdef DEBUG
        Serial.println("Turn right");
        #endif
        return (ECatchLine::TurnRight);
    }
    else if (boolRight && !(boolExtremeLeft || boolLeft || boolExtremeRight))
    {
        #ifdef DEBUG
        Serial.println("Little right correction");
        #endif
        return (ECatchLine::Right);
    }
    else if (boolLeft && !(boolExtremeLeft || boolRight || boolExtremeRight))
    {
        #ifdef DEBUG
        Serial.println("Little left correction");
        #endif
        return (ECatchLine::Left);
    }
    else if (!(boolExtremeLeft && boolLeft && boolRight && boolExtremeRight))
    {
        #ifdef DEBUG
        Serial.println("Reverse");
        #endif
        return (ECatchLine::Reverse);
    }
    else if (!(boolExtremeLeft || boolExtremeRight) && boolLeft && boolRight)
    {
        #ifdef DEBUG
        Serial.println("No correction");
        #endif
        return (ECatchLine::Straight);
    }
    return (Error);
}