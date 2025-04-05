//
// Created by MIKHAIL ARZUMANOV on 2025. 03. 20..
//


#ifndef PM_PACMAN_H
#define PM_PACMAN_H

#include "PM_Map.h"

class PM_Map;

class PM_PacMan{
public:
    PM_PacMan(PM_Map& gameMap);


    void Update();
    void Render() const;

    void SetDirection(const char& NewDirection);

    int GetX() const{return x;}
    int GetY() const{return y;}

    void SetX(int NewX){x = NewX;}
    void SetY(int NewY){y = NewY;}

    bool IsAlive = false;

private:
    PM_Map& map;

    int direction = 1;
    int x=2;
    int y=1;

};



#endif //PM_PACMAN_H
