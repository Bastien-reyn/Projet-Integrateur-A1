#include "LineFinder.h"

const int signalPinExtremLeft = 2;
const int signalPinLeft = 4;
const int signalPinRight = 9; 
const int signalPinExtremRight = 6;

LineFinder::LineFinder(){ 
  
  Serial.begin(9600);

pinMode(signalPinExtremLeft, INPUT);
pinMode(signalPinLeft, INPUT);
pinMode(signalPinRight, INPUT);
pinMode(signalPinExtremRight, INPUT);

}

ECatchLine LineFinder::find(void){

    if( !( boolRead(signalPinExtremLeft) || boolRead(signalPinExtremRight) )  && boolRead(signalPinLeft)  && boolRead(signalPinRight)){
        Serial.println("No correction");   
        return (Straight);
    }
    if( boolRead(signalPinRight) && !(boolRead(signalPinExtremLeft) || boolRead(signalPinLeft)  || boolRead(signalPinExtremRight) ) ){
        Serial.println("Little right correction");   
        return (Right);
    }
    if( boolRead(signalPinLeft) && !( boolRead(signalPinExtremLeft) || boolRead(signalPinRight) || boolRead(signalPinExtremRight) ) ){
        Serial.println("Little left correction");   
        return (Left);
    }
    if( boolRead(signalPinExtremRight) ){
        Serial.println("Big right correction");   
        return (ExtremeRight);
    }
    if( boolRead(signalPinExtremLeft) && !boolRead(signalPinExtremRight) ){
        Serial.println("Big left correction");   
        return (ExtremeLeft);
    }
     if( !(  boolRead(signalPinExtremLeft)   && boolRead(signalPinLeft)  && boolRead(signalPinRight) && boolRead(signalPinExtremRight) ) ){
        Serial.println("Reverse");   
        return (Reverse);
    }
return (Error);
}

boolean LineFinder::boolRead(int signalPin){
    if (HIGH == digitalRead(signalPin))
        return true;

    return false;
}