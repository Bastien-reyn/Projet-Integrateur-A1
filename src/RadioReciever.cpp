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
    if (vw_get_message(buf, &buflen)) //Renvoie "true" si le message reçu est correct
    {
        int i;
        Serial.print("Got: ");
        for(i = 0; i < buflen; ++i)
        {
          Serial.print(buf[i], HEX);
          Serial.print(" ");
        }
    }
    else
    {
      // On retourne le nombre de messages reçus incomplets
      vw_get_rx_bad();
    }
    
}
