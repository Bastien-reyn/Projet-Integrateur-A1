#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include <Arduino.h>
#include <SharpIR.h>

#define irPin 1
#define AngleCapteur 30

class IRsensor
{
private:
    SharpIR sensor;
//Renvoi la longueur de la place
public:
    float taillePlace(float distance);
    IRsensor();
};

#endif