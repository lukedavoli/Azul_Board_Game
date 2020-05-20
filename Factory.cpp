#include "Factory.h"
#include <iostream>


Factory::Factory(int factoryNumber){
    this->factoryNumber=factoryNumber;
    clear();
}

Factory::Factory(Factory& other): 
    factoryNumber(other.factoryNumber){
        for (int i = 0; i < NUM_OF_TILES; i++) {
            tiles[i] = other.tiles[i];
        }
}

Factory::Factory(Factory&& other):
    factoryNumber(other.factoryNumber){
        for (int i = 0; i < NUM_OF_TILES; i++) {
            tiles[i] = other.tiles[i];
        }
}

Factory::~Factory(){
}

int Factory::getNumber(){
    return this->factoryNumber;
}

void Factory::addToFactory(char&& colour){
    int i=0;
    while (i<NUM_OF_TILES && tiles[i]!='.'){
        i++;
    }
    tiles[i]=colour;
}

int Factory::getNumberOfColour(char&& colour){
    int inFactory =0;
    for (int i = 0; i < NUM_OF_TILES; ++i){
        if (tiles[i]==colour){
            inFactory++;
        }
     }
     return inFactory;
}

void Factory::removeTile(char&& colour, std::shared_ptr<FactoryZero> factory){
    for (int i = 0; i < NUM_OF_TILES; ++i){
        if (tiles[i]==colour){
            tiles[i]='.';
        }
    }
    this->moveToFactoryZ(factory);
}

void Factory::moveToFactoryZ(std::shared_ptr<FactoryZero> factory){
    for (int i = 0; i < NUM_OF_TILES; ++i){
        if (tiles[i]!='.'){
            (*factory).addToFac(std::move(tiles[i]));
            tiles[i]='.';
        }
    }
}

void Factory::print(){
    for (int i = 0; i < NUM_OF_TILES; ++i){
       std::cout << tiles[i] << " ";
    }
}

void Factory::clear() {
    for (int i = 0; i < NUM_OF_TILES; ++i){
       tiles[i] = '.';   
    }
}

string Factory::toString() {
    string strTiles = "";
    for(int i = 0; i < NUM_OF_TILES; i++){
        strTiles += tiles[i];
        if(i != NUM_OF_TILES - 1){
            strTiles += " ";
        }
    }
    return strTiles;
}

void Factory::setTile(int index, char&& tile) {
    tiles[index] = tile;
}

bool Factory::isClear() {
    bool clear = true;
    for(int i = 0; i < NUM_OF_TILES; ++i){
        if(tiles[i] != '.') {
            clear = false;
        }
    }
    return clear;
}
