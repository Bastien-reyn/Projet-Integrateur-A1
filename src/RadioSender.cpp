#include "RadioSender.h"
RadioSender::RadioSender()
{
//Mise en place du pin de transmission
vw_set_tx_pin(PinSender); 
//Mise en place de la vitesse de transmission en bit/s
vw_setup(2000);
}

void RadioSender::Send(char *Message)
{
    //On crée un paquet
    //byte package[20];

    //On copie dans le paquet le message
    //strcpy(package, Message);

    //On convertit crypte le message en AES
    uint8_t key[] = {}; // La clé de cryptage AES
    aes128_enc_single(key, Message); //On appelle la fonction qui va encoder le message en fonction de la clé fournie
    #ifdef DEBUG
    Serial.print("données cryptées");
    Serial.println(data);
    #endif


    //On commence l'envoi du paquet / message
    //vw_send(paquet, 20);
     vw_send((uint8_t *)Message, strlen(Message));

    //Cette fonction va bloquer le programme jusqu'a ce que l'envoi soit bien terminé 
    //vw_wait_tx();
}

