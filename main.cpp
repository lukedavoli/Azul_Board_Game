#include "Menu.h"

int processArg(int argc, char** argv);

int main(int argc, char** argv){
    bool seedUsed = false;
    int seed = 0;

    if(argc == 2){
        seedUsed = true;
        seed = std::stoi(argv[1]);
    }

    Menu* menu = new Menu();
    menu->displayWelcome();
    menu->displayMenu(seed, seedUsed);
    return 0;
}
