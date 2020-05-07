#ifndef MOSAIC
#define MOSAIC
#include <string>
#include <memory>

using std::make_shared;
using std::shared_ptr;
using std::string;
#define DIM 5
#define MAX_NUM_OF_CHARS 9
#define ROWS 5
#define COLS 5

#define EMPTY_BLUE 'b'
#define EMPTY_YELLOW 'y'
#define EMPTY_RED 'r'
#define EMPTY_BLACK 'u'
#define EMPTY_LIGHTB 'l'

#define BLUE 'B'
#define YELLOW 'Y'
#define RED 'R'
#define BLACK 'U'
#define LIGHTB 'L'


class Mosaic {

    public:
        Mosaic();
        ~Mosaic();
        
        string getRow1();
        string getRow2();
        string getRow3();
        string getRow4();
        string getRow5();

        

        void insertRow(int row, char tile);
        void getTile(char* tile);
        void setTile(char* tileSpace, char* tile);

        // Test
        void printMosaic();

        // To get a 2D array without white spaces
        void removeWhiteSpaceFromRow(string string, char* newString);
        void updateMosaic();

        // Get 2D array
        char** getMosaic();

    private:
        string row1;
        string row2;
        string row3;
        string row4;
        string row5;
        char** mosaic;

};
#endif //  MOSAIC