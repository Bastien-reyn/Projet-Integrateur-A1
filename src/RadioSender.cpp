#include <RadioSender.h>

RadioSender::RadioSender()
{
//Mise en place du pin de transmission
vw_set_tx_pin(PinSender); 
//Mise en place de la vitesse de transmission en bit/s
vw_setup(2000);
}

void RadioSender::Send(const char *Message)
{
    vw_send((uint8_t *)Message, strlen(Message));
}
