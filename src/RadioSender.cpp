#include "RadioSender.h"
#define DEBUG

RadioSender::RadioSender()
{
//Mise en place du pin de transmission
vw_set_tx_pin(PinSender); 
//Mise en place de la vitesse de transmission en bit/s
vw_setup(2000);
}

void RadioSender::send(String Donnees)
{
    //On crée un paquet
    //byte package[20];

    //On copie dans le paquet le message
    //strcpy(package, Message);

    //On convertit crypte le message en AES
    int taillemsg= Donnees.length() + 1;
    taillemsg=(taillemsg%16) ? ((taillemsg/16)+1)*16 : taillemsg;
    const char *Message=Donnees.c_str();
    uint8_t key[] = {118, 97, 108, 101, 115, 116, 117, 110, 99, 111, 110, 110, 97, 114, 100, 33}; // La clé de cryptage AES
    uint8_t* mts = (uint8_t*) malloc((taillemsg) * sizeof(uint8_t)); //On crée le tableau de la taille du nombre de caractères du message +1 (pour la clé)
    
    //On initialise le tableau à 0
    for(int i = 0; i < taillemsg; i++)
    {
        mts[i] = 0;
    }
    //On écrit le message sur le tableau à envoyer
    mts[0] = 'A'; //La clé d'identification
    Serial.print((char)mts[0]);
    for(int i = 1; i < taillemsg; i++)
    {
        mts[i] = uint8_t(Message[i-1]);
        Serial.print((char)mts[i]);
    }
    aes128_enc_single(key, mts); //On appelle la fonction qui va encoder le message en fonction de la clé fournie
    #ifdef DEBUG
    Serial.println("données cryptées");
    //Serial.println(String(Message));
    #endif

    for(int i = 0; i < taillemsg; i++)
    {
        Serial.print(mts[i], HEX);
        Serial.print(" ");

    }
    //On commence l'envoi du paquet / message
    //vw_send(paquet, 20);
    
    Serial.print(taillemsg);
    vw_send(mts, taillemsg);

    //Cette fonction va bloquer le programme jusqu'a ce que l'envoi soit bien terminé 
    Serial.print("Envoye");
    free(mts);
}

