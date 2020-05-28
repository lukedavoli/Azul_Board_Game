
#include "Player.h"

Player::Player(string name, int points){
    this->name = name;
    this->points = points;

    for(int i = 0; i < STORAGE_ROWS; i++){
        storageRows[i] = make_shared<StorageRow>(i + 1);
    }

    brokenRow = make_shared<BrokenRow>();
    mosaic = make_shared<Mosaic>();
}

Player::~Player(){

}

string Player::getName(){
    return name;
}

void Player::setName(string name) {
    this->name = name;
}

int Player::getPoints(){
    return points;
}

void Player::setPoints(int points){
    this->points = points;
}

shared_ptr<Mosaic> Player::getMosaic(){
    return mosaic;
}

shared_ptr<StorageRow> Player::getStorageRow(int row){
    return storageRows[row - 1];
}

shared_ptr<BrokenRow> Player::getBroken() {
    return brokenRow;
}

string Player::boardToString() {
    string board;
    for(int i = 0; i < STORAGE_ROWS; i++){
        board += std::to_string(i + 1) + ":";
        for(int s = 0; s < SPACES - 1 - i * WHITESPACES; s++){
            board += " ";
        }
        shared_ptr<StorageRow> currRow = getStorageRow(i + 1);
        board += currRow->toStringUI();
        board += " \u2b9e ";
        board += " " + colourizeRow(mosaic->getRow(i + 1));
        board += "\n";
    }
    board += "broken: ";
    board += brokenRow->toStringUI();

    return board;
}

string Player::colourizeRow(string row){
    string colourRow = " ";
    for(std::string::size_type i = 0; i < row.size(); ++i){
        colourRow += colourizeChar(row[i]) + " ";
    }
    return colourRow;
}

string Player::colourizeChar(char character){
    string retVal;
    if(character == 'B'){
        retVal = "\033[44;37;1mB\033[0m";
    }else if(character == 'Y'){
        retVal = "\033[43;37;1mY\033[0m";
    }else if(character == 'R'){
        retVal = "\033[41;37;1mR\033[0m";
    }else if(character == 'U'){
        retVal = "\033[40;37;1mU\033[0m";
    }else if(character == 'L'){
        retVal = "\033[42;37;1mL\033[0m";
    }else if(character == 'b'){
        retVal = "\033[34;1mb\033[0m";
    }else if(character == 'y'){
        retVal = "\033[33;1my\033[0m";
    }else if(character == 'r'){
        retVal = "\033[31;1mr\033[0m";
    }else if(character == 'u'){
        retVal = "\033[30;1mu\033[0m";
    }else if(character == 'l'){
        retVal = "\033[32;1ml\033[0m";
    }
    return retVal;
}
