
#include "Player.h"

Player::Player(std::string name, int points)
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

Mosaic Player::getMosaic()
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
