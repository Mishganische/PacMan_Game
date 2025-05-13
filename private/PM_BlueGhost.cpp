
// Created by MIKHAIL ARZUMANOV on 2025. 05. 11..
//

#include "../public/PM_BlueGhost.h"

void PM_BlueGhost::ChaseMode(int TargetX, int TargetY, const std::vector<std::vector<int>> &map) {
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

        if (current.x == TargetX && current.y == TargetY)
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
    int nextX = TargetX, nextY = TargetY;
    while (prev[nextY][nextX] != std::make_pair(x, y) && prev[nextY][nextX] != std::make_pair(-1, -1)) {
        std::tie(nextX, nextY) = prev[nextY][nextX];
    }

    if (CanMove(nextX, nextY, map)) {
        x = nextX;
        y = nextY;
    }
}

void PM_BlueGhost::ScatterMode(const std::vector<std::vector<int>> &map) {
    if (currentMode == SCATTER) {
        if (!reachedScatterTarget) {
            // Двигаемся к scatter-цели
            if (x == scatterTargetX && y == scatterTargetY) {
                reachedScatterTarget = true;
                currentMode = CHASE;
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
    }
}

void PM_BlueGhost::MoveStep(const PM_PacMan &pacman, const std::vector<std::vector<int>> &map) {
    switch (currentMode) {
        case SCATTER:
            ScatterMode(map);
        break;
        case CHASE:
            ChaseMode(pacman.GetX(), pacman.GetY(), map);
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

void PM_BlueGhost::SwitchMode(int playerX, int playerY) {
    if (currentMode == FRIGHTENED) return;
    if (reachedScatterTarget == true && Distance(playerX,playerY,x, y)>4) {
        reachedScatterTarget = false;
        currentMode = CHASE;
    }
    else if (reachedScatterTarget == false && Distance(playerX,playerY,x, y)<=4) {
        currentMode = SCATTER;
    }
}
