#ifndef BROKENROW_H
#define BROKENROW_H

#include <memory>
#include "LinkedList.h"
#include <string>

using std::make_shared;
using std::shared_ptr;
using std::string;


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
    string toString();

    bool hasFirstPlayerMarker();

private:
    shared_ptr<LinkedList> tiles;


};

#endif //BROKENROW_H
