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
    void send(const char *Message, int lenght);
};

#endif
