
#include "BrokenRow.h"

BrokenRow::BrokenRow()
{
    tiles = make_shared<LinkedList>();
}

BrokenRow::~BrokenRow()
{

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

string BrokenRow::toString(){
    string strBroken = "";
    int brokenTiles = getLength();
    for(int t = 0; t < brokenTiles; t++){
        strBroken += getTileAt(t);
        if(t != brokenTiles - 1){
            strBroken += " ";
        }
    }
    return strBroken;
}