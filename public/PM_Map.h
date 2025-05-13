

#ifndef PM_MAP_H
#define PM_MAP_H
#include "PM_PinkGhost.h"
#include "iostream"
#include "PM_PowerPellet.h"
#include "vector"

#define HEIGHT 23
#define WIDTH 42

class PM_PacMan;
class Ghost; // Forward declaration
class RedGhost;
class PM_PinkGhost;
class PM_BlueGhost;

class PM_Map {
public:

    void DisplayMap(const PM_PacMan& pacman, const PM_PinkGhost& PinkGhost, const RedGhost& RedGhost, const PM_BlueGhost& BlueGhost) const;
    void GameLoop();



    bool IsWall( const int x, const int y) const {
        return map[y][x] == 1;
    }

    bool IsEmpty( const int x, const int y ) const {
        return map[y][x] == -1;
    }

    bool IsPowerPellet( const int x, const int y ) const { return map[y][x] == 2; }


    //start game stuff
    int Menu();
    void ClearMap();


    //end game stuff
    bool AllDotsCollected() const;

    static bool CheckGhostCollision(const PM_PacMan& pacman, PM_PinkGhost& PinkGhost, RedGhost& RedGhost, PM_BlueGhost& BlueGhost);


    //file handling stuff
    void saveScore();

    void ReadScore();


    //cosmetics
    static void disableBufferedInput();

    static void enableBufferedInput();


    void SetMapCell( const int cX, const int cY, const int value) { map[cY][cX] = value; map[cY][cX+1] = -1;}

    ~PM_Map() {
        delete pellet1;
        delete pellet2;
        delete pellet3;
        delete pellet4;
    };
private:

    //cosmetics
    static int kbhit();// the function which check the input (analog _kbhit())
    static void ClearScreen();

    PowerPellet* pellet1=nullptr;
    PowerPellet* pellet2 = nullptr;
    PowerPellet* pellet3= nullptr;
    PowerPellet* pellet4=nullptr;


    bool IsRunning = false;


    //map stuff
    std::vector<std::vector<int>> map = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1},
        {1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1},
        {-2,-2,-2,-2,-2,-2,-2,-2,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,-2,-2,-2,-2,-2,-2,-2,-2},
        {1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1},
        {-2,-2,-2,-2,-2,-2,-2,-2,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,-2,-2,-2,-2,-2,-2,-2,-2},
        {-2,-2,-2,-2,-2,-2,-2,-2,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,-2,-2,-2,-2,-2,-2,-2,-2},
        {1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1},
        {1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1},
        {1,1,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };

};


#endif //PM_MAP_H