#include <iostream>
#include "../public/PM_Map.h"
#include "ctime"

int main() {
    using namespace std;
    srand(time(nullptr));
    try {
        PM_Map gameMap;
        gameMap.disableBufferedInput();
        gameMap.Menu();
        gameMap.enableBufferedInput();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}