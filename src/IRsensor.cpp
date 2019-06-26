#include "IRsensor.h"

IRsensor::IRsensor() : sensor(SharpIR::GP2Y0A21YK0F, A1)
{
    distancePrecedente=0;
}

float IRsensor::taillePlace()
{
    double difference = 0;
    int distanceActuel = sensor.getDistance();
    if( distanceActuel > distancePrecedente + 5 )
    {
        difference = distanceActuel - distancePrecedente;
    }
    
    distancePrecedente = distanceActuel;
    return difference * cos(radians(AngleCapteur));
}