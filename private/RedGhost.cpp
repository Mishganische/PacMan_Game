//
// Created by MIKHAIL ARZUMANOV on 2025. 03. 27..
//

#include "../public/RedGhost.h"
#include "../public/PM_PacMan.h"
#include "queue"
#include "limits"


// chase the pacman (The closest way to Pac-Man)
void RedGhost::ChasePlayer(const PM_PacMan& pacman, const std::vector<std::vector<int>> &map) {
    int rows = map.size();
    int cols = map[0].size();
    int playerX = pacman.GetX();
    int playerY = pacman.GetY();
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

    // Restoring the path and moving the ghost
    int nextX = playerX, nextY = playerY;
    while (prev[nextY][nextX] != std::make_pair(x, y) && prev[nextY][nextX] != std::make_pair(-1, -1)) {
        std::tie(nextX, nextY) = prev[nextY][nextX];
    }

    if (CanMove(nextX, nextY, map)) {
        x = nextX;
        y = nextY;
    }
}

void RedGhost::ScatterMode(const std::vector<std::vector<int>> &map) {
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

        if (current.x == CornerX && current.y == CornerY)
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

    // Restoring the path and moving the ghost
    int nextX = CornerX, nextY = CornerY;
    while (prev[nextY][nextX] != std::make_pair(x, y) && prev[nextY][nextX] != std::make_pair(-1, -1)) {
        std::tie(nextX, nextY) = prev[nextY][nextX];
    }

    if (CanMove(nextX, nextY, map)) {
        x = nextX;
        y = nextY;
    }
}
