#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Mosaic.h"
#include <memory>
// #include "Storage.h"
// #include "Broken.h"

using std::make_shared;
using std::shared_ptr;
using std::string;

class Player {

    public:

        Player(string name, int points);
        ~Player();

        int getPoints();
        void setPoints(int points);
        string getName();

        bool hasNextTurn();
        void setNextTurn(bool boolean);

        shared_ptr<Mosaic> getMosaic();
        // shared_ptr<Storage> getStorage();
        // shared_ptr<Broken> getBrokenStorage();
        

    private:
        string name;
        int points;
        bool nextTurn;

        shared_ptr<Mosaic> mosaic;
        // shared_ptr<Storage> storage;
        // shared_ptr<Broken> broken;

};


#endif // PLAYER_H