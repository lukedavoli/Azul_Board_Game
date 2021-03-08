#include "FactoryZero.h"


FactoryZero::FactoryZero(){
    this->startingPlayer = FIRST_PLAYER_MARKER;
    tiles.push_back(startingPlayer);
}

FactoryZero::FactoryZero(FactoryZero& other):
FactoryZero(){
  tiles=other.tiles;
}

FactoryZero::FactoryZero(FactoryZero&& other){
    int size=other.tiles.size();
    for (int i = 0; i < size; ++i){
        tiles.push_back(std::move(other.tiles[i]));
    }
}

FactoryZero::~FactoryZero(){
    tiles.clear();
}

int FactoryZero::getFNum(){
    return FACTORY_NUM;
}

void FactoryZero::addToFac(char&& tile){
    tiles.push_back(std::move(tile));
}

int FactoryZero::getNumOfCoulour(char&& colour){
   int numIn=0;
   int size=tiles.size();
    for (int i = 0; i < size; ++i){
        if (tiles[i]==colour){   
           numIn++;
        }
    }
    return numIn;
}

int FactoryZero::getNumOfCol(char colour){
   int numIn=0;
   int size=tiles.size();
    for (int i = 0; i < size; ++i){
        if (tiles[i]==colour){   
           numIn++;
        }
    }
    return numIn;
}

void FactoryZero::removeTile(char&& colour){
   tiles.erase(std::remove(tiles.begin(),tiles.end(),colour),tiles.end());
}

void FactoryZero::print(){
    int size=tiles.size();
    for( int i = 0 ; i < size ; i++){
        std::cout << tiles[i] << " ";
    }
}

void FactoryZero::clear() {
    tiles.clear();
}

string FactoryZero::toString() {
    string strTiles = "";
    int size = tiles.size();
    for(int i = 0 ; i < size ; i++){
        strTiles += tiles[i];
        if(i != size - 1){
            strTiles += " ";
        }
    }
    return strTiles;
}

string FactoryZero::toStringColour(){
    string strTiles = "";
    int size = tiles.size();
    for(int i = 0 ; i < size ; i++){
        strTiles += colourizeChar(tiles[i]);
        if(i != size - 1){
            strTiles += " ";
        }
    }
    return strTiles;
}

int FactoryZero::getSize(){
    return tiles.size();
}

// Clears all tiles and adds the First Player Marker.
void FactoryZero::reset() {
    tiles.clear();
    tiles.push_back(startingPlayer);
}

string FactoryZero::colourizeChar(char character){
    string retVal;
    if(character == 'B'){
        retVal = "\033[44;37;1mB\033[0m";
    }else if(character == 'Y'){
        retVal = "\033[103;37;1mY\033[0m";
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