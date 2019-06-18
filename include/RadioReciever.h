#ifndef RADIORECIEVER_H
#define RADIORECIEVER_H
#include <AESLib.h>
#include <Arduino.h>
#include <VirtualWire.h>

const int PinReciever = 3;

class RadioReciever
{
    public:
    void Recieve();
    RadioReciever();
};

#endif
