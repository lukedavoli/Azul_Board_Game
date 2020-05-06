#include "Mosaic.h"


#include <iostream>
using std::cout;
using std::endl;

Mosaic::Mosaic() {
    row1 = "b y r u l";
    row2 = "l b y r u";
    row3 = "u l b y r";
    row4 = "r u l b y";
    row5 = "y r u l b";
    
    mosaic = new char*[DIM];
    for(int i = 0; i < DIM; ++i){
        mosaic[i] = new char[DIM];
    }

    //mosaic  = make_shared<string>(row1 + '\n' + row2 + '\n' + row4 +  '\n' + row5+ '\n');
}

Mosaic::~Mosaic() {
    for(int i = 0; i < DIM; ++i){
        delete mosaic[i];
    }
    delete mosaic;
}

string Mosaic::getRow1() {
    return row1;
}
string Mosaic::getRow2() {
    return row2;
}
string Mosaic::getRow3() {
    return row3;
}
string Mosaic::getRow4() {
    return row4;
}
string Mosaic::getRow5() {
    return row5;
}

void Mosaic::insertRow(int row, char tile){
    
    if(row == 1){
        for(char tileSpace : row1){
            setTile(&tileSpace, &tile);
        }
    } else if (row == 2){
       for(char tileSpace : row2){
            setTile(&tileSpace, &tile);
        }
    } else if (row == 3){
        for(char tileSpace : row3){
            setTile(&tileSpace, &tile);
        }
    } else if (row == 4){
        for(char tileSpace : row4){
            setTile(&tileSpace, &tile);
        }
    } else if (row == 5){
        for(char tileSpace : row5){
            setTile(&tileSpace, &tile);
        }
    }
}

void Mosaic::setTile(char* tileSpace, char* tile){
    if (tileSpace == tile) {
        getTile(tile);
        tileSpace = tile;
    }
}

void Mosaic::getTile(char* tile){
    if(*tile == EMPTY_BLUE){
        *tile = BLUE;

    } else if(*tile == EMPTY_YELLOW){
        *tile = YELLOW;
    }
    else if(*tile == RED){
        *tile = RED;
    }
    else if(*tile == BLACK){
        *tile = BLACK;
    }
    else if(*tile == LIGHTB){
        *tile = LIGHTB;
    }
}

char** Mosaic::getMosaic() {
    return mosaic;
}

void Mosaic::updateMosaic() {
    string array[DIM] = {row1, row2, row3, row4, row5};
    for(int i = 0; i < DIM; ++i){
        removeWhiteSpaceFromRow(array[i],  mosaic[i]);
    }
}

void Mosaic::printMosaic() {
    
    if(mosaic != nullptr){
        for(int row = 0; row < DIM; ++row){
            for(int col = 0; col < DIM; ++col){
                cout << mosaic[row][col];
            }
             cout << endl;
        }
    } else {
        cout << "Mosaic is null." << endl;
    }
}

void Mosaic::removeWhiteSpaceFromRow(string string, char* newString){

    if(string.length() == MAX_NUM_OF_CHARS && newString != nullptr){
        int counter = 0;
        for(int i = 0; i < string.length(); ++i)
        {
            if(string[i] !=  ' '){
                newString[counter] = string[i];
                ++counter;
            }
        }
    }
}