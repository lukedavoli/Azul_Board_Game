#ifndef FACTORYZERO_H
#define FACTORYZERO_H

#include <vector>
#include <string>
using std::string;

#define FACTORY_NUM 0
class FactoryZero
{

public:
    FactoryZero();
    ~FactoryZero();
    FactoryZero(FactoryZero& other);
    // Move Constructor
    FactoryZero(FactoryZero&& other);

//  Get factory number
int getFNum();

//  Insert tile within vector
void addToFac(char&& tile);

// Get number of tiles with the same color as the color selected
int getNumOfCoulour(char&& colour);

//  Remove tiles given the color selected (set them to null)
void removeTile(char&& colour);

void print();

std::string toString();

void clear();

char startingPlayer;

private:
    // startingPlayerMarker
    std::vector<char> tiles;
};
#endif // FACTORYZERO_H
 

 



