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
#define BROKEN_ROW 'B'
#define INIT_POINTS 0
#define NUM_OF_PLAYERS 2
#define MAX_FACTORY_NUM 5
#define MAX_STORAGE_NUM 5
#define MAX_MOSAIC_ROW_NUM 5
#define MAX_BROKEN_TILES 7

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
    // Get the number of tiles currently in the box lid.
    int getNumOfBoxTiles();

    string nextTurn;
    shared_ptr<Player> player1;
    shared_ptr<Player> player2;
    shared_ptr<Player> activePlayer;
    shared_ptr<FactoryZero> factoryZero;

    // To check whether the factories ( or other objects ) have been created on the heap.
    bool initialised;

    Factory* factories[MAX_FACTORY_NUM];
    void deleteFactories();

    // Methods to load data in.
    void init();
    void loadPlayerNames(istream& inStream, string line);
    void loadPoints(istream& inStream, int points);
    void loadFactoryZero(istream& inStream, string line);
    void loadFactories(istream& inStream, string line);
    void loadMosaic(istream& inStream, string line, shared_ptr<Player> player);
    void loadStorageRows(istream& inStream, string line, shared_ptr<Player> player);
    void loadBrokenStorage(istream& inStream, string strStorage, shared_ptr<Player> player);
    void loadBag(istream& inStream, string strBag);
    void loadBoxLid(istream& inStream, string strLid);

    // Prints all the values from loading the file in.
    void printValues();

    // Checks if character is valid (valid chars = 'B', 'Y', 'R', 'U', 'L', 'F', '.')
    bool validChar(char c);

    // Saves the data into a file.
    void saveGame(string filename);

    string factoriesToString();
    bool validateTurn(int factory, char tile, char row);
    bool validTileInRow(char tile, char row);
    bool fileExists(string filename);
    void performTurn(shared_ptr<Player> player,int factory, char tile, char row);

    void fillBoxLid();

    // Fill the bag with tiles from the box lid randomly.
    void fillBagFromBox();

    // Fill the bag with tiles from the box lid randomly with the seed.
    void fillBagFromBoxSeed(int seed);

    // Fill the tile bag with tiles from the box lid sequentially.
    void fillBagSequentially();

    // Fill the factories from the tile bag sequentially.
    void fillFactories();

    // Moves the tiles at the end of round and scores.
    void moveTilesAndScore(shared_ptr<Player> player);

    // Moves the excess tiles from a full storage row to the box lid.
    void moveStorageTilesToBox(int rowNum, char tile);

    // Move Broken Storage tiles to box lid.
    void moveBrokenTilesToBox(shared_ptr<Player> player);

    void setActivePlayer();

    void displayTurnUpdate();

    string boxLidToString();

    string tileBagToString();

    // Checks if all the factories are empty.
    bool emptyFactories();

    // Calculate the score of the player.
    void score(shared_ptr<Player> player,int row,char tile);

    // Checks if the row character inputted is valid.
    // Takes in an int to return a row number if the character is valid.
    bool validRowChar(char row, int* r);

    void brokenScore(shared_ptr<Player> player);

};
#endif // GAMEENGINE_H