#ifndef MOSAIC
#define MOSAIC

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

#define BLUE 'B'
#define YELLOW 'Y'
#define RED 'R'
#define BLACK 'U'
#define LIGHT_BLUE 'L'


class Mosaic {

    public:
        Mosaic();
        ~Mosaic();
        
        string getRow(int rowNum);
        void loadRow(int rowNum, string row);
        void insertRow(int rowNum, char tile);

        void printMosaic();
        void resetMosaic();

        // To get a 2D array without white spaces.
        void removeWhiteSpaceFromRow(string string, char* newString);
        char** get2DMosaic();

        bool validRowNum(int rowNum);
        bool validTile(char tile);

    private:
        void update2DMosaic();
        bool setTile(char* tileSpace, char* tile);
        string rows[DIM];
        char** mosaic;

};
#endif //  MOSAIC