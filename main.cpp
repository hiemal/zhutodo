#include <iostream>

#include "core.h"

int main()
{

    Manager mainManager("main");
    mainManager.loadTasksFromFile();
    mainManager.mainLoop();
    return 0;
}