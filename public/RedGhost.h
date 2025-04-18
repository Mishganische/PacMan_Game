//
// Created by MIKHAIL ARZUMANOV on 2025. 03. 27..
//

#ifndef REDGHOST_H
#define REDGHOST_H

#include "Ghost.h"

class PM_PacMan; // Forward declaration

class RedGhost: public Ghost {


public:
    void ChasePlayer(const PM_PacMan& pacman, const std::vector<std::vector<int>>& map) override;
    void ScatterMode(const std::vector<std::vector<int>>& map) override;
    using Ghost::Ghost; // constructor



private:
    int CornerX = 38;
    int CornerY = 2;
};




#endif //REDGHOST_H