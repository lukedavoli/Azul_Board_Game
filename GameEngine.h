#include "Player.h"
 #include "Factory.h"

#define PROMPT "> "


class GameEngine
{

public:
    GameEngine();
    ~GameEngine();
    
 void newGame();
private:
shared_ptr<Player> player1;
shared_ptr<Player> player2;
shared_ptr<FactoryZero> factory0;
shared_ptr<Factory> factory1;
shared_ptr<Factory> factory2;
shared_ptr<Factory> factory3;
shared_ptr<Factory> factory4;
shared_ptr<Factory> factory5;





    
};
