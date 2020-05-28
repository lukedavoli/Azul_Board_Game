#ifndef STORAGEROW_H
#define STORAGEROW_H

#include <memory>
#include "LinkedList.h"
#include <string>

using std::make_shared;
using std::shared_ptr;
using std::string;

class StorageRow
{
public:
    StorageRow(int maxTiles);
    ~StorageRow();

    //Add a tile to the row
    void addTile(char&& tile);

    //Get the tile colour currently occupying the row
    char getOccupyingColour();

    //Check whether the row is full or not
    bool isFull();

    //Clear a row that has been completed (use AFTER moving a tile to the mosaic and
    void clearCompleteRow();

    //Get the amount of tiles currently in a storage row
    int getLength();

    //Get the first tile from the row
    char getFirstTile();

    //Maximum amount of tiles that may be stored in a row
    int getMaxTiles();

    //Retrieve tile at a specific index
    char getTileAt(int index);

    // Sets all the tile spaces to '.';
    void resetRow();

    //Storage row to readable string format
    string toStringUI();

    string toString();

    //Convert to backwards string for saving to file in valid format
    string toStringBackwards();

    void print();

    //How many tiles are currently in the row occupying spaces
    int getOccupied();

private:
    shared_ptr<LinkedList> tiles;
    int maxTiles;
};


#endif //STORAGEROW_H
