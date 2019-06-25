#ifndef RADIOSENDER_H
#define RADIOSENDER_H
#include <AESLib.h>
#include <Arduino.h>
#include <VirtualWire.h>
#include <util.h>
const int PinSender = 7;

class RadioSender
{
public:
    RadioSender();
    void send(String Donnees);
};

#endif
