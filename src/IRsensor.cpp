#include "IRsensor.h"

IRsensor::IRsensor() : sensor(SharpIR::GP2Y0A21YK0F, A1)
{
    distancePrecedente=0;
}

float IRsensor::taillePlace()
{
    double difference = 0;
    int distanceActuel = sensor.getDistance();
    /* Serial.print(distanceActuel);
    Serial.print(" ");
    Serial.println(distancePrecedente);*/
    if( distanceActuel > distancePrecedente + 8 )
    {
        difference = distanceActuel - distancePrecedente;
    }
    
    distancePrecedente = distanceActuel;
    //float oui = (float)difference*(float)(acos(AngleCapteur));
    //Serial.print((int)oui);
    return difference * cos(radians(AngleCapteur));
    //return (float)sensor.getDistance();
}