#ifndef BROKENROW_H
#define BROKENROW_H

#include <memory>
#include "LinkedList.h"

using std::make_shared;
using std::shared_ptr;


#define MAX_TILES 7

class BrokenRow
{
public:
    BrokenRow();
    ~BrokenRow();

    //Add a tile to the row of broken tiles
    void addTile(char&& colour);

    //Clear the row (Note: use AFTER moving tiles to box lid)
    void clearRow();

    //Check to see if the broken row is full
    bool isFull();

    //get amount of tiles in broken row
    int getLength();

    char getTileAt(int index);

    void print();

    int getMaxSize();

private:
    shared_ptr<LinkedList> tiles;
    int maxSize;
};

#endif //BROKENROW_H
