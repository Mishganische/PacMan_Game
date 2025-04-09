//
// Created by MIKHAIL ARZUMANOV on 2025. 04. 07..
//

#include "../public/PM_PinkGhost.h"
#include "../public/PM_PacMan.h"
#include "queue"
#include "limits"


// chase the pacman (The closest way to Pac-Man)
void PM_PinkGhost::ChasePlayer(const PM_PacMan& pacman, const std::vector<std::vector<int>> &map) {
    int dx[] = {0, 1, 0, -1}; // directions: up, right, down, left
    int dy[] = {-1, 0, 1, 0};

    int playerX = pacman.GetX();
    int playerY = pacman.GetY();
    int playerDir = pacman.GetDirection();

    // Рассчитываем "виртуальную" точку на 4 клетки вперёд
    int rawTargetX = playerX + dx[playerDir] * 8;
    int rawTargetY = playerY + dy[playerDir] * 4;

    // Проверяем, находится ли она в пределах карты и не в стене
    int targetX = rawTargetX;
    int targetY = rawTargetY;
    bool validTarget = targetY >= 0 && targetY < map.size() &&
                       targetX >= 0 && targetX < map[0].size() &&
                       map[targetY][targetX] != 1 && map[targetY][targetX] != -2;

    // Если точка невалидна — цель это игрок
    if (!validTarget) {
        targetX = playerX;
        targetY = playerY;
    }

    // Алгоритм Дейкстры до целевой точки
    int rows = map.size();
    int cols = map[0].size();
    std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, std::numeric_limits<int>::max()));
    std::vector<std::vector<std::pair<int, int>>> prev(rows, std::vector<std::pair<int, int>>(cols, {-1, -1}));

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push({x, y, 0});
    dist[y][x] = 0;

    std::vector<std::pair<int, int>> directions = {{0, -1}, {2, 0}, {0, 1}, {-2, 0}}; // up, right, down, left

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.x == targetX && current.y == targetY)
            break;

        for (auto &[dx, dy] : directions) {
            int newX = current.x + dx;
            int newY = current.y + dy;
            if (newY >= 0 && newY < rows && newX >= 0 && newX < cols && map[newY][newX] != 1 && map[newY][newX] != -2) {
                if (dist[newY][newX] > current.dist + 1) {
                    dist[newY][newX] = current.dist + 1;
                    prev[newY][newX] = {current.x, current.y};
                    pq.push({newX, newY, dist[newY][newX]});
                }
            }
        }
    }

    // Восстановление пути
    int nextX = targetX, nextY = targetY;
    while (prev[nextY][nextX] != std::make_pair(x, y) && prev[nextY][nextX] != std::make_pair(-1, -1)) {
        std::tie(nextX, nextY) = prev[nextY][nextX];
    }

    if (map[nextY][nextX] != 1 || map[nextY][nextX] != -2) {
        x = nextX;
        y = nextY;
    }
}

void PM_PinkGhost::ScatterMode(const std::vector<std::vector<int>> &map) {
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
