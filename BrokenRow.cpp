
#include "BrokenRow.h"

BrokenRow::BrokenRow(){
    tiles = make_shared<LinkedList>();
}

BrokenRow::~BrokenRow(){

}

void BrokenRow::addTile(char&& colour){
    tiles->addBack(move(colour));
}

void BrokenRow::clearRow(){
    tiles->clear();
}

bool BrokenRow::isFull(){
    bool full = false;
    if(tiles->size() == MAX_TILES){
        full = true;
    }
    return full;
}

int BrokenRow::getLength(){
    return tiles->size();
}

char BrokenRow::getTileAt(int index){
    return tiles->get(index);
}

void BrokenRow::print() {
    tiles->print();
}

bool BrokenRow::hasFirstPlayerMarker(){
    bool hasF = false;
    int size = tiles->size();
    //Iterate through LL, set hasF to true if/when 'F' found
    for(int i = 0; i < size; i++){
        if(getTileAt(i) == 'F'){
            hasF = true;
        }
    }
    return hasF;
}

string BrokenRow::toString(){
    string strBroken = "";
    int brokenTiles = getLength();
    for(int t = 0; t < brokenTiles; t++){
        //Append each tile with a space in between
        strBroken += getTileAt(t);
        if(t != brokenTiles - 1){
            strBroken += " ";
        }
    }
    return strBroken;
}