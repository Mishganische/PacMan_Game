#include <iostream>
#include "../public/PM_Map.h"
#include "ctime"

int main() {
    using namespace std;
    srand(time(nullptr));


    PM_Map gameMap;
    gameMap.disableBufferedInput();
    gameMap.Menu();
    gameMap.enableBufferedInput();

    return 0;
}