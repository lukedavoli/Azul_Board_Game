#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "StorageRow.h"
#include "BrokenRow.h"

#define STORAGE_ROWS 5

class Player
{
public:
    Player(std::string name, int points);
    ~Player();

    //get player name
    std::string getName();

    //get player points
    int getPoints();

    //set player points
    void setPoints(int points);

    //get the player's mosaic
    char** getMosaic();

    //get a specific storage row
    StorageRow* getStorageRow(int row);

    //get the player's broken row
    BrokenRow* getBroken();

private:
    std::string name;
    int points;
    char** mosaic;
    StorageRow* storageRows[STORAGE_ROWS];
    BrokenRow* brokenRow;
};

#endif PLAYER_H
