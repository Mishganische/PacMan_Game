#include <iostream>
#include "../public/PM_Map.h"
#include "../public/PM_PacMan.h"
#include "time.h"

int main() {
    using namespace std;


    PM_Map gameMap;
    gameMap.disableBufferedInput();
    gameMap.Menu();
    gameMap.enableBufferedInput();

    return 0;

}
