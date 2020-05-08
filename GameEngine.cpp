#include "GameEngine.h"

GameEngine::GameEngine(){

}
GameEngine::~GameEngine(){

}

void GameEngine::init() {
    string p1Name = " ";
    string p2Name = " ";
   

    player1 = make_shared<Player>(p1Name, INIT_POINTS);
    player2 = make_shared<Player>(p2Name, INIT_POINTS);

    nextTurn = player1->getName();

    factory0 = make_shared<FactoryZero>();
    factory1 = make_shared<Factory>(1);
    factory2 = make_shared<Factory>(2);
    factory3 = make_shared<Factory>(3);
    factory4 = make_shared<Factory>(4);
    factory5 = make_shared<Factory>(5);

}

void GameEngine::newGame(){

    std::string p1Name = "";
    std::string p2Name = "";

    std::cout << "Starting a New Game\n" << std::endl;
    std::cout << "Enter a name for Player 1" << std::endl;
    std::cout << PROMPT;
    std::cin >> p1Name;

    player1 = make_shared<Player>(p1Name, INIT_POINTS);
    
    std::cout << "Enter a name for Player 2" << std::endl;
    std::cout << PROMPT;
    std::cin >> p2Name;

    player2 = make_shared<Player>(p2Name, INIT_POINTS);

    factory0=make_shared<FactoryZero>();
    factory1=make_shared<Factory>(1);
    factory2=make_shared<Factory>(2);
    factory3=make_shared<Factory>(3);
    factory4=make_shared<Factory>(4);
    factory5=make_shared<Factory>(5);

    std::cout << "\nLet's Play!\n" <<player1->getName()<<","<<player2->getName()<< std::endl;
}

void GameEngine::loadGame(string filename){
    init();
    ifstream inStream(filename);
    string line = " ";
    int points = 0;

    while(!inStream.eof()){

        getline(inStream, line);
        player1->setName(line);

        getline(inStream, line);
        player2->setName(line);

        getline(inStream, line);
        points = std::stoi(line);
        player1->setPoints(points);

        getline(inStream, line);
        points = std::stoi(line);
        player2->setPoints(points);
        
        getline(inStream, line);
        nextTurn = line;

        // getline(inStream, line);
        // f1 = line;
        // getline(inStream, line);
        // f2 = line;
        // getline(inStream, line);
        // f3 = line;
        // getline(inStream, line);
        // f4 = line;
        // getline(inStream, line);
        // f4 = line;

        getline(inStream, line);
        player1->getMosaic()->loadRow(1, line);
        getline(inStream, line);
        player1->getMosaic()->loadRow(2, line);
        getline(inStream, line);
        player1->getMosaic()->loadRow(3, line);
        getline(inStream, line);
        player1->getMosaic()->loadRow(4, line);
        getline(inStream, line);
        player1->getMosaic()->loadRow(5, line);

        getline(inStream, line);
        player2->getMosaic()->loadRow(1, line);
        getline(inStream, line);
        player2->getMosaic()->loadRow(2, line);
        getline(inStream, line);
        player2->getMosaic()->loadRow(3, line);
        getline(inStream, line);
        player2->getMosaic()->loadRow(4, line);
        getline(inStream, line);
        player2->getMosaic()->loadRow(5, line);

    }
    inStream.close();

    cout << "Player 1 Name: " << player1->getName() << endl;
    cout << "Player 2 Name: " << player2->getName() << endl;
    cout << "Player 1 Points: " << player1->getPoints() << endl;
    cout << "Player 2 Points: " << player2->getPoints() << endl;
    cout << "Next Turn: " << nextTurn << endl;
    cout << "Player 1 Mosaic Row 1: " << player1->getMosaic()->getRow(1) << endl;
    cout << "Player 1 Mosaic Row 2: " << player1->getMosaic()->getRow(2) << endl;
    cout << "Player 1 Mosaic Row 3: " << player1->getMosaic()->getRow(3) << endl;
    cout << "Player 1 Mosaic Row 4: " << player1->getMosaic()->getRow(4) << endl;
    cout << "Player 1 Mosaic Row 5: " << player1->getMosaic()->getRow(5) << endl;
    cout << "Player 2 Mosaic Row 1: " << player2->getMosaic()->getRow(1) << endl;
    cout << "Player 2 Mosaic Row 2: " << player2->getMosaic()->getRow(2) << endl;
    cout << "Player 2 Mosaic Row 3: " << player2->getMosaic()->getRow(3) << endl;
    cout << "Player 2 Mosaic Row 4: " << player2->getMosaic()->getRow(4) << endl;
    cout << "Player 2 Mosaic Row 5: " << player2->getMosaic()->getRow(5) << endl;
}

 

