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
        factories[i] = make_shared<Factory>(i + 1);
    }

    std::cout << "\nLet's Play!\n" <<player1->getName()<<","<<player2->getName()<< std::endl;
}

void GameEngine::loadGame(string filename){
    init();
    ifstream inStream(filename);
    string line = " ";
    string p1Name;
    string p2Name;
    int p1Points = 0;
    int p2Points = 0;

        inStream >> p1Name;
        player1->setName(p1Name);
        inStream >> p2Name;
        player2->setName(p2Name);

        inStream >> p1Points;
        player1->setPoints(p1Points);
        inStream >> p2Points;
        player2->setPoints(p2Points);

        inStream >> nextTurn;

        // char c = ' ';
        // while(inStream.get(c) && (c != ' ' || c != '\n')) {
        //     factoryZero->clear(); 
        //     factoryZero->addToFac(move(c));
        // }

        getline(inStream, line);

        getline(inStream, line);
        loadFactoryZero(line);

        for(int i = 0; i < MAX_FACTORY_NUM; ++i){
            getline(inStream, line);
            loadFactory(i+1, line);
        }
        
        for(int i = 0; i < MAX_MOSAIC_ROW_NUM; ++i){
            getline(inStream, line);
            player1->getMosaic()->loadRow(i+1, line);
        }

        for(int i = 0; i < MAX_MOSAIC_ROW_NUM; ++i){
            getline(inStream, line);
            player2->getMosaic()->loadRow(i+1, line);
        }

        for(int i = 0; i < MAX_STORAGE_NUM; ++i){
            getline(inStream, line);
            loadStorageRow(i+1, player1, line);
        }

        for(int i = 0; i < MAX_STORAGE_NUM; ++i){
            getline(inStream, line);
            loadStorageRow(i+1, player2, line);
        }

        getline(inStream, line);
        loadBrokenStorage(player1, line);

        getline(inStream, line);
        loadBrokenStorage(player2, line);
    
    inStream.close();

    cout << "Player 1 Name: " << player1->getName() << endl;
    cout << "Player 2 Name: " << player2->getName() << endl;
    cout << "Player 1 Points: " << player1->getPoints() << endl;
    cout << "Player 2 Points: " << player2->getPoints() << endl;
    cout << "Next Turn: " << nextTurn << endl;

    cout << "Factory Zero: ";
    factoryZero->print();
    cout << endl;

    int maxRowNum = 5;
    for(int i = 0; i < maxRowNum; ++i){
        cout << "Factory "<< i+1 << ": ";
        factories[i]->print();
        cout << endl;
    }

 
    for(int i = 0; i < maxRowNum; ++i){
        cout << "Player 1 Mosaic Row "<< i+1 << ": " << player1->getMosaic()->getRow(i+1) << endl;
    }

    for(int i = 0; i < maxRowNum; ++i){
        cout << "Player 2 Mosaic Row "<< i+1 << ": " << player2->getMosaic()->getRow(i+1) << endl;
    }

    
    for(int i = 0; i < maxRowNum; ++i) {
        cout << "Player 1 Storage Row "  << i+1 << ": ";
        player1->getStorageRow(i+1)->print();
        cout << endl;
    }

    for(int i = 0; i < maxRowNum; ++i) {
        cout << "Player 2 Storage Row " << i+1 << ": ";
        player2->getStorageRow(i+1)->print();
        cout << endl;
    }

    cout << "Player 1 Broken Tiles: ";
    player1->getBroken()->print();
    cout << endl;

    cout << "Player 2 Broken Tiles: ";
    player2->getBroken()->print();
    cout << endl;


   
}


/* 
    Loads in Factory Zero
    Clears factory
    FOR each character within string
        IF character is not white space
            ADD to factory.
*/
void GameEngine::loadFactoryZero(string strFactory) {
    factoryZero->clear();
    for(int i = 0; i < strFactory.length(); ++i){
        if(strFactory[i] !=  ' '){
            factoryZero->addToFac(move(strFactory[i]));
        }
    }
}


/*
    Loads in a Standard Factory
    Create a char array containing only tile chars (no white space)
    FOR 0 to MAX_FACTORY_TILES
        ADD tile to factory.
*/

void GameEngine::loadFactory(int fNum, string strFactory){
    char tempfactory[MAX_FACTORY_TILES] = {'\0'};
    getCharArray(strFactory, tempfactory);
   
    if(fNum > 0 && fNum < 6) {
        factories[fNum-1]->clear();
        for(int i = 0; i != MAX_FACTORY_TILES; ++i){
            factories[fNum - 1]->addToFactory(move(tempfactory[i]));
        }
    }
}

void GameEngine::loadStorageRow(int rNum, shared_ptr<Player> player, string strStorage) {
    if(rNum > 0  && rNum < 6) {
        player->getStorageRow(rNum)->clearCompleteRow();
        char tempStorage[rNum];
        getCharArray(strStorage, tempStorage);
        for(int i = 0; i < rNum; ++i){
            player->getStorageRow(rNum)->addTile(move(tempStorage[i]));
        }
    }
}

void GameEngine::loadBrokenStorage(shared_ptr<Player> player, string strBroken){
    player->getBroken()->clearRow();
    //cout << strBroken << endl;
    char tempStorage[player->getBroken()->getMaxSize()];
    getCharArray(strBroken, tempStorage);
    for(int i = 0; i < player->getBroken()->getMaxSize(); ++i){
        player->getBroken()->addTile(move(tempStorage[i]));
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

void GameEngine::printStorageRowAsStr(int rNum, shared_ptr<Player> player){
    for(int i = 0; i < rNum; ++i){
        cout << player->getStorageRow(rNum)->getTileAt(i) << " ";
    }
   
}
 

