//
// Created by MIKHAIL ARZUMANOV on 2025. 03. 20..
//
#include "../public/PM_Map.h"
#include "../public/PM_PacMan.h"
#include "../public/RedGhost.h"
#include "iostream"
#include "stdio.h"
#include "cstdlib"
#include "unistd.h"
#include "termios.h"
#include "time.h"



void PM_Map::DisplayMap(const PM_PacMan& pacman, const RedGhost& ghost ) const {
    ClearScreen();
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == pacman.GetX() && y == pacman.GetY()) {
                std::cout << "\033[43m \033[0m"<<"\033[43m \033[0m";// Pacman
                x++;
            }
            else if (x == ghost.getX() && y == ghost.getY()) {
                std::cout << "GG";
                x++;
            }
            else if (map[y][x] == 1)
                std::cout <<"\033[44m \033[0m";  // Стена
            else if (map[y][x]==0)
                 std::cout << '.';
            else if (map[y][x] == -1 || map[y][x] == -2)
                std::cout<< " ";// Пустое место
        }
        std::cout << '\n';
    }
}

void PM_Map::GameLoop() {
    srand(time(nullptr));
    PM_PacMan pacman( *this);// Создаём Pac-Man'а
    pacman.IsAlive = true;

    RedGhost G(18, 11, 0, 0);


    ClearMap();

    while (pacman.IsAlive) {
        if (kbhit()) {
            char ch = getchar();
            pacman.SetDirection(ch);
        }
        if (CheckGhostCollision(pacman, G)) {
            ClearScreen();
            Menu();
            break;
        }

        pacman.Update();
        G.Update(pacman.GetX(), pacman.GetY(), map);
        DisplayMap(pacman, G);
        usleep(100000); //Задержка 100 мс (Pac-Man двигается каждые 0.1 сек)
    }
}


//menu stuff
int PM_Map::Menu() {
    while (true) {
        ClearScreen();
        std::cout<<'\t'<< "PACMAN"<<'\n';
        std::cout<<"1. New Game\n";
        std::cout<< "2. Exit";

        std::cout<<'\n';
        std::cout<<"Choose Option:";
        char ChoiceOptionValue = getchar();
        switch (ChoiceOptionValue) {
            case '1':
                GameLoop();
            case '2':
                IsRunning = false;
                enableBufferedInput();
                printf("Exiting...\n");
                exit(0);
            default:
                std::cout<<"Invalid choice. Try again.\n";
                usleep(1000000);
        }
    }
}


//cosmetics stuff realization
void PM_Map::ClearScreen() {
    printf("\033[2J");
    printf("\033[0;0f");
}

int PM_Map::kbhit() {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

void PM_Map::disableBufferedInput() {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &term);
}

void PM_Map::enableBufferedInput() {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag |= ICANON;
    term.c_lflag |= ECHO;
    tcsetattr(0, TCSANOW, &term);
}

void PM_Map::ClearMap() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (map[y][x] == -1) map[y][x] = 0;
        }
    }
}


bool PM_Map::CheckGhostCollision(const PM_PacMan& pacman, const Ghost& Ghost) {
    if (pacman.GetX()==Ghost.GetX() && pacman.GetY()==Ghost.GetY()) {
        return true;
    }
    return false;

}
