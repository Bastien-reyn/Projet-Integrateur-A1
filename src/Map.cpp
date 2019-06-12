#include "Map.h"

int xd = 6;
int yd = 4;
int nmax = 30;

int posx[30];
int posy[30];

int fposx[30];
int fposy[30];

bool mapI[9][11] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

Map::Map()
{
    Serial.begin(9600);
    Map::setTravel();
}
void Map::getTravel(void)
{
    for(int n = 0; n < nmax + 2; n++)
    {
        Serial.print("-->> x :");
        Serial.print(fposx[n]);
        Serial.print(" y:");
        Serial.println(fposy[n]);
    }
}
void Map::setTravel(void)
{
    Serial.println("");
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 11; y++)
            Serial.print(((mapI[x][y]) ? "1 " : "0 "));
            Serial.println("");
    }
    while (Map::creatTravel(0, 2, 2, 2, 2))
    {
        for (int n = 0; n < nmax + 1; n++)
        {
            fposx[n] = 0;
            fposx[n] = 0;

            fposx[n] = posx[n];
            fposy[n] = posy[n];

            posx[n] = 0;
            posy[n] = 0;
        }
        nmax--;
    }
}
bool Map::creatTravel(int n, int xp, int yp, int x, int y)
{
    if (x == xd && y == yd && n < nmax)
    {
        nmax = n;
        posx[n] = x;
        //Serial.print("x :");
        posy[n] = y;
       // Serial.print("y :");
       // Serial.println(y);
        return true;
    }

    if (n == nmax)
        return false;

    if (y > 0)
    {
        if (yp != y - 1)
        {
            if (mapI[x][y - 1])
            {
                if (Map::creatTravel(n + 1, x, y, x, y - 1))
                {
                    posx[n] = x;
                   // Serial.print("x :");
                   // Serial.print(x);
                    posy[n] = y;
                   // Serial.print("y :");
                   // Serial.println(y);
                    return true;
                }
            }
        }
    }
    if (y < 10)
    {
        if (yp != y + 1)
        {
            if (mapI[x][y + 1])
            {
                if (Map::creatTravel(n + 1, x, y, x, y + 1))
                {
                    posx[n] = x;
                    // Serial.print("x :");
                    // Serial.print(x);
                    posy[n] = y;
                    // Serial.print("y :");
                    // Serial.println(y);
                    return true;
                }
            }
        }
    }
    if (x > 0)
    {
        if (xp != x - 1)
        {
            if (mapI[x - 1][y])
            {
                if (Map::creatTravel(n + 1, x, y, x - 1, y))
                {
                    posx[n] = x;
                    // Serial.print("x :");
                    // Serial.print(x);
                    posy[n] = y;
                    // Serial.print("y :");
                    // Serial.println(y);
                    return true;
                }
            }
        }
    }
    if (x < 8)
    {
        if (xp != x + 1)
        {
            if (mapI[x + 1][y])
            {
                if (Map::creatTravel(n + 1, x, y, x + 1, y))
                {
                    posx[n] = x;
                    // Serial.print("x :");
                    // Serial.print(x);
                    posy[n] = y;
                    // Serial.print("y :");
                    // Serial.println(y);
                    return true;
                }
            }
        }
    }
    return false;
}