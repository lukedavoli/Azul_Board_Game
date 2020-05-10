#ifndef MOSAIC
#define MOSAIC

#include "Tiles.h"

// #include <memory>
// #include <array>
// using std::shared_ptr;
// using std::make_shared;
// using std::array;

#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

#define DIM 5
#define MAX_NUM_OF_CHARS 9


class Mosaic {

public:
    Mosaic();
    ~Mosaic();

    string getRow(int rowNum);
    void loadRow(int rowNum, string row);
    void insertRow(int rowNum, char tile);

    void printMosaic();
    void clear();

    // To get a 2D array without white spaces.
    void removeWhiteSpaceFromRow(string string, char* newString);
    char** get2DMosaic();
    void print2DMosaic();

    bool validRowNum(int rowNum);
    bool validTile(char tile);
    string toString();

private:
    void update2DMosaic();
    bool setTile(char* tileSpace, char* tile);
    string rows[DIM];
    char** mosaic;


};
#endif //  MOSAIC