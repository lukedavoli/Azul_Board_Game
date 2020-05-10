#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Player.h"
#include "Factory.h"
#include "FactoryZero.h"
#include "Tiles.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

using std::ifstream;
using std::istream;
using std::cout;
using std::cin;
using std::getline;
using std::move;

#define MAX_BAG_TILES 101
#define PROMPT "> "
#define INIT_POINTS 0
#define MAX_FACTORY_TILES 4
#define MAX_FACTORY_NUM 5
#define MAX_STORAGE_NUM 5
#define MAX_MOSAIC_ROW_NUM 5
#define COMMAND_LENGTH 4
#define COMIN_START_INDEX 5
#define SPACE 1
#define TILE_INDEX 7
#define ROW_INDEX 9

class GameEngine
{

public:
    GameEngine();
    ~GameEngine();


    void newGame(); // Sets up an new game and then enters game loop
    void loadGame(string filename); // Load in existing game from file and then enter game loop
    void enterGame(); // Enter game loop

private:

    // LinkedList* bag;
    // LinkedList* box;
    string nextTurn;

    shared_ptr<Player> player1;
    shared_ptr<Player> player2;
    shared_ptr<Player> activePlayer;
    shared_ptr<FactoryZero> factoryZero;

    bool initialised;
    Factory* factories[MAX_FACTORY_NUM];
    //shared_ptr<Factory> factories[MAX_FACTORY_NUM];

    // shared_ptr<Factory> factory1;
    // shared_ptr<Factory> factory2;
    // shared_ptr<Factory> factory3;
    // shared_ptr<Factory> factory4;
    // shared_ptr<Factory> factory5;

    void init();
    void loadPlayerNames(istream& inStream, string line);
    void loadPoints(istream& inStream, int points);
    void loadFactoryZero(istream& inStream, string line);
    void loadFactories(istream& inStream, string line);
    void loadMosaic(istream& inStream, string line, shared_ptr<Player> player);
    void loadStorageRows(istream& inStream, string line, shared_ptr<Player> player);
    void loadBrokenStorage(istream& inStream, string strStorage, shared_ptr<Player> player);
    void deleteFactories();

    // Helper method to remove whitespece from string and places it in a char array.
    void getCharArray(string string, char* charArray);

    void printValues();
    bool validChar(char c);
    void saveGame(string filename);
    string factoriesToString();
    bool validateTurn(int factory, char tile, char row);
    bool fileExists(string filename);
    void performTurn(int factory, char tile, char row);

};
#endif // GAMEENGINE_H