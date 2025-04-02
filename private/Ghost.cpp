//
// Created by MIKHAIL ARZUMANOV on 2025. 03. 27..
//

#include "../public/Ghost.h"
#include "iostream"
#include "vector"
#include "random"
#include "queue"
#include "limits"


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
    int rows = map.size();
    int cols = map[0].size();
    std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, std::numeric_limits<int>::max()));
    std::vector<std::vector<std::pair<int, int>>> prev(rows, std::vector<std::pair<int, int>>(cols, {-1, -1}));

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push({x, y, 0});
    dist[y][x] = 0;

    std::vector<std::pair<int, int>> directions = {{0, -1}, {2, 0}, {0, 1}, {-2, 0}};

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.x == playerX && current.y == playerY)
            break;

        for (auto &[dx, dy] : directions) {
            int newX = current.x + dx;
            int newY = current.y + dy;
            if (CanMove(newX, newY, map) && dist[newY][newX] > current.dist + 1) {
                dist[newY][newX] = current.dist + 1;
                prev[newY][newX] = {current.x, current.y};
                pq.push({newX, newY, dist[newY][newX]});
            }
        }
    }

    // Восстановление пути и движение призрака
    int nextX = playerX, nextY = playerY;
    while (prev[nextY][nextX] != std::make_pair(x, y) && prev[nextY][nextX] != std::make_pair(-1, -1)) {
        std::tie(nextX, nextY) = prev[nextY][nextX];
    }

    if (CanMove(nextX, nextY, map)) {
        x = nextX;
        y = nextY;
    }
}


void Ghost::Update(int playerX, int playerY, const std::vector<std::vector<int>>& map) {
    FrameCounter++;
    if (FrameCounter >= ghostSpeedFactor) {
        SwitchMode(playerX, playerY);
        if (scatterMode) {
            MoveStep(map);
        } else {
            chasePlayer(playerX, playerY, map);
        }
        FrameCounter = 0;
    }
}

void Ghost::SwitchMode(int playerX, int playerY) {
    if (std::hypot(playerX - x, playerY - y)>=20)
    scatterMode = true;
    else {
        scatterMode = false;
    }
}