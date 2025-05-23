//
// Created by MIKHAIL ARZUMANOV on 2025. 03. 27..
//

#ifndef REDGHOST_H
#define REDGHOST_H

#include "Ghost.h"

class PM_PacMan; // Forward declaration

class RedGhost: public Ghost {


public:
    void ChaseMode(int TargetX, int TargetY, const std::vector<std::vector<int>>& map);
    void ScatterMode(const std::vector<std::vector<int>>& map) override;
    void MoveStep(const PM_PacMan& pacman, const std::vector<std::vector<int>> &map) override;
    using Ghost::Ghost; // constructor


    void SwitchMode(int playerX, int playerY) override;



private:
    int scatterTargetX = 38;
    int scatterTargetY = 1;
    int scatterZoneMinX=30;
    int scatterZoneMinY=0;
    int scatterZoneMaxX=38;
    int scatterZoneMaxY=6;
};




#endif //REDGHOST_H