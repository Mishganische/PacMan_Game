//
// Created by MIKHAIL ARZUMANOV on 2025. 03. 27..
//

#include "../public/Ghost.h"
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
    int newDirection = distrib(gen);

    // Change direction if it turns into the wall
    while (!CanMove(x + (newDirection == 1) - (newDirection == 3),
                    y + (newDirection == 2) - (newDirection == 0), map)) {
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

// chase the pacman (The closest way to Pac-Man)
void Ghost::chasePlayer(int playerX, int playerY, const std::vector<std::vector<int>> &map) {
    int bestX = x, bestY = y;
    double bestDistance = std::hypot(playerX - x, playerY - y); // Euclidean distance

    // check directions
    std::vector<std::pair<int, int>> moves = {{x, y - 1}, {x + 1, y}, {x, y + 1}, {x - 1, y}};
    for (const auto& move : moves) {
        int newX = move.first, newY = move.second;
        if (CanMove(newX, newY, map)) {
            double distance = std::hypot(playerX - newX, playerY - newY);
            if (distance < bestDistance) {
                bestDistance = distance;
                bestX = newX;
                bestY = newY;
            }
        }
    }

    x = bestX;
    y = bestY;
}


void Ghost::Update(int playerX, int playerY, const std::vector<std::vector<int>>& map) {
    if (scatterMode) {
        MoveStep(map);
    } else {
        chasePlayer(playerX, playerY, map);
    }
}

void Ghost::SwitchMode() {
    scatterMode = !scatterMode;
}