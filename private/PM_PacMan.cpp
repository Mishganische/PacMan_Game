//
// Created by MIKHAIL ARZUMANOV on 2025. 03. 20..
//

#include "../public/PM_PacMan.h"
#include "iostream"

PM_PacMan::PM_PacMan( PM_Map& gameMap)
    : map(gameMap), direction(1) { }// by default the direction is right


void PM_PacMan::Update() {
    if (!IsAlive) return;

    //check if the wall in front of pacman
    if ((direction == 0 && map.IsWall(x, y - 1)) ||
        (direction == 1 && map.IsWall(x + 2, y)) ||
        (direction == 2 && map.IsWall(x, y + 1)) ||
        (direction == 3 && map.IsWall(x - 1, y))) {
        return;
        }

    switch (direction) {
        case 0: y-=1; break;
        case 1: x+=2; break;
        case 2: y+=1; break;
        case 3: x-=2; break;
        default: return;
    }

    if (!map.IsEmpty(x,y)) {
        map.SetMapCell(x,y,-1);
    }
}

void PM_PacMan::Render() const {
    std::cout << "Pacman is at (" << x << ", " << y << ")\n";
}

void PM_PacMan::SetDirection(const char& NewDirection) {


    //check if player try to turn into the wall
    if ((NewDirection == 'w' && map.IsWall(x, y - 1)) ||
        (NewDirection == 'd' && map.IsWall(x + 2, y)) ||
        (NewDirection == 's' && map.IsWall(x, y + 1)) ||
        (NewDirection == 'a' && map.IsWall(x - 1, y))) {
        return;
        }

    switch (NewDirection) {
        case 'w': direction = 0; break;
        case 'd': direction = 1; break;
        case 's': direction = 2; break;
        case 'a': direction = 3; break;
        case 'q': map.Menu();
        default:
            return;
    }


}