#include "RadioSender.h"

RadioSender::RadioSender()
{
//Mise en place du pin de transmission
vw_set_tx_pin(PinSender); 
//Mise en place de la vitesse de transmission en bit/s
vw_setup(2000);
}

void RadioSender::Send(const char *Message)
{
    //On crée un paquet
    //byte package[20];

    //On copie dans le paquet le message
    //strcpy(package, Message);

    //On commence l'envoi du paquet / message
    //vw_send(paquet, 20);
     vw_send((uint8_t *)Message, strlen(Message));

    //Cette fonction va bloquer le programme jusqu'a ce que l'envoi soit bien terminé 
    //vw_wait_tx();
}

