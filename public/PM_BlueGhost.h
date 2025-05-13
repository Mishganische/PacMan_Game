//
// Created by MIKHAIL ARZUMANOV on 2025. 04. 07..
//

#ifndef PM_BLUEGHOST_H
#define PM_BLUEGHOST_H


#include "Ghost.h"
#include "PM_PacMan.h"

class PM_PacMan; // Forward declaration

class PM_BlueGhost: public Ghost {


public:

    void ChaseMode(int TargetX, int TargetY, const std::vector<std::vector<int>>& map);
    void ScatterMode(const std::vector<std::vector<int>>& map) override;
    void MoveStep(const PM_PacMan& pacman, const std::vector<std::vector<int>> &map) override;
    using Ghost::Ghost; // constructor

    void SwitchMode(int playerX, int playerY) override;



private:
    int scatterTargetX = 18;
    int scatterTargetY = 16;
    int scatterZoneMinX = 0;
    int scatterZoneMaxX = 10;
    int scatterZoneMinY = 0;
    int scatterZoneMaxY = 6;
};



#endif //PM_BLUEGHOST_H