#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include <Arduino.h>
#include <SharpIR.h>
#include "math.h"

#define irPin A1
#define AngleCapteur 30

class IRsensor
{
private:
    SharpIR sensor;
    int distancePrecedente;
public:
//Renvoi la longueur de la place
    float taillePlace();
    IRsensor();
};

#endif