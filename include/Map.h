#ifndef _MAP_H
#define _MAP_H

#include <Arduino.h>

class Map
{
private:
    bool createTravel(int n, int xp, int yp, int x, int y);

    int xd = 6;
    int yd = 4;
    int nmax = 30;

    int posx[30];
    int posy[30];

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