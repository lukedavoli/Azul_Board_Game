
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

string BrokenRow::toStringUI(){
    string strBroken = "";
    int tilesInBroken = getLength();
    for(int t = 0; t < MAX_TILES; t++){
        if(t == 0){
            strBroken += "-1 ";
        }else if(t == 2){
            strBroken += " -2 ";
        }else if(t == 5){
            strBroken += " -3 ";
        }
        if(t < tilesInBroken)
        {
            strBroken += colourizeChar(getTileAt(t)) + " ";
        }else{
            strBroken += "\u25a2";
            strBroken += " ";
        }
    }
    return strBroken;
}

string BrokenRow::colourizeChar(char character){
    string retVal;
    if(character == 'B'){
        retVal = "\033[44;37;1mB\033[0m";
    }else if(character == 'Y'){
        retVal = "\033[43;37;1mY\033[0m";
    }else if(character == 'R'){
        retVal = "\033[41;37;1mR\033[0m";
    }else if(character == 'U'){
        retVal = "\033[40;37;1mU\033[0m";
    }else if(character == 'L'){
        retVal = "\033[42;37;1mL\033[0m";
    }else if(character == 'F'){
        retVal = "\033[47;30;1mF\033[0m";
    }
    return retVal;
}