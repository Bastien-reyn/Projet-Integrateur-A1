#include "MotorSpeedSensor.h"

const int motorSpeedPin = 3;

MotorSpeedSensor::MotorSpeedSensor()
{
    init();
}

MotorSpeedSensor::MotorSpeedSensor(void(*updater) (void))
{
    init();
    attachInterrupt(digitalPinToInterrupt(motorSpeedPin), updater, CHANGE);
}

void MotorSpeedSensor::init()
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
    //Decalage de tous les intervales
    for (int n = 20; n > 0; n--){
        intervals[n] = intervals[n - 1];
    }
    previousState = actualState();
    timeAtPreviousState = millis();
    
    
}

double MotorSpeedSensor::getSpeed()
{
    intervals[0] = millis() - timeAtPreviousState;
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
    if (intervals[0] > 200)
    {
        return 0.00;
    }
    else
    {
        return ((( 3.14 * 0.065) / 40.0) / sum) ;
    }
    
    

}

boolean MotorSpeedSensor::actualState(void)
{
    if (digitalRead(motorSpeedPin) == HIGH)
        return true;
    else
        return false;
}
