//
// Created by MIKHAIL ARZUMANOV on 2025. 03. 20..
//


#ifndef PM_PACMAN_H
#define PM_PACMAN_H

#include "PM_GameObjectCore.h"
#include "PM_Map.h"

class PM_Map;

class PM_PacMan: public PM_GameObjectCore {
public:
    PM_PacMan(int startX, int startY, PM_Map& gameMap);

    int Update() override;
    void Render() const override;

    void SetDirection(const char& NewDirection);

private:
    PM_Map& map;
    int direction = 1;

};



#endif //PM_PACMAN_H
