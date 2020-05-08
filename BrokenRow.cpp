
#include "BrokenRow.h"

BrokenRow::BrokenRow()
{
    maxSize = 7;
    tiles = make_shared<LinkedList>();
}

BrokenRow::~BrokenRow()
{

}

int BrokenRow::getMaxSize() {
    return maxSize;
}

void BrokenRow::addTile(char&& colour)
{
    tiles->addBack(move(colour));
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
    return tiles->size();
}

char BrokenRow::getTileAt(int index)
{
    return tiles->get(index);
}

void BrokenRow::print() {
    tiles->print();
}