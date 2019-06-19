#ifndef RADIORECIEVER_H
#define RADIORECIEVER_H
#include <AESLib.h>
#include <Arduino.h>
#include <VirtualWire.h>

const int PinReciever = 6;

class RadioReciever
{
    public:
    void Recieve();
    RadioReciever();
};

#endif
