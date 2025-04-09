//
// Created by MIKHAIL ARZUMANOV on 2025. 03. 27..
//

#include "../public/Ghost.h"
#include "../public/PM_PacMan.h"
#include "iostream"
#include "vector"
#include "random"



// define global generator of numbers
std::random_device rd;  // source of entropy
std::mt19937 gen(rd()); // Generator Mersenne Twister
std::uniform_int_distribution<int> distrib(0, 3); // interval [0,3]

Ghost::Ghost(int StartX,int StartY, int AimX, int AimY): x(StartX), y(StartY),scatterTargetX(AimX), scatterTargetY(AimY) {
    direction = distrib(gen);
}


void Ghost::MoveStep(const std::vector<std::vector<int>> &map) {
    /*srand(time(NULL));
    int newDirection = rand() % 4;
    if ((newDirection == 0 && !CanMove(x, y - 1, map)) ||
        (newDirection == 1 && !CanMove(x+2, y, map)) ||
        (newDirection == 2 && !CanMove(x, y + 1, map)) ||
        (newDirection == 3 && !CanMove(x-1, y , map))) {
        return;
        }

    direction = newDirection;

    switch(direction) {
        case 0:
            CanMove(x, y - 1, map)? y -= 1:y;
            break;// up
        case 1:
            CanMove(x+2, y, map)? x+=2:x;
            break; // right
        case 2:
            CanMove(x, y+1, map)? y+=1:y;
            break; // down
        case 3:
            CanMove(x-1, y, map)? x-=-2:x;
            break; // left
        default:return;
    }*/

    int opposite = (direction + 2) % 4; //opposite direction for current direction
    int newDirection = distrib(gen);

    // Change direction if it turns into the wall
    while (!CanMove(x + (newDirection == 1) - (newDirection == 3),
                    y + (newDirection == 2) - (newDirection == 0), map) || newDirection == opposite) {
        newDirection = distrib(gen);
                    }

    direction = newDirection;

    switch (direction) {
        case 0: if (CanMove(x, y - 1, map)) y -= 1; break;
        case 1: if (CanMove(x + 2, y, map)) x += 2; break;
        case 2: if (CanMove(x, y + 1, map)) y += 1; break;
        case 3: if (CanMove(x - 1, y, map)) x -= 2; break;
        default: return;
    }
}


void Ghost::Update(const PM_PacMan& pacman, const std::vector<std::vector<int>>& map) {
    FrameCounter++;
    if (FrameCounter >= ghostSpeedFactor) {
        SwitchMode(pacman.GetX(), pacman.GetY());
        if (IsPlayerVisible) {
            ScatterMode(map);
        } else {
            ChasePlayer(pacman, map);
        }
        FrameCounter = 0;
    }
}

void Ghost::SwitchMode(int playerX, int playerY) {
    if (std::hypot(playerX - x, playerY - y)>=15)
    IsPlayerVisible = true;
    else {
        IsPlayerVisible = false;
    }
}
