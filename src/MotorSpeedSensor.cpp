#include "MotorSpeedSensor.h"

const int motorSpeedPin = 3;


MotorSpeedSensor::MotorSpeedSensor()
{
    //pinMode(motorSpeedPin, INPUT);
    previousState = actualState();
    timeAtPreviousState = millis();
    intervals = new int[20];
    for(int i=0;i<20;i++)
    {
        intervals[i] = 0;
    }
}

void MotorSpeedSensor::update()
{
    intervals[0] = millis() - timeAtPreviousState;
    if (actualState() != previousState)
    {
        //Decalage de tous les intervales
        for (int n = 20; n > 0; n--){
            intervals[n] = intervals[n - 1];
        }
        previousState = actualState();
        timeAtPreviousState = millis();
    }
    
}

double MotorSpeedSensor::getSpeed()
{
    double sum = 0.0;
    for(int i = 0; i < 20; i++)
    {
        sum += (double) intervals[i];
    }
    sum = (sum / 20.0) / 1000;
    //sum = intervals[0];
   //Serial.print("sum :");
   //Serial.println(sum);
    //return  (sum);

     return ((( 3.14 * 0.065) / 40.0) / sum) ;

}

boolean MotorSpeedSensor::actualState(void)
{
    if (digitalRead(motorSpeedPin) == HIGH)
        return true;
    else
        return false;
}
