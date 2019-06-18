#ifndef RADIOSENDER_H
#define RADIOSENDER_H
#include <AESLib.h>
#include <Arduino.h>
#include <VirtualWire.h>
const int PinSender = 6;

class RadioSender
{
public:
    RadioSender();
    void Send(const char *Message);
};

#endif
