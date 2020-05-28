#include "StorageRow.h"
#include <iostream>

StorageRow::StorageRow(int maxTiles){
    this->maxTiles = maxTiles;
    tiles = make_shared<LinkedList>();
}

StorageRow::~StorageRow(){

}

void StorageRow::addTile(char&& tile){
    tiles->addBack(move(tile));
}

char StorageRow::getOccupyingColour(){
    char firstTile = tiles->get(0);
    return firstTile;
}

bool StorageRow::isFull(){
    bool full = false;
    int occupied = getOccupied();
    
    if(maxTiles == occupied)
    {
        full = true;
    }
    return full;
}

char StorageRow::getFirstTile(){
   return tiles->get(0);
}

void StorageRow::clearCompleteRow(){
    tiles->clear();
}

int StorageRow::getLength(){
    return tiles->size();
}

int StorageRow::getMaxTiles(){
    return maxTiles;
}

char StorageRow::getTileAt(int index){
    return tiles->get(index);
}

void StorageRow::resetRow() {
    tiles->clear();
    for(int i = 0; i < maxTiles; ++i){
        tiles->addFront(move('.'));
    }
}

void StorageRow::print() {
    tiles->print();
}

string StorageRow::toString(){
    string row = "";
    int size = getLength();
    for(int i = 0; i < maxTiles - size; i++){
        row += ".";
        if(i != maxTiles){
            row += " ";
        }
    }

    for(int i = 0; i < size; i++){
        row += getTileAt(i);
        if(i != size){
            row += " ";
        }
    }

    return row;
}

string StorageRow::toStringUI() {
    string row = "";
    int size = getLength();
    for(int i = 0; i < maxTiles - size; i++){
        row += "\u25a2";
        if(i != maxTiles){
            row += " ";
        }
    }

    for(int i = 0; i < size; i++){
        char nextTile = getTileAt(i);
        string nextTileColour;
        if(nextTile == 'B'){
            nextTileColour = "\033[44;37;1mB\033[0m";
        }else if(nextTile == 'Y'){
            nextTileColour = "\033[43;37;1mY\033[0m";
        }else if(nextTile == 'R'){
            nextTileColour = "\033[41;37;1mR\033[0m";
        }else if(nextTile == 'U'){
            nextTileColour = "\033[40;37;1mU\033[0m";
        }else if(nextTile == 'L'){
            nextTileColour = "\033[42;37;1mL\033[0m";
        }
        row += nextTileColour;
        if(i != size){
            row += " ";
        }
    }

    return row;
}

string StorageRow::toStringBackwards() {
    string row = "";
    int size = getLength();

    for(int i = 0; i < size; i++){
        row += getTileAt(i);
        row += " ";
    }

    for(int i = 0; i < maxTiles - size; i++){
        row += ".";
        if(i != maxTiles){
            row += " ";
        }
    }

    return row;
}

int StorageRow::getOccupied(){
    int occupied = 0;
    int size = tiles->size();
    for(int i = 0; i < size; i++){
        if(getTileAt(i) != '.'){
            occupied++;
        }
    }
    return occupied;
}


