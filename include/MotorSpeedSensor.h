#ifndef MOTOR_SPEED_SENSOR
#define MOTOR_SPEED_SENSOR

#include <Arduino.h>

#define STEP_NUMBER 20

class MotorSpeedSensor
{
private:
    boolean previousState;
    unsigned long timeAtPreviousState;
    void init();
    int* intervals;
    MotorSpeedSensor();

public:

    MotorSpeedSensor(void(*)());
    
    boolean actualState();
    void update();
    double getSpeed();
    
};

#endif