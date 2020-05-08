
#ifndef FACTORY_ZERO
#define FACTORY_ZERO

#define NUM_OF_TILES 4
#include "FactoryZero.h"
class Factory
{

public:
 // Constructor takes in a number that will act as its index within its wrapper.

    Factory(int factoryNumber);
    // Copy constructor – useful for moving tiles to Factory Zero.
    Factory( Factory& other);
    ~Factory();
    // move constructor
    Factory(Factory&& other);

//  Get factory number
int getNumber();
// Add tiles to array
void addToFactory(char&& colour);
//  Get number of tiles with the same color as the color selected
int getNumberOfColour(char&& colour);

// Remove tiles given the color selected (set them to null)
void removeTile(char&& colour, FactoryZero* factory);

//  Move excess tiles to Factory Zero
void moveToFactoryZ(FactoryZero* factory);

// This method is only for testing 
// We can remove it later 
void print();
private:

char tiles[NUM_OF_TILES];
int factoryNumber;
};

#endif // FACTORY_H

 



