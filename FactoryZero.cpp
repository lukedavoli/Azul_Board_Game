#include "FactoryZero.h"
#include <iostream>
#include<vector>
#include<utility>

FactoryZero::FactoryZero(){
    this->srartingPlayer='F';
    tiles.push_back(srartingPlayer);
}

FactoryZero::FactoryZero(FactoryZero& other):
FactoryZero()
{
  tiles=other.tiles;
}

FactoryZero::FactoryZero(FactoryZero&& other)
{
    int size=other.tiles.size();
 for (int i = 0; i < size; ++i)
 {
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
    for (int i = 0; i < size; ++i)
    {
        if (tiles[i]==colour)
        {   
           numIn++;
        }
        
    }
    return numIn;
}

void FactoryZero::removeTile(char&& colour){
  int size=tiles.size();
  for (int i = 0; i < size; ++i)
    {
        if (tiles[i]==colour)
        {   
            tiles.erase(tiles.begin()+i);   
            
         }
        
    }

}

void FactoryZero::print(){
        int size=tiles.size();
        for(int i=0;i<size;i++){
        std::cout << tiles[i] << " ";
    }
}
