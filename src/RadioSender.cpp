#include "RadioSender.h"
#define DEBUG

RadioSender::RadioSender()
{
//Mise en place du pin de transmission
vw_set_tx_pin(PinSender); 
//Mise en place de la vitesse de transmission en bit/s
vw_setup(2000);
}

void RadioSender::send( char *Message, int lenght)
{
    //On crée un paquet
    //byte package[20];

    //On copie dans le paquet le message
    //strcpy(package, Message);

    //On convertit crypte le message en AES
    uint8_t key[] = {118, 97, 108, 101, 115, 116, 117, 110, 99, 111, 110, 110, 97, 114, 100, 33}; // La clé de cryptage AES
    uint8_t* mts = (uint8_t*) malloc(16 * sizeof(uint8_t));
    for(int i = 0; i < 16; i++)
    {
        mts[i] = 0;
    }
    for(int i = 0; i < lenght; i++)
    {
        mts[i] = uint8_t(Message[i]);
        Serial.print((char)mts[i]);
    }
    aes128_enc_single(key, mts); //On appelle la fonction qui va encoder le message en fonction de la clé fournie
    #ifdef DEBUG
    Serial.println("données cryptées");
    //Serial.println(String(Message));
    #endif

    for(int i = 0; i < 16; i++)
    {
        Serial.print(mts[i], HEX);
        Serial.print(" ");

    }
    //On commence l'envoi du paquet / message
    //vw_send(paquet, 20);
    vw_send(mts, 16);

    //Cette fonction va bloquer le programme jusqu'a ce que l'envoi soit bien terminé 
    Serial.print("Envoye");
    free(mts);
}

