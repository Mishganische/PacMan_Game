//
// Created by MIKHAIL ARZUMANOV on 2025. 03. 27..
//

#ifndef GHOST_H
#define GHOST_H

#include "vector"

struct Node {
    int x, y, dist;
    bool operator>(const Node &other) const { return dist > other.dist; }
};

class Ghost {


public:

    Ghost(int StartX,int StartY, int AimX, int AimY);

    //Getters
    int getX() const { return x; }
    int getY() const { return y; }

    static bool CanMove(const int newX, const int newY, const std::vector<std::vector<int>>& map) {
        return map[newY][newX] != 1;
    }

    void MoveStep(const std::vector<std::vector<int>>& map);


    void chasePlayer(int playerX, int playerY, const std::vector<std::vector<int>>& map);


    void Update(int playerX, int playerY, const std::vector<std::vector<int>>& map);


    void SwitchMode(int playerX, int playerY);



private:
    int ghostSpeedFactor = 2; // Призрак движется в 2 раза медленнее игрока
    int FrameCounter = 0;
    int x, y;
    int direction;
    bool scatterMode=true;; // scatter or chase mode
    int scatterTargetX, scatterTargetY; // default aim coordinates
    bool IsEaten=false;


};



#endif //GHOST_H
