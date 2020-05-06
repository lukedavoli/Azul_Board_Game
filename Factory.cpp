#include "Factory.h"
#include <iostream>
#include <utility>


Factory::Factory(int factoryNumber){
    this->factoryNumber=factoryNumber;
     for (int i = 0; i < NUM_OF_TILES; ++i)
     {
       tiles[i]='.';   
     }
     
}

Factory::Factory(Factory& other):
    factoryNumber(other.factoryNumber)
    {
         for (int i = 0; i < NUM_OF_TILES; i++) {
            tiles[i] = other.tiles[i];
    }
    }
Factory::Factory(Factory&& other):
    factoryNumber(other.factoryNumber)
        {
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
    while (i<NUM_OF_TILES && tiles[i]!='.')
    {
        i++;
    }
   tiles[i]=colour;
    
}

int Factory::getNumberOfColour(char&& colour){
     int inFactory =0;
     for (int i = 0; i < NUM_OF_TILES; ++i)
     {
        if (tiles[i]==colour)
        {
            inFactory++;
        }
        
     }
     return inFactory;
     

}

void Factory::removeTile(char&& colour, FactoryZero* factory){
    for (int i = 0; i < NUM_OF_TILES; ++i)
    {
        if (tiles[i]==colour)
        {
            std::cout<<"test";
            tiles[i]='.';
        }
        
    }
    this->moveToFactoryZ(factory);
    
}

void Factory::moveToFactoryZ(FactoryZero* factory){
    for (int i = 0; i < NUM_OF_TILES; ++i)
    {
        if (tiles[i]!='.')
        {
            (*factory).addToFac(std::move(tiles[i]));
            tiles[i]='.';
        }
        
    }
    
}

void Factory::print(){
    for (int i = 0; i < NUM_OF_TILES; ++i)
    {
       std::cout<< tiles[i];
    }
    
}