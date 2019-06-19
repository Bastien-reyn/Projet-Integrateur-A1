#include "RadioReciever.h"
#define DEBUG

RadioReciever::RadioReciever()
{
//Mise en place du pin de trans²mission
vw_set_rx_pin(PinReciever);
//Mise en place de la vitesse de transmission en bit/s
vw_setup(2000);
//Démarrage du récepteur
vw_rx_start();
}

void RadioReciever::Recieve()
{
    uint8_t buf[16];
    uint8_t buflen = 16;
    uint8_t key[] = {0x76, 0x61, 0x6c, 0x65, 0x73, 0x74, 0x75, 0x6e, 0x63, 0x6f, 0x6e, 0x6e, 0x61, 0x72, 0x64, 0x21}; // La clé de cryptage AES
    if (vw_get_message(buf, &buflen)) //Renvoie "true" si le message reçu est correct
    {
        int i;
        Serial.print("Recu: ");
        for(i = 0; i < buflen; i++)
        {
          //Serial.print(buf[i], HEX);  Initialement buf était de type uint8_t
          Serial.print(buf[i]);
          Serial.print(" ");
        }
          Serial.println(" ");
        aes128_dec_single(key, buf);

        #ifdef DEBUG
        Serial.print("decrypted:");
        Serial.print((char*)buf);

        #endif

    }
    else
    {
      // On retourne le nombre de messages reçus incomplets
      vw_get_rx_bad();
    }
    
}
