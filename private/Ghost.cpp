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
    this->startX = StartX;
    this->startY = StartY;
    direction = distrib(gen);
}


void Ghost::SetMode(GhostMode mode) {
    currentMode = mode;
}


void Ghost::FrightenedMode(const std::vector<std::vector<int>> &map) {
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

    if (--FrightenedTimer==0) {
        currentMode=SCATTER;
        ghostSpeedFactor=2;
    }

}

void Ghost::ResetStart() {
    this->x = startX;
    this->y = startY;
    this->reachedScatterTarget = false;
}

void Ghost::Update(const PM_PacMan& pacman, const std::vector<std::vector<int>>& map) {
    FrameCounter++;
    if (FrameCounter >= ghostSpeedFactor) {
        if (pacman.IsPowerPellet&& FrightenedTimer == 0) {
            currentMode = FRIGHTENED;
            FrightenedTimer = 100;
            ghostSpeedFactor = 4;
            reachedScatterTarget=false;
        }

        SwitchMode(pacman.GetX(), pacman.GetY());
        MoveStep(pacman, map);
        FrameCounter = 0;
    }
}


double Ghost::Distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
