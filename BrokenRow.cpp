
#include "BrokenRow.h"

BrokenRow::BrokenRow()
{
    tiles = new LinkedList();
}

BrokenRow::~BrokenRow()
{
    delete tiles;
}

void BrokenRow::addTile(char&& colour)
{
    tiles->addFront(colour);
}

void BrokenRow::clearRow()
{
    tiles->clear();
}

bool BrokenRow::isFull()
{
    bool full = false;
    if(tiles->size() == MAX_TILES)
    {
        full = true;
    }
    return full;
}

int BrokenRow::getLength()
{
    tiles->size();
}

char BrokenRow::getTileAt(int index)
{
    return tiles->get(index);
}