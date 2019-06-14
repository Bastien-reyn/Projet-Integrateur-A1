#include "LineFinder.h"

LineFinder::LineFinder()
{
    Serial.begin(9600);

    pinMode(signalPinExtremLeft, INPUT);
    pinMode(signalPinLeft, INPUT);
    pinMode(signalPinRight, INPUT);
    pinMode(signalPinExtremRight, INPUT);
}

ECatchLine LineFinder::find(void)
{
    bool boolExtremeLeft = (digitalRead(signalPinExtremLeft) == HIGH) ? true : false;
    bool boolLeft = (digitalRead(signalPinLeft) == HIGH) ? true : false;
    bool boolRight = (digitalRead(signalPinRight) == HIGH) ? true : false;
    bool boolExtremeRight = (digitalRead(signalPinExtremRight) == HIGH) ? true : false;

    if (!(boolExtremeLeft || boolExtremeRight) && boolLeft && boolRight)
    {
        Serial.println("No correction");
        return (ECatchLine::Straight);
    }
    else if (boolRight && !(boolExtremeLeft || boolLeft || boolExtremeRight))
    {
        Serial.println("Little right correction");
        return (ECatchLine::Right);
    }
    else if (boolLeft && !(boolExtremeLeft || boolRight || boolExtremeRight))
    {
        Serial.println("Little left correction");
        return (ECatchLine::Left);
    }
    else if (boolExtremeRight)
    {
        Serial.println("Turn right");
        return (ECatchLine::TurnRight);
    }
    else if (boolExtremeLeft && !boolExtremeRight)
    {
        Serial.println("Turn left");
        return (ECatchLine::TurnLeft);
    }
    else if (!(boolExtremeLeft && boolLeft && boolRight && boolExtremeRight))
    {
        Serial.println("Reverse");
        return (ECatchLine::Reverse);
    }
    return (Error);
}