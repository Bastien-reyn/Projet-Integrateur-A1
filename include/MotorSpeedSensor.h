#ifndef MOTOR_SPEED_SENSOR
#define MOTOR_SPEED_SENSOR

#include <Arduino.h>
#include <cppQueue.h>
#define STEP_NUMBER 20

class MotorSpeedSensor
{
private:
    boolean previousState;
    unsigned long timeAtPreviousState;

    int* intervals;

public:
    MotorSpeedSensor();
    boolean actualState();
    void update();
    double getSpeed();
    
};

#endif