#include "RadioSender.h"

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

    //Taille message + 1 pour la clé
    int taillemsg= Donnees.length() + 1; 
    //On convertit la taille en fonction du nombre de données en héxadécimal (16 bits) à envoyer 
    taillemsg=(taillemsg%16) ? ((taillemsg/16)+1)*16 : taillemsg;
    //On convertit les données String en const char pour l'envoi et le cryptage
    const char *Message=Donnees.c_str();
    uint8_t key[] = {118, 97, 108, 101, 115, 116, 117, 110, 99, 111, 110, 110, 97, 114, 100, 33}; // La clé de cryptage AES
    uint8_t* mts = (uint8_t*) malloc((taillemsg+1) * sizeof(uint8_t)); //On crée le tableau de la taille du nombre de caractères du message +1 (pour la clé)
    //uint8_t* mtss = (uint8_t*) malloc((taillemsg+1) * sizeof(uint8_t)); //On crée le tableau de la taille du nombre de caractères du message +1 (pour la clé)
    
    //On initialise le tableau à 0
    for(int i = 0; i < taillemsg +1; i++)
    {
        mts[i] = 0;
    }
    //On écrit le message sur le tableau à envoyer
    mts[1] = 'A'; //La clé d'identification cryptée
    //Serial.print((char)mts[0]);
    //On ajoute dans les données à envoyer le message en question
    for(int i = 1; i < taillemsg; i++)     
    {
        mts[i] = uint8_t(Message[i-1]);
    }
    aes128_enc_single(key, mts + 1); //On appelle la fonction qui va encoder le message en fonction de la clé fournie
    mts[0]='A';
    #ifdef DEBUG
    // Serial.println("données cryptées");

     for(int i = 0; i < taillemsg+1; i++)
    {
        Serial.print(mts[i], HEX);
        Serial.print(" ");
    }
   Serial.println((char)mts[0]);
    #endif

    vw_send(mts, taillemsg+1);
    Serial.print("Envoye");

    free(mts);
}

