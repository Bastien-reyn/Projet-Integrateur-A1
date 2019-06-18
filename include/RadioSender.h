#ifndef RADIOSENDER_H
#define RADIOSENDER_H
#include <AESLib.h>
#include <Arduino.h>
#include <VirtualWire.h>
const int PinSender = 7;

class RadioSender
{
public:
    RadioSender();
    void Send( char *Message);
};

#endif
