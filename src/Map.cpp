#include "Map.h"

// Le tableau qui va contenir la map sous forme de 0 (rien) et de 1 (route)

// On va créer la map à l'aide de la fonction "setTravel"
Map::Map() : mapI{
                 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                 {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
                 {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
                 {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                 {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                 {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                 {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
                 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}
{
    xd = 6;
    yd = 2;

    currentx = 2;
    currenty = 6;

    nTurn = 0;
    nMove = 0;
    nmax = 17;
    //Serial.begin(9600);
    Map::setTravel();
}
// On va récupérer la map
void Map::getTravel(void)
{
    for (int n = 0; n < nmax; n++)
    {
        Serial.print("-->> x :");
        Serial.print(fposx[n]);
        Serial.print(" y:");
        Serial.println(fposy[n]);
    }

    Serial.println(nmax);
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
    while (createTravel(0, currentx, currenty, currentx, currenty))
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
    int i = 0;
    for (int n = 1; n < nmax + 2; n++)
        if (isTurn(fposx[n], fposy[n]))
        {
            Serial.print(n);
            Serial.print("----> x:");
            Serial.print(fposx[n]);
            Serial.print(" y:");
            Serial.println(fposy[n]);
            nMoveTurn[i] = n;
            i++;
        }
}

bool Map::createTravel(int n, int xp, int yp, int x, int y)
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
                if (Map::createTravel(n + 1, x, y, x, y - 1))
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
                if (Map::createTravel(n + 1, x, y, x, y + 1))
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
                if (Map::createTravel(n + 1, x, y, x - 1, y))
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
                if (Map::createTravel(n + 1, x, y, x + 1, y))
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

ERobotState Map::nextDirection(void)
{
    nMove = nMoveTurn[nTurn];
    nTurn++;
    if (nMove >= nmax)
    {
        #ifdef DEBUG
        Serial.print("STTTTTTTTTTOOOOOOOOOOPPPPPPPPPPPPPPPP");
        #endif

        return ERobotState::STOP;
    }

    #ifdef DEBUG
    Serial.print("---->Move: ");
    Serial.print(nMove);
    Serial.print(" Nmax");
    Serial.println(nmax);
     #endif
    bool manu; //true = Left;
    if (fposx[nMove - 1] != fposx[nMove])
    {
        if (fposy[nMove + 1] < fposy[nMove])
            manu = true;
        else if (fposy[nMove + 1] > fposy[nMove])
            manu = false;
        else if (fposy[nMove - 1] == fposy[nMove])
        {
            #ifdef DEBUG
            Serial.println("follow");
            #endif
            return FOLLOWING;
        }

        if (fposx[nMove - 1] < fposx[nMove])
            manu = !manu;
    }
    else
    {
        if (fposy[nMove - 1] > fposy[nMove])
            manu = true;
        else
            manu = false;

        if (fposx[nMove + 1] < fposx[nMove])
            manu = !manu;
        if (fposx[nMove + 1] == fposx[nMove])
        {
            #ifdef DEBUG
            Serial.println("follow");
             #endif
            return FOLLOWING;
        }
    }

    if (manu)
    {
        #ifdef DEBUG
        Serial.println("left");
         #endif
        return LEFT_TURN;
    }
    #ifdef DEBUG
    Serial.println("right");
     #endif
    return RIGHT_TURN;
}

bool Map::isTurn(int x, int y)
{
    int n = 0;
    if (y > 0)
        if (mapI[x][y - 1])
            n++;

    if (y < 11)
        if (mapI[x][y + 1])
            n++;
    if (x > 0)
        if (mapI[x - 1][y])
            n++;
    if (y < 9)
        if (mapI[x + 1][y])
            n++;

    if (n > 2)
        return true;

    if (n == 2)
    {
        if (mapI[x][y - 1] && mapI[x][y + 1])
            return false;
        if (mapI[x - 1][y] && mapI[x + 1][y])
            return false;
        return true;
    }
    return false;
}