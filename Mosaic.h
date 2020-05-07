#ifndef MOSAIC
#define MOSAIC

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
        bool setTile(char* tileSpace, char* tile);

        void printMosaic();
        void resetMosaic();

        // To get a 2D array without white spaces
        void removeWhiteSpaceFromRow(string string, char* newString);
        void update2DMosaic();

        // Get 2D array
        char** get2DMosaic();

        // Test
        void print2DMosaic();

        bool validRowNum(int rowNum);
        bool validTile(char tile);


    private:

        string rows[DIM];
        char** mosaic;

};
#endif //  MOSAIC