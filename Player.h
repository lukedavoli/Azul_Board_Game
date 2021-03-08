#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>

#include "StorageRow.h"
#include "BrokenRow.h"
#include "Mosaic.h"

using std::shared_ptr;
using std::make_shared;
using std::string;

#define SPACES 10
#define WHITESPACES 2
#define STORAGE_ROWS 5

class Player
{
public:
    Player(string name, int points);
    ~Player();

    //get player name
    string getName();
    void setName(string name);

    //get player points
    int getPoints();

    //set player points
    void setPoints(int points);

    //get a specific storage row
    shared_ptr<StorageRow> getStorageRow(int row);

    //get the player's broken row
    shared_ptr<BrokenRow> getBroken();

    shared_ptr<Mosaic> getMosaic();

    string boardToString();

    string colourizeRow(string row);

    string colourizeChar(char character);

private:
    string name;
    int points;
    shared_ptr<Mosaic> mosaic;
    shared_ptr<StorageRow> storageRows[STORAGE_ROWS];
    shared_ptr<BrokenRow> brokenRow;
};

#endif //PLAYER_H
