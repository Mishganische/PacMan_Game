//
// Created by MIKHAIL ARZUMANOV on 2025. 04. 07..
//

#ifndef PM_PINKGHOST_H
#define PM_PINKGHOST_H


#include "Ghost.h"
#include "PM_PacMan.h"

class PM_PacMan; // Forward declaration

class PM_PinkGhost: public Ghost {


public:

    void ChaseMode(const PM_PacMan& pacman, const std::vector<std::vector<int>>& map);
    void ScatterMode(const std::vector<std::vector<int>>& map) override;
    void MoveStep(const PM_PacMan& pacman, const std::vector<std::vector<int>> &map) override;
    using Ghost::Ghost; // constructor


    void SwitchMode(int playerX, int playerY) override;


private:
    int scatterTargetX = 2;
    int scatterTargetY = 1;
    int scatterZoneMinX = 0;
    int scatterZoneMaxX = 10;
    int scatterZoneMinY = 0;
    int scatterZoneMaxY = 6;

};



#endif //PM_PINKGHOST_H