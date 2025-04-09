//
// Created by MIKHAIL ARZUMANOV on 2025. 03. 27..
//

#ifndef GHOST_H
#define GHOST_H

#include "vector"


class PM_PacMan; // Forward declaration


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


    virtual void ChasePlayer(const PM_PacMan& pacman, const std::vector<std::vector<int>>& map) =0;

    virtual void ScatterMode(const std::vector<std::vector<int>>& map) =0;


    void Update(const PM_PacMan& pacman, const std::vector<std::vector<int>>& map);


    void SwitchMode(int playerX, int playerY);

    int GetX() const{return x;}
    int GetY() const{return y;}



protected:
    int ghostSpeedFactor = 2; // ghost moves 2 times slower than the player
    int FrameCounter = 0;
    int x, y;
    int direction;
    bool IsPlayerVisible=true;; // scatter or chase mode
    int scatterTargetX, scatterTargetY; // default aim coordinates
    bool IsEaten=false;


};



#endif //GHOST_H