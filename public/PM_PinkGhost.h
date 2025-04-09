//
// Created by MIKHAIL ARZUMANOV on 2025. 04. 07..
//

#ifndef PM_PINKGHOST_H
#define PM_PINKGHOST_H


#include "Ghost.h"

class PM_PacMan; // Forward declaration

class PM_PinkGhost: public Ghost {


public:
    void ChasePlayer(const PM_PacMan& pacman, const std::vector<std::vector<int>>& map) override;
    void ScatterMode(const std::vector<std::vector<int>>& map) override;
    using Ghost::Ghost; // constructor


private:
    int CornerX = 2;
    int CornerY = 1;
};



#endif //PM_PINKGHOST_H
