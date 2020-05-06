#include "Player.h"

Player::Player(string name, int points){
    this->name = name;
    this->points = points;
    mosaic = make_shared<Mosaic>();
}

Player::~Player(){

}

int Player::getPoints() {
    return points;
}

void Player::setPoints(int points) {
    this->points = points;
}

string Player::getName() {
    return name;
}

bool Player::hasNextTurn() {
    return nextTurn;
}

void Player::setNextTurn(bool boolean){
    this->nextTurn = boolean;
}

shared_ptr<Mosaic> Player::getMosaic() {
    return mosaic;  
}

// shared_ptr<Storage> Player::getStorage() {
//     return storage;
// }

// shared_ptr<Broken> Player::getBroken() {
//     return broken;
// }


