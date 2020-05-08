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

    factoryZero = make_shared<FactoryZero>();
    for(int i = 0; i < MAX_FACTORY_NUM; ++i){
        factories[i] = make_shared<Factory>( i + 1 );
    }

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

    factoryZero = make_shared<FactoryZero>();
    for(int i = 0; i < MAX_FACTORY_NUM; ++i){
        factories[i] = make_shared<Factory>( i + 1 );
    }

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

        getline(inStream, line);
        loadFactoryZero(line);

        getline(inStream, line);
        loadFactory(1, line);
        getline(inStream, line);
        loadFactory(2, line);
        getline(inStream, line);
        loadFactory(3, line);
        getline(inStream, line);
        loadFactory(4, line);
        getline(inStream, line);
        loadFactory(5, line);

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

    cout << "Factory Zero: ";
    factoryZero->print();
    cout << endl;

    cout << "Factory 1: ";
    factories[0]->print();
    cout << endl;

    cout << "Factory 2: ";
    factories[1]->print();
    cout << endl;

    cout << "Factory 3: ";
    factories[2]->print();
    cout << endl;

    cout << "Factory 4: ";
    factories[3]->print();
    cout << endl;

    cout << "Factory 5: ";
    factories[4]->print();
    cout << endl;

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

void GameEngine::loadFactoryZero(string strFactory) {
   for(int i = 0; i < strFactory.length(); ++i){
        if(strFactory[i] !=  ' '){
            factoryZero->addToFac(move(strFactory[i]));
        }
    }
}

void GameEngine::loadFactory(int fNum, string strFactory){
    char tempfactory[MAX_FACTORY_TILES] = {'\0'};
    getCharArray(strFactory, tempfactory);
   
    if(fNum > 0 && fNum < 6) {
        for(int i = 0; i != MAX_FACTORY_TILES; ++i){
            factories[fNum - 1]->addToFactory(move(tempfactory[i]));
        }
    }
}

void GameEngine::getCharArray(string string, char* charArray){
    int counter = 0;
    for(int i = 0; i < string.length(); ++i){
        if(string[i] !=  ' '){
            charArray[counter] = string[i];
            ++counter;
        }
    }
}


 

