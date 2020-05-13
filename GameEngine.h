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
#include <array>

using std::ifstream;
using std::istream;
using std::cout;
using std::cin;
using std::getline;
using std::move;

#define MAX_BAG_TILES 101
#define PROMPT "> "
#define INIT_POINTS 0
#define NUM_OF_PLAYERS 2
#define MAX_FACTORY_NUM 5
#define MAX_STORAGE_NUM 5
#define MAX_MOSAIC_ROW_NUM 5

#define COMMAND_LENGTH 4
#define COMIN_START_INDEX 5
#define TILE_INDEX 7
#define ROW_INDEX 9
#define TOTAL_TILES 100
#define LAST_B_TILE 19
#define LAST_L_TILE 39
#define LAST_U_TILE 59
#define LAST_R_TILE 79
#define LAST_Y_TILE 99

class GameEngine
{

public:
    GameEngine();
    ~GameEngine();


    void newGame(int randomseed, bool seedUsed); // Sets up an new game and then enters game loop
    void loadGame(string filename); // Load in existing game from file and then enter game loop
    void enterGame(); // Enter game loop

private:
    int seed;

    shared_ptr<LinkedList> tileBag;
    std::array<char, TOTAL_TILES> boxLid;

    string nextTurn;

    shared_ptr<Player> player1;
    shared_ptr<Player> player2;
    shared_ptr<Player> activePlayer;
    shared_ptr<FactoryZero> factoryZero;

    bool initialised;
    Factory* factories[MAX_FACTORY_NUM];

    void init();
    void loadPlayerNames(istream& inStream, string line);
    void loadPoints(istream& inStream, int points);
    void loadFactoryZero(istream& inStream, string line);
    void loadFactories(istream& inStream, string line);
    void loadMosaic(istream& inStream, string line, shared_ptr<Player> player);
    void loadStorageRows(istream& inStream, string line, shared_ptr<Player> player);
    void loadBrokenStorage(istream& inStream, string strStorage, shared_ptr<Player> player);
    void deleteFactories();

    void printValues();
    bool validChar(char c);
    void saveGame(string filename);
    string factoriesToString();
    bool validateTurn(int factory, char tile, char row);
    bool validTileInRow(char tile, char row);
    bool fileExists(string filename);
    void performTurn(int factory, char tile, char row);

    void fillBoxLid();

    void fillBagFromBox();

    void fillBagFromBoxSeed(int seed);

    void fillFactories();

    void moveTilesEOR(shared_ptr<Player> player);
    bool factoriesEmpty();

    void setActivePlayer();

    void displayTurnUpdate();
};
#endif // GAMEENGINE_H