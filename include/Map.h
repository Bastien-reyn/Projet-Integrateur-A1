#ifndef _MAP_H
#define _MAP_H

#include <Arduino.h>
#include "Robot.h"

#define DEBUG_MAP

class Map
{
private:
    bool createTravel(int n, int xp, int yp, int x, int y);

    bool isTurn(int x,int y);
   
    int posx[17];
    int posy[17];

    int fposx[17];
    int fposy[17];
    int nMoveTurn[17];
    int nMove;
    int nTurn;
    int nTurnMax;
    int nmax;
    // Le tableau qui va contenir la map sous forme de 0 (rien) et de 1 (route)
    bool mapI[9][11];
public: 

    int xd;
    int yd;
    int currentx;
    int currenty;
    
 
    Map();
    void getTravel(void);
    void setTravel(void);
    ERobotState nextDirection(void);
};

#endif