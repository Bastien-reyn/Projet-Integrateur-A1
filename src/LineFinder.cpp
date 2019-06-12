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

    if (!(boolRead(signalPinExtremLeft) || boolRead(signalPinExtremRight)) && boolRead(signalPinLeft) && boolRead(signalPinRight))
    {
        Serial.println("No correction");
        return (ECatchLine::Straight);
    }
    else if (boolRead(signalPinRight) && !(boolRead(signalPinExtremLeft) || boolRead(signalPinLeft) || boolRead(signalPinExtremRight)))
    {
        Serial.println("Little right correction");
        return (ECatchLine::Right);
    }
    else if (boolRead(signalPinLeft) && !(boolRead(signalPinExtremLeft) || boolRead(signalPinRight) || boolRead(signalPinExtremRight)))
    {
        Serial.println("Little left correction");
        return (ECatchLine::Left);
    }
    else if (boolRead(signalPinExtremRight))
    {
        //Serial.println("Big right correction");
        return (ECatchLine::ExtremeRight);
    }
    else if (boolRead(signalPinExtremLeft) && !boolRead(signalPinExtremRight))
    {
        Serial.println("Big left correction");
        return (ECatchLine::ExtremeLeft);
    }
    else if (!(boolRead(signalPinExtremLeft) && boolRead(signalPinLeft) && boolRead(signalPinRight) && boolRead(signalPinExtremRight)))
    {
        Serial.println("Reverse");
        return (ECatchLine::Reverse);
    }
    return (Error);
}

inline boolean LineFinder::boolRead(int signalPin)
{
    return (digitalRead(signalPin) == HIGH) ? true : false;
}