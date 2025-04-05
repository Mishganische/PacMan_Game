//
// Created by MIKHAIL ARZUMANOV on 2025. 03. 27..
//

#ifndef REDGHOST_H
#define REDGHOST_H

#include "Ghost.h"

class RedGhost: public Ghost {


public:
    void chasePlayer(int playerX, int playerY, const std::vector<std::vector<int>> &map) override;
    using Ghost::Ghost; // constructor
};



#endif //REDGHOST_H
