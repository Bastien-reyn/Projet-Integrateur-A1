#include "IRsensor.h"

IRsensor::IRsensor() : sensor(SharpIR::GP2Y0A21YK0F, irPin)
{
    distancePrecedente=0;
}

float IRsensor::taillePlace()
{
    int difference = 0;
    int distanceActuel = 0;
    if( distanceActuel > distancePrecedente + 3 )
    {
        distanceActuel = sensor.getDistance();
        difference = distanceActuel - distancePrecedente;
    }
    
    distancePrecedente = distanceActuel;
    return difference*(acos(AngleCapteur));
}