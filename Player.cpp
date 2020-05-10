
#include "Player.h"

Player::Player(string name, int points)
{
    this->name = name;
    this->points = points;

    for(int i = 0; i < STORAGE_ROWS; i++)
    {
        storageRows[i] = make_shared<StorageRow>(i + 1);
    }

    brokenRow = make_shared<BrokenRow>();
    mosaic = make_shared<Mosaic>();
}

Player::~Player()
{

}

string Player::getName()
{
    return name;
}

void Player::setName(string name) {
    this->name = name;
}

int Player::getPoints()
{
    return points;
}

void Player::setPoints(int points)
{
    this->points = points;
}

shared_ptr<Mosaic> Player::getMosaic()
{
    return mosaic;
}

shared_ptr<StorageRow> Player::getStorageRow(int row)
{
    return storageRows[row - 1];
}

shared_ptr<BrokenRow> Player::getBroken()
{
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
        board += currRow->toString();
        board += " || ";
        board += mosaic->getRow(i + 1);
        board += "\n";
    }
    board += "broken: ";
    int brokenTiles = brokenRow->getLength();
    for(int t = 0; t < brokenTiles; t++){
        board += brokenRow->getTileAt(t);
        if(t != brokenTiles - 1){
            board += " ";
        }
    }

    return board;
}
