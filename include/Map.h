#ifndef _MAP_H
#define _MAP_H

#include <Arduino.h>

class Map
{
private:
    bool createTravel(int n, int xp, int yp, int x, int y);

    //destination en x
    int xd = 6;
    //destination en y
    int yd = 4;
    //deplacement max
    int nmax = 19;

    //coordonées temporaires
    int posx[30];
    int posy[30];
    
    //coordonées d'un point
    int fposx[30];
    int fposy[30];

    // Le tableau qui va contenir la map sous forme de 0 (rien) et de 1 (route)
    bool mapI[9][11];
public:
    Map();
    void getTravel(void);
    void setTravel(void);

};

#endif