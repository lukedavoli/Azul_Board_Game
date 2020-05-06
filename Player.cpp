
#include "Player.h"

Player::Player(std::string name, int points)
{
    this->name = name;
    this->points = points;

    for(int i = 0; i < STORAGE_ROWS; i++)
    {
        storageRows[i] = new StorageRow(i + 1);
    }

    brokenRow = new BrokenRow();

    //TODO initiate mosaic
}

Player::~Player()
{
    for(int i = 0; i < STORAGE_ROWS; i++)
    {
        delete storageRows[i];
    }
}

std::string Player::getName()
{
    return name;
}

int Player::getPoints()
{
    return points;
}

void Player::setPoints(int points)
{
    this->points = points;
}

char **Player::getMosaic()
{
    return mosaic;
}

StorageRow *Player::getStorageRow(int row)
{
    return storageRows[row - 1];
}

BrokenRow *Player::getBroken()
{
    return brokenRow;
}
