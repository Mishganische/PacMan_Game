//
// Created by MIKHAIL ARZUMANOV on 2025. 03. 20..
//
#include "../public/PM_Map.h"
#include "../public/PM_PacMan.h"
#include "iostream"
#include "stdio.h"
#include <unistd.h>
#include <termios.h>



void PM_Map::DisplayMap(const PM_PacMan& pacman ) {
    ClearScreen();
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == pacman.GetX() && y == pacman.GetY()) {
                std::cout << "\033[43m \033[0m"<<"\033[43m \033[0m";// Pacman
                x++;
            }
            else if (map[y][x] == 1)
                std::cout <<"\033[44m \033[0m";  // Стена
            else if (map[y][x]==0)
                 std::cout << '.';
            else if (map[y][x] == -1)
                std::cout<< " ";// Пустое место
        }
        std::cout << '\n';
    }
}

void PM_Map::GameLoop() {
    PM_PacMan pacman(2, 1, *this); // Создаём Pac-Man'а

    ClearMap();

    while (IsRunning) {
        if (kbhit()) {
            char ch = getchar();
            pacman.SetDirection(ch);
        }
        pacman.Update();
        DisplayMap(pacman);
        usleep(100000); //Задержка 100 мс (Pac-Man двигается каждые 0.1 сек)
    }
}


//menu stuff
int PM_Map::Menu() {
    while (1) {
        ClearScreen();
        std::cout<<'\t'<< "PACMAN"<<'\n';
        std::cout<<"1. New Game\n";
        std::cout<< "2. Exit";

        std::cout<<'\n';
        std::cout<<"Choose Option:";
        char ChoiceOptionValue = getchar();
        switch (ChoiceOptionValue) {
            case '1':
                IsRunning = true;
                GameLoop();
            case '2':
                IsRunning = false;
                enableBufferedInput();
                printf("Exiting...\n");
                system("exit");
            default:
                std::cout<<"Invalid choice. Try again.\n";
                usleep(1000000);
        }
    }
}


//cosmetics stuff realization
void PM_Map::ClearScreen() const{
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
