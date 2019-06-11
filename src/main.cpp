#include <Arduino.h>
#include "Move.h"


unsigned long time;


   Move* move;

/*
  ////////////////////////////////////////////////////////////////////////////speedCapteur
  const int motorSpeedPin = 5;
  int motorSpeedEtat =0 ;

  boolean nPresence[100];
  const char nEncoche = 20;
  const float rayon = 0.068;

  float vitesse(void);
  boolean presence(void);
*/

void setup() {
  Serial.begin(9600);
  
  move = new Move();
/* 
    ////////////////////////////////////////////////////////////////////////////speedCapteur
  pinMode(motorSpeedPin, INPUT);
  for (int n = 0; n < 100; n++)
    nPresence[n] == 0;
*/
  Serial.print("init ");
}

void loop() {

  time = millis();
  //Serial.println(time);

  /*
    ////////////////////////////////////////////////////////////////////////////speedCapteur
    Serial.print( speed() );
    Serial.println(" m/s");
  */
  
  move->motorDriver();

  while ( (millis() - time) < 10);

}


/*
  ////////////////////////////////////////////////////////////////////////////speedCapteur
  float speed(void){

  for(int n=100;n>0;n--)
    nPresence[n] = nPresence[n-1];


  if(presence()){
    nPresence[0] = true;
    }
    else {
      nPresence[0] = false;
    }

  int sommePresence = 0;
  for(int n=0;n<100;n++){
  if(nPresence[n]){
    sommePresence++;
  }
  }
  Serial.print(sommePresence);

  double tourS = (double)sommePresence / (double)nEncoche;

    Serial.print("tour/s: "); Serial.println(tourS);

  return (double)2 * 3.14 * (double)rayon * tourS;
  }

  boolean presence(void){
    if (digitalRead(motorSpeedPin)== HIGH)
      return true;
    else
      return false;
  }


/*
///////////////////////////////////////////////////////////////////////////MAP
{1, 1 ,1, 1 ,1, 1 ,1, 1 ,1, 1 ,1,
 1, 0 ,1, 0 ,1, 0 ,1, 0 ,1, 0 ,1,
 1, 1 ,1, 1 ,1, 1 ,1, 0 ,1, 0 ,1,
 1, 0 ,0, 0 ,0, 0 ,0, 0 ,1, 0 ,1,
 1, 1 ,1, 1 ,1, 1 ,1, 1 ,1, 1 ,1,
 1, 0 ,0, 0 ,0, 0 ,0, 0 ,1, 0 ,1,
 1, 0 ,1, 1 ,1, 1 ,1, 1 ,1, 0 ,1,
 1, 0 ,1, 0 ,0, 0 ,0, 0 ,0, 0 ,1,
 1, 1 ,1, 1 ,1, 1 ,1, 1 ,1, 1 ,1,}
*/
