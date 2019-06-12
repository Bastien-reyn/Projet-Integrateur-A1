#ifndef _MAP_H
#define _MAP_H

#include <Arduino.h>

class Map
{
public:
    Map();
    void getTravel(void);
    void setTravel(void);
private:
    bool creatTravel(int n, int xp, int yp, int x, int y);
};

#endif