#include "Player.h"
#include "Factory.h"
#include <iostream>
#include <fstream>

using std::ifstream;
using std::cout;
using std::cin;
using std::getline;

#define MAX_BAG_TILES 101
#define PROMPT "> "
#define INIT_POINTS 0

class GameEngine
{

public:
    GameEngine();
    ~GameEngine();
    
 void newGame();
 void loadGame(string filename);

private:

// LinkedList* bag;
// char boxlid[MAX_TILES];
string nextTurn;

shared_ptr<Player> player1;
shared_ptr<Player> player2;
shared_ptr<FactoryZero> factory0;
shared_ptr<Factory> factory1;
shared_ptr<Factory> factory2;
shared_ptr<Factory> factory3;
shared_ptr<Factory> factory4;
shared_ptr<Factory> factory5;

// Variables to help store tiles within ADTs
// string f1;
// string f2;
// string f3;
// string f4;
// string f5;

void init();

};
