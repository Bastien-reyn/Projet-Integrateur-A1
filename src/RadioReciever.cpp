#include "RadioReciever.h"


RadioReciever::RadioReciever()
{
//Mise en place du pin de transmission
vw_set_rx_pin(PinReciever);
//Mise en place de la vitesse de transmission en bit/s
vw_setup(2000);
//Démarrage du récepteur
vw_rx_start();
}

void RadioReciever::Recieve()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    uint8_t key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; // La clé de cryptage AES
    if (vw_get_message(buf, &buflen)) //Renvoie "true" si le message reçu est correct
    {
        aes128_dec_single(key, buf);

        #ifdef DEBUG
        Serial.print("decrypted:");
        Serial.println(buf);
        #endif

        int i;
        Serial.print("Recu: ");
        for(i = 0; i < buflen; i++)
        {
          //Serial.print(buf[i], HEX);  Initialement buf était de type uint8_t
          Serial.print(buf[i]);
          Serial.print(" ");
        }
    }
    else
    {
      // On retourne le nombre de messages reçus incomplets
      vw_get_rx_bad();
    }
    
}
