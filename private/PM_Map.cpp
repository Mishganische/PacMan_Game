//
// Created by MIKHAIL ARZUMANOV on 2025. 03. 20..
//
#include "../public/PM_Map.h"
#include "../public/PM_PacMan.h"
#include "../public/RedGhost.h"
#include "../public/PM_PinkGhost.h"
#include "../public/PM_BlueGhost.h"
#include "../public/PM_PowerPellet.h"
#include "iostream"
#include "stdio.h"
#include "cstdlib"
#include "unistd.h"
#include "termios.h"
#include "time.h"



void PM_Map::DisplayMap(const PM_PacMan& pacman, const PM_PinkGhost& PinkGhost, const RedGhost& RedGhost, const PM_BlueGhost& BlueGhost) const {
    ClearScreen();
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == pacman.GetX() && y == pacman.GetY()) {
                std::cout << "\033[43m \033[0m"<<"\033[43m \033[0m";// Pacman
                x++;
            }
            else if (x == RedGhost.getX() && y == RedGhost.getY()) {
                std::cout << "\033[41m \033[0m"<<"\033[41m \033[0m";
                x++;
            }
            else if (x == PinkGhost.GetX() && y == PinkGhost.GetY()) {
                std::cout << "\033[105m \033[0m"<<"\033[105m \033[0m";
                x++;
            }
            else if (x == BlueGhost.getX() && y == BlueGhost.getY()) {
                std::cout <<"\033[106m \033[0m"<<"\033[106m \033[0m";
                x++;
            }
            else if (map[y][x] == 1)
                std::cout <<"\033[44m \033[0m";
            else if (map[y][x]==0)
                 std::cout << '.';
            else if (map[y][x]==2) {
                std::cout << "["<<"]";
                x++;
            }
            else if (map[y][x] == -1 || map[y][x] == -2 || map[y][x] == -3)
                std::cout<< " ";
        }
        std::cout << '\n';
    }
}

void PM_Map::GameLoop() {
    srand(time(nullptr));
    PM_PacMan pacman( *this);// create pacman object
    pacman.IsAlive = true;

    PM_PinkGhost PinkGhost(18, 11, 0, 0);
    RedGhost RedGhost(22, 11, 0, 0);
    PM_BlueGhost BlueGhost(20, 11, 0, 0);


    ClearMap();

    while (pacman.IsAlive) {
        if (AllDotsCollected()) {
            ClearScreen();
            saveScore();
            std::cout << "YOU WIN!\n";
            usleep(5000000);
            ClearScreen();
            Menu();
            break;
        }

        if (kbhit()) {
            char ch = getchar();
            pacman.SetDirection(ch);
        }
        if (CheckGhostCollision(pacman, PinkGhost, RedGhost, BlueGhost)) {
            ClearScreen();
            Menu();
            break;
        }

        pacman.Update();
        PinkGhost.Update(pacman, map);
        RedGhost.Update(pacman, map);
        BlueGhost.Update(pacman, map);
        DisplayMap(pacman, PinkGhost, RedGhost, BlueGhost);
        usleep(100000); //delay 100 мс (Pac-Man moves each 0.1 сек)
    }
}


//menu stuff
int PM_Map::Menu() {
    while (true) {
        ClearScreen();
        std::cout<<'\t'<< "PACMAN"<<'\n';
        std::cout<<"1. New Game\n";
        std::cout<<"2. Wins\n";
        std::cout<< "3. Exit\n";

        std::cout<<'\n';
        std::cout<<"Choose Option:";
        char ChoiceOptionValue = getchar();
        switch (ChoiceOptionValue) {
            case '1':
                GameLoop();
                break;
            case '2':
                ClearScreen();
                printf("\n");
                printf("The best reuslt is: ");
                ReadScore();
                printf("\npress any key to return in menu!\n");
                getchar();
                break;
            case '3':
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
    if (pellet1) delete pellet1; pellet1 = nullptr;
    if (pellet1) delete pellet2; pellet2 = nullptr;
    if (pellet1) delete pellet3; pellet3 = nullptr;
    if (pellet1) delete pellet4; pellet4 = nullptr;

    pellet1 = new PowerPellet(2, 1);
    pellet2 = new PowerPellet(38, 1);
    pellet3 = new PowerPellet(2, 21);
    pellet4 = new PowerPellet(38, 21);


    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (map[y][x] == -1 || map[y][x]==-3) map[y][x] = 0;
        }
    }

    map[pellet1->y][pellet1->x] = 2;

    map[pellet2->y][pellet2->x] = 2;

    map[pellet3->y][pellet3->x] = 2;

    map[pellet4->y][pellet4->x] = 2;
}

bool PM_Map::AllDotsCollected() const {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (map[y][x] == 0) return false;
        }
    }
    return true;
}


bool PM_Map::CheckGhostCollision(const PM_PacMan& pacman, PM_PinkGhost& PinkGhost, RedGhost& RedGhost, PM_BlueGhost& BlueGhost) {
    if (pacman.IsPowerPellet) {
        if (pacman.GetX()==PinkGhost.GetX() && pacman.GetY()==PinkGhost.GetY()) {
            PinkGhost.ResetStart();
            return false;
        }
        if (pacman.GetX()==RedGhost.GetX() && pacman.GetY()==RedGhost.GetY()) {
            RedGhost.ResetStart();
            return false;
        }
        if (pacman.GetX()==BlueGhost.GetX() && pacman.GetY()==BlueGhost.GetY()) {
            BlueGhost.ResetStart();
            return false;
        }

    }else {
        if ((pacman.GetX()==PinkGhost.GetX() && pacman.GetY()==PinkGhost.GetY())//
        || pacman.GetX()==RedGhost.GetX() && pacman.GetY()==RedGhost.GetY() //
        || pacman.GetX()==BlueGhost.GetX() && pacman.GetY()==BlueGhost.GetY()) {
            return true;
        }
    }
    return false;

}

void PM_Map::saveScore() {
    int score=0;
    FILE *Recordfile = fopen("hall_of_fame.txt", "r+");
    if (!Recordfile) return; // if file didn't found then just quit from the function
    else {
        fscanf(Recordfile, "%d", &score); // Read the current record from file
        score+=1;
        rewind(Recordfile); // clear the file
        fprintf(Recordfile, "%d\n", score);
    }
    fclose(Recordfile);
}

void PM_Map::ReadScore() {
    FILE *Recordfile = fopen("hall_of_fame.txt", "r");
    if(!Recordfile) {
        perror("Could not open record file");
        return;
    }// if file didn't found then just quit from the function
    int number;
    while (fscanf(Recordfile, "%d", &number) == 1) {
        printf("%d\n", number);
    }

    fclose(Recordfile);
}
