#include "StorageRow.h"

StorageRow::StorageRow(int maxTiles)
{
    this->maxTiles = maxTiles;
    tiles = new LinkedList();
}

StorageRow::~StorageRow()
{
    delete tiles;
}

void StorageRow::addTile(char&& tile)
{
    tiles->addFront(tile);
}

char StorageRow::getOccupyingColour()
{
    char firstTile = tiles->get(0);
    return firstTile;
}

bool StorageRow::isFull()
{
    bool full = false;
    if(maxTiles == tiles->size())
    {
        full = true;
    }
    return full;
}

char StorageRow::getFirstTile()
{
    tiles->get(0);
}

void StorageRow::clearCompleteRow()
{
    tiles->clear();
}

int StorageRow::getLength()
{
    tiles->size();
}

int StorageRow::getMaxTiles()
{
    return maxTiles;
}

char StorageRow::getTileAt(int index)
{
    return tiles->get(index);
}

