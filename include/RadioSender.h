#ifndef RADIOSENDER_H
#define RADIOSENDER_H

#include <Arduino.h>
#include <VirtualWire.h>
const int PinSender = -1;

class RadioSender
{
    RadioSender();
    void Send(const char *Message);
};

#endif
