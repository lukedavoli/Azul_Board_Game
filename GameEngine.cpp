#include <random>
#include <set>
#include "GameEngine.h"
#include <string>

GameEngine::GameEngine(){
    initialised = false;
    tileBag = make_shared<LinkedList>();
    possibleMoves = new string[POSSIBLE_MOVES];
}

GameEngine::~GameEngine(){
    deleteFactories();
    delete possibleMoves;
}

void GameEngine::deleteFactories(){
    for(int i = 0; i < MAX_FACTORY_NUM; ++i){
        delete factories[i];
    }
}

/**
 * Initialises modules of the game for loading in a file.
 *      Deletes factories if they have already been created on the heap.
 *      Creates players with no names and 0 points.
 *      Creates factories (empty).
 * */
void GameEngine::init(){
    if(initialised == true){
        deleteFactories();
    }
    initialised = true;
    string p1Name = " ";
    string p2Name = " ";
    player1 = make_shared<Player>(p1Name, INIT_POINTS);
    player2 = make_shared<Player>(p2Name, INIT_POINTS);
    factoryZero = make_shared<FactoryZero>();
    for(int i = 0; i < MAX_FACTORY_NUM; ++i){
        factories[i] = new Factory(i+1);
    }
}
/**
 * Initialises modules of the game for a new game.
 *      Prompts players to enter their names.
 *      Decides who begins first.
 *      Fills the boxlid, bag and factories.
 *      Starts the game.
 * */
void GameEngine::newGame(int seed, bool seedUsed){
    ai = false;
    std::string p1Name = "";
    std::string p2Name = "";
    std::cout << "Starting a New Game\n" << std::endl;
    std::cout << "Enter a name for \033[95;1mPlayer 1\033[0m" << std::endl;
    std::cout << PROMPT;
    std::cin >> p1Name;
    player1 = make_shared<Player>(p1Name, INIT_POINTS);
    std::cout << "Enter a name for \033[96;1mPlayer 2\033[0m" << std::endl;
    std::cout << PROMPT;
    std::cin >> p2Name;
    player2 = make_shared<Player>(p2Name, INIT_POINTS);

    std::cout << "\nWho most recently visited Portugal? 💚🔴\n" <<
                 "[1] \033[95;1m" << p1Name << "\033[0m" << "\n" <<
                 "[2] \033[96;1m" << p2Name << "\033[0m" << endl;
          
    char mostRecent =  ' ';
    std::cout << PROMPT;
    std::cin >> mostRecent;
    while(!cin.good() || (mostRecent != '1' && mostRecent != '2')) {
        std::cout <<  "Please enter an integer (1) or (2)." << endl;
        std::cout << PROMPT;
        mostRecent = ' ';
        std::cin >> mostRecent;
    }
    if(mostRecent == '1'){
        nextTurn = p1Name;
    } else{
        nextTurn = p2Name;
    }
    fillBoxLid();
    if(seedUsed){
        fillBagFromBoxSeed(seed);
    }else{
        fillBagFromBox();
    }
    factoryZero = make_shared<FactoryZero>();
    for(int i = 0; i < MAX_FACTORY_NUM; ++i){
        factories[i] = new Factory(i+1);
    }
    fillFactories();
    std::cout << "\n\033[95;1m" << player1->getName() << "\033[0m and " 
              << "\033[96;1m" << player2->getName() << "\033[0m" <<
                 ", Let's Play!\n" << std::endl;
    enterGame();
}

void GameEngine::newGameSP(int seed, bool seedUsed){
    ai = true;
    generatePossibleMoves();
    std::string p1Name = "";
    std::string p2Name = "AzulBot🤖";
    std::cout << "Starting a New Game\n" << std::endl;
    std::cout << "Enter a name for \033[95;1mPlayer 1\033[0m" << std::endl;
    std::cout << PROMPT;
    std::cin >> p1Name;
    player1 = make_shared<Player>(p1Name, INIT_POINTS);
    player2 = make_shared<Player>(p2Name, INIT_POINTS);

    nextTurn = p1Name;
    fillBoxLid();
    if(seedUsed){
        fillBagFromBoxSeed(seed);
    }else{
        fillBagFromBox();
    }
    factoryZero = make_shared<FactoryZero>();
    for(int i = 0; i < MAX_FACTORY_NUM; ++i){
        factories[i] = new Factory(i+1);
    }
    fillFactories();
    std::cout << "\n\033[95;1m" << player1->getName() << "\033[0m and " << 
                 "\033[96;1m" << player2->getName() << "\033[0m" <<
                 ", Let's Play!\n" << std::endl;
    enterGame();
}

/**
 * Loads in a save file.
 *      Loads in the data line by line.
 *      Prints the data that was loaded in.
 * */
void GameEngine::loadGame(string filename){
    init();
    ifstream inStream(filename);
    string line = " ";
    int points = 0;
    std::string gametype = "";
    
    loadPlayerNames(inStream, line);
    loadPoints(inStream, points);
    inStream >> nextTurn;
    getline(inStream, line);
    loadFactoryZero(inStream, line);
    loadFactories(inStream, line);
    loadMosaic(inStream, line, player1);    
    loadMosaic(inStream, line, player2);
    loadStorageRows(inStream, line, player1);
    loadStorageRows(inStream, line, player2);
    loadBrokenStorage(inStream, line, player1);
    loadBrokenStorage(inStream, line, player2);
    loadBoxLid(inStream, line);
    loadBag(inStream, line);
    inStream >> seed;
    inStream >> gametype;
    if(gametype == "sp"){
        ai = true;
        generatePossibleMoves();
    }else{
        ai = false;
    }
    
    inStream.close();
    cout << "\"" << filename << "\"" << " loaded successfully!" << endl;
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
        for(string::iterator c = strFactory.begin();
            c != strFactory.end(); ++c){
            if(validChar(*c)){
                char tile = *c;
                factories[i]->addToFactory(move(tile));
            }
        }
    }
}

void GameEngine::loadMosaic(istream& inStream, string line,
                            shared_ptr<Player> player){
    for(int i = 0; i < MAX_MOSAIC_ROW_NUM; ++i){
        getline(inStream, line);
        player->getMosaic()->loadRow(i+1, line);
    }
}

void GameEngine::loadStorageRows(istream& inStream, string strStorage,
                                 shared_ptr<Player> player) {
     for(int i = 0; i < MAX_STORAGE_NUM; ++i){
        getline(inStream, strStorage);
        player->getStorageRow(i+1)->clearCompleteRow();
        for(string::iterator c = strStorage.begin();
            c != strStorage.end(); ++c){
            if(validStorageChar(*c)){
                char tile = *c;
                player->getStorageRow(i+1)->addTile(move(tile));
            }
        }   
    }
}

void GameEngine::loadBrokenStorage(istream& inStream, string strBroken,
                                   shared_ptr<Player> player){
    getline(inStream, strBroken);
    player->getBroken()->clearRow();
    for(string::iterator c = strBroken.begin(); c != strBroken.end(); ++c){
        if(validChar(*c)) {
            char tile = *c;
            player->getBroken()->addTile(move(tile));
        }
    }
}

void GameEngine::loadBag(istream& inStream, string strBag) {
    getline(inStream, strBag);
    tileBag->clear();
    for(string::iterator c = strBag.begin(); c != strBag.end(); ++c){
        if(validChar(*c)){
            char tile = *c;
            tileBag->addBack(move(tile));
        }
    }
}

void GameEngine::loadBoxLid(istream& inStream, string strLid){
    getline(inStream, strLid);
    int index = 0;
    boxLid.fill('\0');
    for(string::iterator c = strLid.begin(); c != strLid.end(); ++c){
        if(validChar(*c)){
            boxLid[index] = *c;
            ++index;
        }
    }
}

bool GameEngine::validChar(char c) {
    bool valid = false;
    if(c == BLUE || c == YELLOW || c == RED || c == BLACK || c == LIGHT_BLUE ||
       c == FIRST_PLAYER_MARKER || c == EMPTY){
        valid = true;
    }
    return valid;
}

bool GameEngine::validStorageChar(char c) {
    bool valid = false;
    if(c == BLUE || c == YELLOW || c == RED || c == BLACK || c == LIGHT_BLUE) {
        valid = true;
    }
    return valid;
}

/**
 * enterGame():
 *  If the factories are empty 
 *       Proceed to move tiles and score and display the player's board.
 *       Refill the factories if the tile bag is empty.
 *       Otherwise refill the bag first, then the factories. 
 */
void GameEngine::enterGame(){
    bool completeRow = false;
    bool userExit = false;
    bool validCommand = false;
    bool cmdShort = true;
    bool firstLoop = true;
    string turn = "";

   // Continues in loop until end of round.
    while(!userExit && !completeRow){
        setActivePlayer();
        displayTurnUpdate();
        validCommand = false;
        // Continue in loop until user exits game or command is valid.
        while(!validCommand && !userExit){
            cmdShort = true;
            turn = "";
            // Do not proceed until the command is long enough to be valid.
            while (cmdShort && !userExit){
                cout << PROMPT;
                if(nextTurn != "AzulBot🤖" || !ai){
                    if(firstLoop){
                        getline(cin, turn);
                        firstLoop = false;
                    }
                    getline(cin, turn);
                }else{
                    turn = aiTurn();
                    cout << turn << endl;
                }
                if(cin.eof()){
                    userExit = true;
                }else{
                    cmdShort = turn.length() < COMMAND_LENGTH;
                    if(cmdShort){
                        cout << "\n\033[31;1mInvalid action, please try again "
                                "with one of the following: \n" <<
                                "- turn [factory: 0-5] [tile: R,Y,B,L,U,F] "
                                "[Row: 1-5, B]\n"
                                "- show\n"
                                "- save [filename] (ensure file exists)\n" <<
                                "- exit\033[0m" << endl;
                    }
                }
            }
            // Skip if user has chosen to exit.
            if(!userExit){
                // Take action based on command and argument.
                string command = turn.substr(0, COMMAND_LENGTH);
                int turnLength = turn.length();
                if(turn[turnLength - 1] == '\r'){
                    turn = turn.substr(0, turn.length() - 1);
                }
                if (command == "turn" && turn.length() == TURN_COMMAND_LENGTH){
                    // Seperate arguments into factory, tile and row.
                    char factoryChar = turn[5];
                    char tile =   turn[7];
                    char row =  turn[9];
                    int factory = -1;
                    if(validateTurn(factoryChar, tile, row, &factory)) {
                        validCommand = true;
                        if (this->nextTurn.compare(player1->getName())==0){
                            performTurn(player1, factory, tile, row);
                            nextTurn = player2->getName();
                        } else {
                            performTurn(player2,factory, tile, row);
                            nextTurn = player1->getName();
                        }
                        if(emptyFactories()){
                            cout << "\n------------\n" <<
                                    "END OF ROUND\n" <<
                                    "------------\n" << endl;
                            if(player1->getBroken()->hasFirstPlayerMarker()){
                                nextTurn = player1->getName();
                            }else{
                                nextTurn = player2->getName();
                            }
                            moveTilesAndScore(player1);
                            moveTilesAndScore(player2);
                            cout << endl;
                            cout << player1->getName() << "'s Board" << endl;
                            cout << player1->boardToString() << endl;
                            cout << "\n";
                            cout << player2->getName() << "'s Board" << endl;
                            cout << player2->boardToString() <<  endl;
                            cout << "\n--------------------------------" << endl;
                            factoryZero->reset();
                            if(tileBag->size() >= MIN_BAG_TILES) {
                                fillFactories();
                            } else {
                                fillBagSequentially();
                                fillFactories();
                            }
                            completeRow = endGame(); 
                            if(completeRow){
                                bonusPoints(player1);
                                bonusPoints(player2);
                                displayWinner();
                            }    
                        }
                    } else {
                        cout << "You can't perform that move, try again..." <<
                                endl;
                    }
                }else if (command == "save") {
                    validCommand = true;
                    int inputLength = turn.length();
                    string filename = turn.substr(COMMAND_LENGTH + 1,
                                                  inputLength - 1 -
                                                  COMMAND_LENGTH);
                    int filenameLength = filename.length();
                    if(filename[filenameLength - 1] == '\r'){
                        filename = filename.substr(0, filenameLength - 1);
                    }
                    saveGame(filename);
                    cout << "Game saved." << endl;
                }else if(command == "exit"){
                    cout << "\n" << endl;
                    validCommand = true;
                    userExit = true;
                }else if(command == "show"){
                    if(nextTurn == player1->getName()){
                        cout << "\n\033[96;1m" << player2->getName() << "'s\033[0m's board:" << endl;
                        cout << player2->boardToString() << endl;
                    }else{
                        cout << "\n\033[95;1m" << player1->getName() << "'s\033[0m's board:" << endl;
                        cout << player1->boardToString() << endl;
                    }     
                }else if(command == "help"){
                    cout << "\n\033[93mPlease use one of the following commands...\n" <<
                         "- turn [factory: 0-5] [tile: R,Y,B,L,U,F] "
                         "[Row: 1-5, B] (performs a turn in the game)\n"
                         "- show (displays the opponents board to inform"
                         " strategic decision making)\n"
                         "- save [filename] (saves the current game to file)\n" 
                         "- exit (leaves the game to the main menu"
                         " without saving)\n" <<
                         "For a refresher of the rules, click the link below:\033[0m\n"
                         "\033[34;1mhttps://www.ultraboardgames.com/azul/game-rules.php\033[0m" << endl;
                } else {
                    cout << "\n\033[31;1mInvalid action, please try again with"
                            " one of the following: \n" <<
                         "- turn [factory: 0-5] [tile: R,Y,B,L,U,F] "
                         "[Row: 1-5, B]\n"
                         "- show\n"
                         "- save [filename] (ensure file exists)\n" <<
                         "- exit\033[0m" << endl;
                }
            }
        }
    }
}

void GameEngine::displayWinner() {
    cout << "\nEND OF GAME" << endl;
    if(player1->getPoints() > player2->getPoints()){
        cout << "\033[95;1m" << player1->getName() << "\033[0m Wins!" << endl;
    } else {
        cout << "\033[96;1m" << player2->getName() << "\033[0m Wins!" << endl;
    }
    cout << "\033[95;1m" << (*player1).getPoints() << " - " << 
            player1->getName() << "\033[0m" << endl;
    cout << "\033[96;1m" << (*player2).getPoints() << " - " << 
                player2->getName() << "\033[0m" << endl;
}

bool GameEngine::endGame() {
    bool end = false;
    if(completeMosaic(player1) || completeMosaic(player2)) {
        end = true;
    }
    return end;
}

void GameEngine::bonusPoints(shared_ptr<Player> player){
    int countRow=0;
    int countCol=0;
    int countBlue=0;
    int countBlack=0;
    int countYellow=0;
    int countRed=0;
    int countLB=0;
    int bonusPoints=0;

    for (int i = 0; i < MAX_MOSAIC_COL_NUM; i++){
        countRow=0;
        for (int j = 0; j < MAX_MOSAIC_ROW_NUM; j++){
            if(player->getMosaic()->
               validTile(player->getMosaic()->get2DMosaic()[j][i])){
                countRow++;
            }
            if (countRow==5){
              bonusPoints+=7;
            } 
        }
    }
    for (int i = 0; i < MAX_MOSAIC_ROW_NUM; i++){
        countCol=0;
        for (int j = 0; j < MAX_MOSAIC_COL_NUM; j++){
            if(player->getMosaic()->
               validTile(player->getMosaic()->get2DMosaic()[i][j])){
                countCol++;
            }
            if (player->getMosaic()->get2DMosaic()[i][j]==BLACK){
               countBlack++;
            }
            if (player->getMosaic()->get2DMosaic()[i][j]==YELLOW){
               countYellow++;
            }
            if (player->getMosaic()->get2DMosaic()[i][j]==BLUE){
               countBlue++;
            }
            if (player->getMosaic()->get2DMosaic()[i][j]==LIGHT_BLUE){
               countLB++;
            }
            if (player->getMosaic()->get2DMosaic()[i][j]==RED){
               countRed++;
            }   
            if (countCol==5){
                bonusPoints+=2;
            }
        }
    }

    if(countBlack==5){
        bonusPoints+=10;
    }
    if(countBlue==5){
        bonusPoints+=10;
    }
    if(countLB==5){
        bonusPoints+=10;
    }
    if (countRed==5){
        bonusPoints+=10;
    }
    if (countYellow==5){
        bonusPoints+=10;
    }
    int prevScore= player->getPoints();
    player->setPoints(prevScore+bonusPoints);
}

bool GameEngine::completeMosaic(shared_ptr<Player> player) {
   bool completed = false;
    if(completeRow(player)){
       completed = true;
    }
   return completed;
}

bool GameEngine::completeRow(shared_ptr<Player> player){
    bool completed = false;
    int counter = 0;
    for(int row = 0; row < MAX_MOSAIC_ROW_NUM; ++row){
        counter = 0;
        for(int col = 0; col < MAX_MOSAIC_COL_NUM; ++col){
            char tile = player->getMosaic()->get2DMosaic()[row][col];
            checkRow(tile, &completed, &counter, &row, &col);
        }
    }
    return completed;
}

void GameEngine::checkRow(char tile, bool* completed, int* counter, 
                          int* row, int* col){
    if(tile == toupper(tile)){
        (*counter)++;
    }
    if(*counter == MAX_MOSAIC_COL_NUM) {
        *completed = true;
        *col = MAX_MOSAIC_COL_NUM;
        *row = MAX_MOSAIC_ROW_NUM;
    }
}

/**
 *  Moving tiles at the end of round.
 *  Under the assumption that all factories are empty. 
 * */
void GameEngine::moveTilesAndScore(shared_ptr<Player> player) {
    for(int j = 0; j < MAX_STORAGE_NUM; ++j){
        int rowNum = j+1;
        if(player->getStorageRow(rowNum)->isFull()) {
            char tile = player->getStorageRow(rowNum)->getOccupyingColour();
            player->getMosaic()->insertRow(rowNum, tile);
            score(player,rowNum,tile);
            moveStorageTilesToBox(rowNum, tile);
            player->getStorageRow(rowNum)->clearCompleteRow();
        }
    }
    brokenScore(player);
    if(player->getBroken()->getLength() > 0){
        moveBrokenTilesToBox(player);
        player->getBroken()->clearRow();
    }
}

/**
 * Moving excess tiles from full storage rows into the box.
 * Under the assumption that the row is full. 
 * */
void GameEngine::moveStorageTilesToBox(int rowNum, char tile){
    for(int i = 0; i != rowNum - 1; ++i){
       int lastIndex = getNumOfBoxTiles();
       boxLid[lastIndex] = tile;
    }
}

 // Move Broken Storage tiles to box.
void GameEngine::moveBrokenTilesToBox(shared_ptr<Player> player){
    for(int i = 0; i != player->getBroken()->getLength(); ++i){
        char tile = player->getBroken()->getTileAt(i);
        if(tile != FIRST_PLAYER_MARKER){
            int lastIndex= getNumOfBoxTiles();
            boxLid[lastIndex] = tile;
        }
    }
}

/**
 * Move tiles from the box to the bag.
 * Under the assumption that the bag is empty and the box is full. 
 * */
void GameEngine::fillBagSequentially() {
    int index = 0;
    while(boxLid.at(index) != '\000'){
        char tile = boxLid.at(index);
        tileBag->addFront(std::move(tile));
        ++index;
    }
    boxLid.fill('\000');
}

int GameEngine::getNumOfBoxTiles() {
    int count = 0;
    while(boxLid[count] != '\0'){
        ++count;
    }
    return count;
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
        fileStream << player1->getStorageRow(i+1)->toStringBackwards() << "\n";
    }
    for(int i = 0; i < MAX_STORAGE_NUM; i++){
        fileStream << player2->getStorageRow(i+1)->toStringBackwards() << "\n";
    }
    fileStream << player1->getBroken()->toString() << "\n"
               << player2->getBroken()->toString() << "\n";
    fileStream << boxLidToString() << "\n"
               << tileBagToString() << "\n"
               << seed << "\n";
    if(ai){
        fileStream << "sp";
    }else{
        fileStream << "mp";
    }
    fileStream.close();
}

string GameEngine::factoriesToString(){
    string strFactories = "";
    strFactories += "0: " + factoryZero->toStringColour() + "\n";
    for(int i = 0; i < MAX_FACTORY_NUM; i++){
        strFactories += std::to_string(i + 1) + ": " + factories[i]->toStringColour();
        if(i != MAX_FACTORY_NUM - 1){
            strFactories += "\n";
        }
    }
    return strFactories;
}

bool GameEngine::validFactoryChar(char c, int* factoryNumber){
    bool valid = false;
    char validChars[MAX_FACTORY_NUM + 1] = {'0', '1', '2', '3', '4', '5'};
    for(int i = 0; i <= MAX_FACTORY_NUM; ++i){
        if(c == validChars[i]){
            valid = true;
            *factoryNumber = i;
        }
    }
    return valid;
}

bool GameEngine::validateTurn(char factChar, char tile, char row, int* factoryN) {
    char checkTile1=tile;
    char checkTile2=tile;
    bool validTurn = false;
    bool validInput=false;
    bool exists=false;
    if(validFactoryChar(factChar, factoryN)) {
        if(tile==RED || tile==YELLOW || tile==BLACK || tile== BLUE ||
        tile==LIGHT_BLUE){
            if(*factoryN>=0 && *factoryN<=5) {
                if(row=='1' || row=='2' || row=='3' || row=='4' || row=='5' ||
                row=='B'){
                    validInput=true;
                }
            }
        }
        if(*factoryN ==0 ){
            if (validInput && 
                (*factoryZero).getNumOfCoulour(std::move(checkTile1)) > 0){
            exists=true;
            }
        }
        if(*factoryN>0 && 
            (*factories[*factoryN-1]).getNumberOfColour(std::move(checkTile2))>0){
            exists=true;
        }
        if(exists){
            if((row != BROKEN_ROW &&
                validTileInRow(tile, row)) || (row == BROKEN_ROW)) {
                validTurn = true;
            }
        }
    }
    return validTurn;
}


bool GameEngine::validRowChar(char rowChar, int* row){
    bool valid = false;
    char validStorageRow[MAX_STORAGE_NUM] =  {'1','2','3','4','5'};
    for (int i = 0; i < MAX_STORAGE_NUM; i++) {
        if(rowChar == validStorageRow[i]){
            valid = true;
            *row = i+1;
            i = MAX_STORAGE_NUM;
        }
    }
    return valid;
}


bool GameEngine::validTileInRow(char tile, char storageRow){
    bool valid=false;
    bool exists = false;
    int rowNum = 0;

    if(validRowChar(storageRow, &rowNum)) {
        if(this->nextTurn.compare(player1->getName())==0) {
            for (int i = 0; i < 9; i+=2){
                if (player1->getMosaic()->getRow(rowNum)[i]==tile){
                    exists=true;
                }  
            }
            if (!exists && !player1->getStorageRow(rowNum)->isFull()){
                if (player1->getStorageRow(rowNum)->getOccupied()==0){
                    valid=true;
                }else if(player1->getStorageRow(rowNum)->
                         getOccupyingColour()==tile){
                    valid=true;
                }
            }

        } else {
            for (int i = 0; i < 9; i+=2){
                if (player2->getMosaic()->getRow(rowNum)[i]==tile) {
                    exists=true;
                } 
            }
            if (!exists && !player2->getStorageRow(rowNum)->isFull()){
                if (player2->getStorageRow(rowNum)->getOccupied()==0){
                    valid=true;
                } else if (player2->getStorageRow(rowNum)->
                           getOccupyingColour()==tile){
                    valid=true;
                }
            }
        }
    }

    return valid;
}
// This method will perform the turn assuming that the turn is valid.
// It will check in which row we want to add the tiles from the factories.
// Then it would remove the spefied colour from the factory , the rest will
// be added in the factory zero. Then it will add the as many tiles as can 
//fit in the row the rest would be added in ht ebroker row of the player.
void GameEngine::performTurn(shared_ptr<Player> player,int factoryN,
                             char tile, char row) {
    int r = 0;
    validRowChar(row, &r);
    char tileE= tile;
    char tileA=tile;
    char Fp='F';
    int timesInZ=(*factoryZero).getNumOfCoulour(std::move(tileE));

    if(row == BROKEN_ROW)
    {
        char test10=tile;
        char test12=tile;
        if(factoryN==0 ){
            int s1= (*factoryZero).getNumOfCoulour(std::move(test12));
            for (int i = 0; i <s1 ; i++){
                char test20=tile;
                player->getBroken()->addTile(std::move(test20));
            }
            (*factoryZero).removeTile(std::move(test10));
            if((*factoryZero).getNumOfCoulour('F')==1) {
                player->getBroken()->addTile(std::move('F'));
                (*factoryZero).removeTile(std::move('F'));
            }
        } else {
            int s = (*factories[factoryN-1])
                    .getNumberOfColour(std::move(test12));
            for (int i = 0; i <s ; i++){
                char test20=tile;
                player->getBroken()->addTile(std::move(test20));
            }
            for (int i = 0; i < s; i++){
                char test15=tile;
                (*factories[factoryN-1]).removeTile(move(test15),factoryZero);
            }
        }
    } else if(row != BROKEN_ROW){
        int avLength = r-player->getStorageRow(r)->getLength();
        if(factoryN==0 && row!='B') {
            if(timesInZ<=avLength){
                char test3=tile;
                for (int i = 0; i < timesInZ; ++i){
                    char test=tile;
                    player->getStorageRow(r)->addTile(std::move(test));
                }
                if ((*factoryZero).getNumOfCoulour(std::move(Fp))==1){
                    player->getBroken()->addTile(std::move('F'));
                    (*factoryZero).removeTile(std::move('F'));
                }
                (*factoryZero).removeTile(std::move(test3));
            } else {
                char test4=tile;
                for (int i = 0; i < avLength; ++i){
                    char test =tile;
                    player->getStorageRow(r)->addTile(std::move(test));
                }
                for (int i = 0; i < (timesInZ-avLength); ++i){
                    char test10 =tile;
                    player->getBroken()->addTile(std::move(test10));
                }
                if ((*factoryZero).getNumOfCoulour('F')==1) {
                    player->getBroken()->addTile(std::move('F'));
                    (*factoryZero).removeTile(std::move('F'));
                }
                (*factoryZero).removeTile(std::move(test4));
            }

        } else if(row!='B'){
            char test5 = tile;
            int  timesInF=(*factories[factoryN-1])
                          .getNumberOfColour(std::move(tileA));
            if(timesInF<=avLength){
                for (int i = 0; i < timesInF; ++i){
                    char test = tile;
                    player->getStorageRow(r)->addTile(std::move(test));
                }
                (*factories[factoryN - 1])
                .removeTile(std::move(test5),factoryZero);
            } else {
                char test2=tile;
                for (int i = 0; i < avLength; i++){
                    char test = tile;
                    player->getStorageRow(r)->addTile(std::move(test));
                }
                for (int i = 0; i <(timesInF- avLength); i++){
                    char test=tile;
                    player->getBroken()->addTile(std::move(test));
                }
                (*factories[factoryN-1])
                .removeTile(std::move(test2), factoryZero);
            }
        }
    }
}

bool GameEngine::emptyFactories(){
    bool empty=false;
    if((*factoryZero).getSize()==0 ){
        for (int i = 0; i < MAX_FACTORY_NUM; i++){
            if (factories[i]->isClear()){
               empty=true;
            } else {
                empty=false;
                i = MAX_FACTORY_NUM;
            }
        }
    }
    return empty;
}
// This method counts by how many points the playes points should be augmented.
// Checks how many tiles are connected with the tile added in this round   
// and calculates the points.   
void GameEngine::score(shared_ptr<Player> player,int row,char tile){
    shared_ptr<Mosaic> m=player->getMosaic();
    int x=0;
    for (int n = 0; n < 5; n++){
        if (m->get2DMosaic()[row-1][n]==tile){
            x=n;
        }
    }

    int begginingX=x;
    // This set of booleans are for checking if the searching is in bounds.
    bool CANgU=true;
    bool CANgD=true;
    bool CANgR=true;
    bool CANgL=true;
    //This set of bolleans are for checking if the tile is connected.
    bool hadUp=false;
    bool hadRight=false;
    bool hadDown=false;
    bool hadLeft=false;
    int beggingY =row-1;
    int score=0;
       
    if ((beggingY-1)<0 ){
        CANgU=false;
    }
    if ((beggingY+1)>4 ){
        CANgD=false;
    }
    if ((begginingX-1)<0 ){
        CANgL=false;
    }
    if ((begginingX+1)>4){
        CANgR=false;
    }       
    //This set of loops check at each dierection of the tiles to find the connected tiles.
    //Checks North
    while ( CANgU ){     
        if(beggingY>0 &&
           m->validTile(m->get2DMosaic()[beggingY-1][begginingX])){
            hadUp=true;
            beggingY--;
            score++;
        } else {
            beggingY=row-1;
            begginingX=x;
            CANgU=false;
        }
    }
    //Checks East
    while ( CANgR ){
        if (begginingX < 4 &&
            m->validTile(m->get2DMosaic()[beggingY][begginingX+1])){
            hadRight=true;
            begginingX++;
            score++;
        } else {
            beggingY=row-1;
            begginingX=x;
            CANgR=false;
        }
    }
    //Checks South
    while (CANgD){
        if ((beggingY) < 4 && 
            m->validTile(m->get2DMosaic()[beggingY+1][begginingX])){
            hadDown=true;
            beggingY++;
            score++;
        } else {
            beggingY=row-1;
            begginingX=x;
            CANgD=false;
        }
    }
    //Checks West
    while (CANgL) {     
        if(begginingX > 0 &&
           m->validTile(m->get2DMosaic()[beggingY][begginingX-1])){
            hadLeft=true;
            begginingX--;
            score++;
        } else {
            beggingY=row-1;
            begginingX=x;
            CANgL=false;
        }
    }
    if (hadUp==true || hadDown==true){
        score++;
    }
    if (hadRight==true || hadLeft==true){
        score++;
    }
    if(hadUp==false && hadDown==false && hadRight ==false && hadLeft==false){
        score++;
    }    
    int prevS=(*player).getPoints();
    (*player).setPoints(prevS+score);
}

// This method calculates the points the player will loose.
// Depending on how many tiles the player has on the broken row.
void GameEngine::brokenScore(shared_ptr<Player> player){
    int brokenScore[MAX_BROKEN_TILES] = {-1, -2, -4, -6, -8, -11, -14};
    int prevScore = (*player).getPoints();
    int lostPoints=0;
    for(int i = 0; i != MAX_BROKEN_TILES; ++i){
        if(player->getBroken()->getLength() == i+1) {
            lostPoints = brokenScore[i];
        }
    }
    if (prevScore+lostPoints < 0) {
        (*player).setPoints(0);
    } else {
        (*player).setPoints(prevScore+lostPoints);
    }
    if(player->getName() == player1->getName()){
        cout << "\033[95;1m" << (*player).getPoints() << " - " << 
                player1->getName() << "\033[0m" << endl;
    }else{
        cout << "\033[96;1m" << (*player).getPoints() << " - " << 
                player2->getName() << "\033[0m" << endl;
    }
    
}

/**
 * fillBoxlid():
 *   Iterate from 0 to 100, adding a different colour tile each step of 20.
 * */
void GameEngine::fillBoxLid() {
   
    for(int i = 0; i < TOTAL_TILES; i++){
        char nextTile = ' ';
        if(i <= LAST_B_TILE){
            nextTile = BLUE;
            boxLid[i] = std::move(nextTile);
        }else if(i <= LAST_L_TILE){
            nextTile = LIGHT_BLUE;
            boxLid[i] = std::move(nextTile);
        }else if(i <= LAST_U_TILE){
            nextTile = BLACK;
            boxLid[i] = std::move(nextTile);
        }else if(i <= LAST_R_TILE){
            nextTile = RED;
            boxLid[i] = std::move(nextTile);
        }else if(i <= LAST_Y_TILE){
            nextTile = YELLOW;
            boxLid[i] = std::move(nextTile);
        }
    }
}


/* 
* fillBagFromBoxSeed():
*     Continue while bag not full
*        Randomly select an index of the box to add to the bag
*        Check to see if that index has already been selected
*        If not, add the tile to the front of the bag
*     Clear the boxlid.
*/
void GameEngine::fillBagFromBoxSeed(int seed) {
    std::uniform_int_distribution<int> uniform_dist(0, TOTAL_TILES - 1);
    std::default_random_engine engine(seed);
    std::set<int> selected;
    while(tileBag->size() != TOTAL_TILES){
        int index = uniform_dist(engine);
        if(selected.find(index) == selected.end()){
            tileBag->addFront(std::move(boxLid.at(index)));
            selected.insert(index);
        }
    }
    boxLid.fill('\0');
}


/*
* fillBagFromBox():
*   Continue will bag not full
*      Randomly select an index of the box to add to the bag
*      Check to see if that index has already been selected
*      If not, add the tile to the front of the bag.
*    Clear box lid.
*/

void GameEngine::fillBagFromBox() {
    std::uniform_int_distribution<int> uniform_dist(0, TOTAL_TILES - 1);
    std::random_device engine;
    std::set<int> selected;
    while(tileBag->size() != TOTAL_TILES){
        int index = uniform_dist(engine);
        if(selected.find(index) == selected.end()){
            tileBag->addFront(std::move(boxLid.at(index)));
        }
    }
    boxLid.fill('\0');
}

void GameEngine::fillFactories() {
    for(int i = 0; i < MAX_FACTORY_NUM; ++i){
        for(int t = 0; t < NUM_OF_TILES; t++){
            factories[i]->setTile(t, std::move(tileBag->get(0)));
            tileBag->removeFront();
        }
    }
}

// Compare the name of the current active player, switch to opposite
void GameEngine::setActivePlayer() {
    if(nextTurn == player1->getName()){
        activePlayer = player1;
    }else{
        activePlayer = player2;
    }
}

void GameEngine::displayTurnUpdate() {
    if(nextTurn == player1->getName()){
        cout << "\n\033[95;1m" << player1->getName() << "'s\033[0m turn..." << endl;
        cout << "Factories: \n" << factoriesToString() << "\n" << endl;
        cout << "\n\033[95;1m" << activePlayer->getName() << "'s\033[0m board:\n" <<
        activePlayer->boardToString() << endl;
    }else{
        cout << "\n\033[96;1m" << player2->getName() << "'s\033[0m turn..." <<endl;
        cout << "Factories: \n" << factoriesToString() << "\n" << endl;
        cout << "\n\033[96;1m" << activePlayer->getName() << "'s\033[0m board:\n" <<
        activePlayer->boardToString() << endl;
    }
}

string GameEngine::boxLidToString(){
    string strBoxLid = "";
    int i = 0;
    while(boxLid[i] != '\0'){
        strBoxLid += boxLid[i];
        if((i + 1) != '\0'){
            strBoxLid += " ";
        }
        ++i;
    }
    return strBoxLid;
}

string GameEngine::tileBagToString(){
    string strBag = "";
    int size = tileBag->size();
    for (int i = 0; i < size; i++) {
        strBag += tileBag->get(i);
        if(i != size - 1){
            strBag += " ";
        }
    }
    return strBag;
}

string GameEngine::aiTurn(){
    string chosenTurn = "no turn found";
    findValidMoves();
    chosenTurn = findBestMove();
    return chosenTurn;
}

void GameEngine::generatePossibleMoves(){
    int i = 0;
    for(int f = 0; f <= MAX_FACTORY_NUM; f++){
        for(int t = 0; t < TILES; t++){
            for(int s = 1; s <= MAX_STORAGE_NUM + 1; s++){
                string turn = "turn ";
                turn += std::to_string(f) + " ";
                if(t == 0){
                    turn += "B ";
                }else if(t == 1){
                    turn += "Y ";
                }else if(t == 2){
                    turn += "R ";
                }else if(t == 3){
                    turn += "U ";
                }else if(t == 4){
                    turn += "L ";
                }
                if(s != 6){
                    turn += std::to_string(s);
                }else{
                    turn += "B";
                }
                possibleMoves[i] = turn;
                i++;
            }
        }
    }
}

void GameEngine::findValidMoves(){
    validMoves.clear();
    for(int m = 0; m < POSSIBLE_MOVES; m++){
        string turn = possibleMoves[m];
        char factoryChar = turn[5];
        char tile = turn[7];
        char row = turn[9];
        int factory = -1;
        if(validateTurn(factoryChar, tile, row, &factory)){
            validMoves.push_back(turn);
        }
    }
}

string GameEngine::findBestMove(){
    int totalValidMoves = validMoves.size();
    std::vector<string> movesToConsider;
    int moveLevel = 0;
    bool directBroken = false;

    //iterate through all moves that are currently valid
    for(int m = 0; m < totalValidMoves; m++){
        //Get the details of the next move
        string turn = validMoves.at(m);
        char factoryChar = turn[5];
        int factoryNum = factoryChar - '0';
        char tile = turn[7];
        char row = turn[9];
        int rowNum = -1;
        int rowCapacity = 0;
        int currRowSize;
        int tilesToAdd;
        if(factoryChar == '0'){
            tilesToAdd = factoryZero->getNumOfCol(tile);
        }else{
            tilesToAdd = factories[factoryNum - 1]->getNumberOfCol(tile);
        }

        if(row != 'B'){
            rowNum = row - '0';
            currRowSize = activePlayer->getStorageRow(rowNum)->getOccupied();
            rowCapacity = activePlayer->getStorageRow(rowNum)->getMaxTiles();
            
            //Identify what outcome the move will have and choose whether or not to consider it accordingly
            //level 5 move: perfectly fills a row
            if(currRowSize + tilesToAdd == rowCapacity){
                if(moveLevel < 5){
                    movesToConsider.clear();
                    moveLevel = 5;
                    directBroken = false;
                }
                movesToConsider.push_back(turn);
            //level 4 move: fills a row to 1 less than capacity
            }else if(currRowSize + tilesToAdd == rowCapacity - 1 && moveLevel < 5){
                if(moveLevel < 4){
                    movesToConsider.clear();
                    moveLevel = 4;
                    directBroken = false;
                }
                movesToConsider.push_back(turn);
            //level 3 move: fills a row to 1 over capacity
            }else if(currRowSize + tilesToAdd == rowCapacity + 1 && moveLevel < 4){
                if(moveLevel < 3){
                    movesToConsider.clear();
                    moveLevel = 3;
                    directBroken = false;
                }
                movesToConsider.push_back(turn);
            //level 2 move: fills a row to 2 or more below capacity
            }else if(currRowSize + tilesToAdd < rowCapacity - 1 && moveLevel < 3){
                if(moveLevel < 2){
                    movesToConsider.clear();
                    moveLevel = 2;
                    directBroken = false;
                }
                movesToConsider.push_back(turn);
            //level 1 move: fills a row to 2 or more above capacity
            }else if(currRowSize + tilesToAdd > rowCapacity + 1 && moveLevel < 2){
                if(moveLevel < 1){
                    movesToConsider.clear();
                    moveLevel = 1;
                    directBroken = false;
                }
                movesToConsider.push_back(turn);
            }
        }
        //level 0 move: moves tiles directly to broken row
        if(row == 'B' && moveLevel < 1){
            directBroken = true;
            movesToConsider.push_back(turn);
        }
    }
    
    /*
    * Go through all moves to consider, if a move can be played to a row,
    * choose the one that uses the largest row. If the bot must move directly
    * to broken, choose the move with the least amount of tiles
    */
    int totalMovesToConsider = movesToConsider.size();
    string chosenMove = "";
    if(!directBroken){
        int largestRow = 0;
        for(int i = 0; i < totalMovesToConsider; i++){
            string currTurn = movesToConsider.at(i);
            int row = currTurn[9] - '0';
            if(row > largestRow){
                chosenMove = currTurn;
                largestRow = row;
            }
        } 
    }else{
        int leastTiles = MAX_BAG_TILES;
        for(int i = 0; i < totalMovesToConsider; i++){
            string currTurn = movesToConsider.at(i);
            char factoryChar = currTurn[5];
            char tile = currTurn[7];
            int factoryNum = factoryChar - '0';
            int tilesToAdd = 0;
            if(factoryChar == '0'){
                tilesToAdd = factoryZero->getNumOfCol(tile);
            }else{
                tilesToAdd = factories[factoryNum - 1]->getNumberOfCol(tile);
            }
            if(tilesToAdd < leastTiles){
                chosenMove = currTurn;
                leastTiles = tilesToAdd;
            }
        }
    }
    return chosenMove;
}