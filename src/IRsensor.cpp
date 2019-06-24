#include "IRsensor.h"

IRsensor::IRsensor() : sensor(SharpIR::GP2Y0A21YK0F, irPin)
{
    distancePrecedente=0;
}

float IRsensor::taillePlace()
{
    int difference = 0;
    int distanceActuel = sensor.getDistance();
    Serial.println((int)distanceActuel + " " + (int)distancePrecedente);
    if( distanceActuel > distancePrecedente + 3 )
    {
        difference = distanceActuel - distancePrecedente;
    }
    
    distancePrecedente = distanceActuel;
    float oui = (float)difference*(float)(acos(AngleCapteur));
    Serial.print((int)oui);
    return (float)difference*(float)(acos(AngleCapteur));
    //return (float)sensor.getDistance();
}