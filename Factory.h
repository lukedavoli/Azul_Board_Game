
#ifndef FACTORY_ZERO
#define FACTORY_ZERO

#include <memory>

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
    int getNumberOfCol(char colour);

    // Remove tiles given the color selected (set them to null)
    void removeTile(char&& colour, std::shared_ptr<FactoryZero> factory);

    //  Move excess tiles to Factory Zero
    void moveToFactoryZ(std::shared_ptr<FactoryZero> factory);

    // Resets all chars in factory to '.'
    void clear();

    // This method is only for testing
    // We can remove it later
    void print();

    string toString();

    string toStringColour();

    void setTile(int index, char&& tile);

    bool isClear();

    string colourizeChar(char character);
private:

    char tiles[NUM_OF_TILES];
    int factoryNumber;


};

#endif // FACTORY_H

 



