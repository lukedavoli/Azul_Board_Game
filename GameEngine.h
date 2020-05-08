#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Player.h"
#include "Factory.h"
#include "FactoryZero.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

using std::ifstream;
using std::cout;
using std::cin;
using std::getline;
using std::move;

#define MAX_BAG_TILES 101
#define PROMPT "> "
#define INIT_POINTS 0
#define MAX_FACTORY_TILES 4
#define MAX_FACTORY_NUM 5
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
shared_ptr<FactoryZero> factoryZero;
shared_ptr<Factory> factories[MAX_FACTORY_NUM];

void init();
void loadFactoryZero(string strFactory);
void loadFactory(int fNum, string strFactory);

// A method that puts the chars from string into a char array.
void getCharArray(string string, char* charArray);

};
#endif // GAMEENGINE_H