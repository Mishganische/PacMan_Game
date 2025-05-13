//
// Created by MIKHAIL ARZUMANOV on 2025. 04. 07..
//

#include "../public/PM_PinkGhost.h"
#include "../public/RedGhost.h"
#include "../public/PM_PacMan.h"
#include "queue"
#include "limits"
#include "random"




// chase the pacman (The closest way to Pac-Man)
void PM_PinkGhost::ChaseMode(const PM_PacMan& pacman, const std::vector<std::vector<int>> &map) {
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
    if (currentMode == SCATTER) {
        if (!reachedScatterTarget) {
            // Двигаемся к scatter-цели
            if (x == scatterTargetX && y == scatterTargetY) {
                reachedScatterTarget = true;
            } else {
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

                    if (current.x == scatterTargetX && current.y == scatterTargetY)
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
                int nextX = scatterTargetX, nextY = scatterTargetY;
                while (prev[nextY][nextX] != std::make_pair(x, y) && prev[nextY][nextX] != std::make_pair(-1, -1)) {
                    std::tie(nextX, nextY) = prev[nextY][nextX];
                }

                if (CanMove(nextX, nextY, map)) {
                    x = nextX;
                    y = nextY;
                }
                return;
            }
        }


        // Генераторы случайных чисел (вынеси их в один .cpp файл, чтобы избежать ошибки duplicate symbol)
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distrib(0, 3);



        int opposite = (direction + 2) % 4;
        std::vector<int> validDirections;

        for (int d = 0; d < 4; ++d) {
            if (d == opposite) continue;

            int newX = x, newY = y;
            switch (d) {
                case 0: newY -= 1; break;
                case 1: newX += 2; break;
                case 2: newY += 1; break;
                case 3: newX -= 2; break;
            }

            if (CanMove(newX, newY, map) &&
                newX >= scatterZoneMinX && newX <= scatterZoneMaxX &&
                newY >= scatterZoneMinY && newY <= scatterZoneMaxY) {
                validDirections.push_back(d);
                }
        }

        if (!validDirections.empty()) {
            std::uniform_int_distribution<int> choiceDistrib(0, validDirections.size() - 1);
            int chosen = validDirections[choiceDistrib(gen)];

            direction = chosen;
            switch (direction) {
                case 0: y -= 1; break;
                case 1: x += 2; break;
                case 2: y += 1; break;
                case 3: x -= 2; break;
            }
        }
    }
}


void PM_PinkGhost::MoveStep(const PM_PacMan& pacman, const std::vector<std::vector<int>> &map) {
    switch (currentMode) {
        case SCATTER:
            ScatterMode(map);
        break;
        case CHASE:
            reachedScatterTarget = false;
            ChaseMode(pacman, map);
        break;
        case FRIGHTENED:
            if (FrightenedTimer>0) {
                FrightenedMode(map);
                FrightenedTimer--;
            }else {
                currentMode = SCATTER;
                ghostSpeedFactor=2;
            }
        break;
        default:
            break;
    }
}




void PM_PinkGhost::SwitchMode(int playerX, int playerY) {
    if (currentMode == FRIGHTENED) return;
    if (std::hypot(playerX - x, playerY - y)>=20)
        currentMode = SCATTER;
    else {
        currentMode = CHASE;
    }
}