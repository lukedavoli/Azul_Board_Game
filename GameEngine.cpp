#include "GameEngine.h"
#include<iostream>

#define Starting_Points 0

using std::cout;
using std::cin;

GameEngine::GameEngine(){

}
GameEngine::~GameEngine(){


}

void GameEngine::newGame(){
    std::string p1Name = "";
    std::string p2Name = "";

    std::cout << "Starting a New Game\n" << std::endl;
    std::cout << "Enter a name for player 1" << std::endl;
    std::cout << PROMPT;
    std::cin >> p1Name;
    player1=make_shared<Player>(p1Name,0);
    

    std::cout << "Enter a name for player 2" << std::endl;
    std::cout << PROMPT;
    std::cin >> p2Name;

    player2=make_shared<Player>(p2Name,Starting_Points);
    factory0=make_shared<FactoryZero>();
    factory1=make_shared<Factory>(1);
    factory2=make_shared<Factory>(2);
    factory3=make_shared<Factory>(3);
    factory4=make_shared<Factory>(4);
    factory5=make_shared<Factory>(5);
    



    std::cout << "\nLet's Play!\n" <<player1->getName()<<","<<player2->getName()<< std::endl;


}
 

