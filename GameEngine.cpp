#include "GameEngine.h"

GameEngine::GameEngine(){
    initialised = false;

}
GameEngine::~GameEngine(){
    deleteFactories();
}

void GameEngine::deleteFactories() {
    for(int i = 0; i < MAX_FACTORY_NUM; ++i){
        delete factories[i];
    }
}

void GameEngine::init() {
    // Delete variables on the heap if they have already been created.
    if(initialised == true){
        deleteFactories();
    }
    // Set initialised to true, because factories will be created on the heap here.
    initialised = true;

    string p1Name = " ";
    string p2Name = " ";

    player1 = make_shared<Player>(p1Name, INIT_POINTS);
    player2 = make_shared<Player>(p2Name, INIT_POINTS);

    nextTurn = player1->getName();
    factoryZero = make_shared<FactoryZero>();
    
    for(int i = 0; i < MAX_FACTORY_NUM; ++i){
        factories[i] = new Factory(i+1);
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

    std::cout << "Who most recently visited Portugal?\n" <<
                 "[1] " << p1Name << "\n" <<
                 "[2] " << p2Name << endl;
    int mostRecent = 0;
    while(1 != mostRecent && mostRecent != 2){
        std::cout << PROMPT;
        std::cin >> mostRecent;
    }
    if(mostRecent == 1){
        nextTurn = p1Name;
    } else{
        nextTurn = p2Name;
    }


    factoryZero = make_shared<FactoryZero>();
    for(int i = 0; i < MAX_FACTORY_NUM; ++i){
        factories[i] = new Factory(i+1);
    }

    std::cout << "\n" << player1->getName() << " and " << player2->getName() << ", Let's Play!\n" << std::endl;

    enterGame();
}

void GameEngine::loadGame(string filename){
    init();
    ifstream inStream(filename);

    string line = " ";
    int points = 0;
    
    loadPlayerNames(inStream, line);
    loadPoints(inStream, points);

    inStream >> nextTurn;
    inStream >> line;

    loadFactoryZero(inStream, line);
    loadFactories(inStream, line);
    loadMosaic(inStream, line, player1);    
    loadMosaic(inStream, line, player2);
    loadStorageRows(inStream, line, player1);
    loadStorageRows(inStream, line, player2);
    loadBrokenStorage(inStream, line, player1);
    loadBrokenStorage(inStream, line, player2);
    
    inStream.close();
    printValues();
    enterGame();

}

void GameEngine::loadPlayerNames(istream& inStream, string line) {
    inStream >> line;
    player1->setName(line);
    inStream >> line;
    player2->setName(line);
}

void GameEngine::loadPoints(istream& inStream, int points){
    inStream >> points;
    player1->setPoints(points);
    inStream >> points;
    player2->setPoints(points);
}

void GameEngine::loadFactoryZero(istream& inStream, string strFactory) {
    getline(inStream, strFactory);
    factoryZero->clear();
    for(string::iterator c = strFactory.begin(); c != strFactory.end(); ++c){
        if(validChar(*c)){
            char tile = *c;
            factoryZero->addToFac(move(tile));
        }
    }
}

void GameEngine::loadFactories(istream& inStream, string strFactory){
    for(int i = 0; i < MAX_FACTORY_NUM; ++i){
        getline(inStream, strFactory);
        factories[i]->clear();
        for(string::iterator c = strFactory.begin(); c != strFactory.end(); ++c){
            if(validChar(*c)){
                char tile = *c;
                factories[i]->addToFactory(move(tile));
            }
        }
    }
}

void GameEngine::loadMosaic(istream& inStream, string line, shared_ptr<Player> player){
    for(int i = 0; i < MAX_MOSAIC_ROW_NUM; ++i){
        getline(inStream, line);
        player->getMosaic()->loadRow(i+1, line);
    }
}

void GameEngine::loadStorageRows(istream& inStream, string strStorage, shared_ptr<Player> player) {
     for(int i = 0; i < MAX_STORAGE_NUM; ++i){
        getline(inStream, strStorage);
        player->getStorageRow(i+1)->clearCompleteRow();
        for(string::iterator c = strStorage.begin(); c != strStorage.end(); ++c){
            if(validChar(*c)){
                char tile = *c;
                player->getStorageRow(i+1)->addTile(move(tile));
            }
        }   
    }
}

void GameEngine::loadBrokenStorage(istream& inStream, string strBroken, shared_ptr<Player> player){
    getline(inStream, strBroken);
    player->getBroken()->clearRow();
    for(string::iterator c = strBroken.begin(); c != strBroken.end(); ++c){
        if(validChar(*c)) {
            char tile = *c;
            player->getBroken()->addTile(move(tile));
        }
    }
}

bool GameEngine::validChar(char c) {
    bool valid = false;
    if(c == BLUE || c == YELLOW || c == RED || c == BLACK || c == LIGHT_BLUE || c == FIRST_PLAYER_MARKER || c == EMPTY){
        valid = true;
    }
    return valid;
}

void GameEngine::printValues() {

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

void GameEngine::enterGame(){
    bool completeRow = false;
    bool userExit = false;
    string turn = "";

    while(!userExit && !completeRow){

        // Set pointer to player whose turn it is
        if(nextTurn == player1->getName()){
            activePlayer = player1;
        }else{
            activePlayer = player2;
        }

        // Display the current status of the game
        cout << "TURN FOR PLAYER: " << activePlayer->getName() << endl;
        cout << "Factories: \n" << factoriesToString() << "\n" << endl;
        cout << activePlayer->getName() << "'s board:\n" <<
            activePlayer->boardToString() << endl;

        // Get a command from the player whose turn it is
        bool validCommand = false;
        while(!validCommand){
            turn = "";
            bool cmdShort = true;
            // Do not proceed until command is long enough
            while(cmdShort){
                cout << PROMPT;
                cin.ignore();
                getline(cin, turn);
                cmdShort = turn.length() < COMMAND_LENGTH;
                if(cmdShort){
                    cout << "Invalid action, please try again with one of the"
                            " following: \n" <<
                         "turn [factory: 0-5] [tile: R,Y,B,L,U,F] "
                         "[Row: 1-5, B]\n"
                         "save [filename] (ensure file exists)\n" <<
                         "exit" << endl;
                }
            }

            // Seperate input into command and argument
            string command = turn.substr(0, COMMAND_LENGTH);

            // Take action based on command and argument
            if(command == "turn")
            {
                validCommand = true;
                //seperate arguments into factory, tile and row
                int factory = command[COMIN_START_INDEX] - '0'; // Subtract '0' for ASCII conversion
                char tile = command[TILE_INDEX];
                char row = command[ROW_INDEX];
                if(validateTurn(factory, tile, row)){
                    performTurn(factory, tile, row);
                }
            }
            else if(command == "save")
            {
                validCommand = true;
                int inputLength = turn.length();
                string filename = turn.substr(COMMAND_LENGTH + 1,
                    inputLength - 1 - COMMAND_LENGTH);
                saveGame(filename);
            }
            else if(command == "exit")
            {
                validCommand = true;
                userExit = true;
            }
            else
            {
                cout << "Invalid action, please try again with one of the"
                        " following: \n" <<
                        "turn [factory: 0-5] [tile: R,Y,B,L,U,F] "
                        "[Row: 1-5, B]\n"
                        "save [filename] (ensure file exists)\n" <<
                        "exit" << endl;
            }
        }


    }

}

 void GameEngine::saveGame(string filename) {
    std::ofstream fileStream(filename);
    fileStream << player1->getName() << "\n"
               << player2->getName() << "\n"
               << player1->getPoints() << "\n"
               << player2->getPoints() << "\n"
               << nextTurn << "\n"
               << factoryZero->toString() << "\n";
    for(int i = 0; i < MAX_FACTORY_NUM; i++){
        fileStream << factories[i]->toString() << "\n";
    }
    fileStream << player1->getMosaic()->toString() << "\n"
               << player2->getMosaic()->toString() << "\n";
    for(int i = 0; i < MAX_STORAGE_NUM; i++){
        fileStream << player1->getStorageRow(i+1)->toString() << "\n";
    }
    for(int i = 0; i < MAX_STORAGE_NUM; i++){
        fileStream << player2->getStorageRow(i+1)->toString() << "\n";
    }
    fileStream << player1->getBroken()->toString() << "\n"
               << player2->getBroken()->toString();
    //TODO write box lid, bag and seed to file
    fileStream.close();
}

string GameEngine::factoriesToString(){
    string strFactories = "";
    strFactories += "0: " + factoryZero->toString() + "\n";
    for(int i = 0; i < MAX_FACTORY_NUM; i++){
        strFactories += std::to_string(i + 1) + ": " + factories[i]->toString();
        if(i != MAX_FACTORY_NUM - 1){
            strFactories += "\n";
        }
    }
    return strFactories;
}

bool GameEngine::validateTurn(int factory, char tile, char row) {
    // TODO implement
    /*
     * correct character length
     * factory in range
     * tile in range
     * row in range
     * factory has tile
     * row can accept tile (not occupied by diff colour, colour not already in mosaic for row
     */
    return false;
}

void GameEngine::performTurn(int factory, char tile, char row) {
    // Assumes the move is already validated

    // TODO implement
}



   
 

