#include "Mosaic.h"

Mosaic::Mosaic() {

    clear();
    
    // Creates the 2D array on the heap.
    // Then uses 'update2DMosaic()' to actually have tiles in the 2D array.
    mosaic = new char*[DIM];
    for(int i = 0; i < DIM; ++i){
        mosaic[i] = new char[DIM];
    }
    update2DMosaic();
}

Mosaic::~Mosaic() {
    for(int i = 0; i < DIM; ++i){
        delete mosaic[i];
    }
    delete mosaic;
}

void Mosaic::clear() {
    string row1 = "b y r u l";
    string row2 = "l b y r u";
    string row3 = "u l b y r";
    string row4 = "r u l b y";
    string row5 = "y r u l b";
    
    string temp[DIM] = {row1, row2, row3, row4, row5};
    for(int i = 0; i != DIM; ++i){
        rows[i] = temp[i];
    }
}

string Mosaic::getRow(int rowNum) {
    if(validRowNum(rowNum)) {
         return rows[rowNum-1];
    }
    return "Error - invalid row number";
}

void Mosaic::loadRow(int rowNum, string row) {
    if(validRowNum(rowNum)) {
        if(row.size() == MAX_NUM_OF_CHARS){
            rows[rowNum-1] = row;
        }
    }
}

void Mosaic::insertRow(int rowNum, char tile){
    if(validRowNum(rowNum)) {
        if(validTile(tile)){
            for(int i = 0; i < MAX_NUM_OF_CHARS; ++i){
                if(setTile(&rows[rowNum-1].at(i), &tile)){
                    i = MAX_NUM_OF_CHARS;
                }
            }
        }
    }
}

bool Mosaic::setTile(char* tileSpace, char* tile){
    bool success = false;
    *tile = tolower(*tile);
    if(*tileSpace == *tile) {
        *tileSpace = toupper(*tile);
        success = true;
    }
    return success;
}

void Mosaic::printMosaic() {
    for(int i = 0; i < DIM; ++i){
        cout << rows[i] << endl;
    }
}

char** Mosaic::get2DMosaic() {
    update2DMosaic();
    return mosaic;
}

// Inserts the data from 'rows' into the 2D mosaic.
void Mosaic::update2DMosaic() {
    for(int i = 0; i < DIM; ++i){
        removeWhiteSpaceFromRow(rows[i],  mosaic[i]);
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

bool Mosaic::validTile(char tile) {
    bool valid = false;
    if(tile == BLUE || tile == YELLOW || tile == RED || tile == BLACK || tile == LIGHT_BLUE){
        valid = true;
    }
    return valid;
}

bool Mosaic::validRowNum(int rowNum){
    bool valid = false;
    if(rowNum > 0 && rowNum <= DIM) {
        valid = true;
    }
    return valid;
}
