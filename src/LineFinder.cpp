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
    if (boolRead(signalPinRight) && !(boolRead(signalPinExtremLeft) || boolRead(signalPinLeft) || boolRead(signalPinExtremRight)))
    {
        Serial.println("Little right correction");
        return (ECatchLine::Right);
    }
    if (boolRead(signalPinLeft) && !(boolRead(signalPinExtremLeft) || boolRead(signalPinRight) || boolRead(signalPinExtremRight)))
    {
        Serial.println("Little left correction");
        return (ECatchLine::Left);
    }
    if (boolRead(signalPinExtremRight))
    {
        Serial.println("Big right correction");
        return (ECatchLine::ExtremeRight);
    }
    if (boolRead(signalPinExtremLeft) && !boolRead(signalPinExtremRight))
    {
        Serial.println("Big left correction");
        return (ECatchLine::ExtremeLeft);
    }
    if (!(boolRead(signalPinExtremLeft) && boolRead(signalPinLeft) && boolRead(signalPinRight) && boolRead(signalPinExtremRight)))
    {
        Serial.println("Reverse");
        return (ECatchLine::Reverse);
    }
    return (Error);
}

inline boolean LineFinder::boolRead(int signalPin)
{
    (digitalRead(signalPin) == HIGH) ? true : false;
}