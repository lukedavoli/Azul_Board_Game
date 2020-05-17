#include <random>
#include <set>
#include "GameEngine.h"
#include<string>

GameEngine::GameEngine(){
    initialised = false;
    tileBag = make_shared<LinkedList>();
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

    factoryZero = make_shared<FactoryZero>();
    
    for(int i = 0; i < MAX_FACTORY_NUM; ++i){
        factories[i] = new Factory(i+1);
    }
}

void GameEngine::newGame(int seed, bool seedUsed){

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
    fillFactories();

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
    getline(inStream, line);
    loadFactoryZero(inStream, line);
    loadFactories(inStream, line);
    loadMosaic(inStream, line, player1);    
    loadMosaic(inStream, line, player2);
    loadStorageRows(inStream, line, player1);
    loadStorageRows(inStream, line, player2);
    loadBrokenStorage(inStream, line, player1);
    loadBrokenStorage(inStream, line, player2);
    loadBag(inStream, line);
    loadBoxLid(inStream, line);
    inStream >> seed;
    
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

    for(int i = 0; i < MAX_FACTORY_NUM; ++i){
        cout << "Factory "<< i+1 << ": ";
        factories[i]->print();
        cout << endl;       
    }
    for(int i = 0; i < MAX_MOSAIC_ROW_NUM; ++i){
        cout << "Player 1 Mosaic Row "<< i+1 << ": " << player1->getMosaic()->getRow(i+1) << endl;
    }
    for(int i = 0; i < MAX_MOSAIC_ROW_NUM; ++i){
        cout << "Player 2 Mosaic Row "<< i+1 << ": " << player2->getMosaic()->getRow(i+1) << endl;
    }
    
    for(int i = 0; i < MAX_STORAGE_NUM; ++i) {
        cout << "Player 1 Storage Row "  << i+1 << ": ";
        player1->getStorageRow(i+1)->print();
        cout << endl;
    }
    for(int i = 0; i < MAX_STORAGE_NUM; ++i) {
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

    cout << "Bag: " << tileBagToString() << endl;
    cout << "Box Lid: " << boxLidToString() << endl;
    
    cout << "Seed: " << seed << endl;
}

void GameEngine::enterGame(){
    bool completeRow = false;
    bool userExit = false;
    bool validCommand = false;
    bool cmdShort = true;
    bool firstLoop = true;
    string turn = "";

    while(!userExit && !completeRow){

        setActivePlayer();
        displayTurnUpdate();
        validCommand = false;

        while(!validCommand && !userExit){
            cmdShort = true;
            turn = "";
            cout << PROMPT;
            while (cmdShort && !userExit){
                if(firstLoop){
                    cin.ignore();
                    firstLoop = false;
                }
                getline(cin, turn);
                if(cin.eof()){
                    userExit = true;
                }else{
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
            }

            if(!userExit){
                string command = turn.substr(0, COMMAND_LENGTH);

                // Take action based on command and argument
                if (command == "turn") {

                    //seperate arguments into factory, tile and row
                    int factory = turn[5]-'0'; // Subtract '0' for ASCII conversion
                    char tile =   turn[7];
                    char row =  turn[9];

                    if(validateTurn(factory, tile, row)) {
                        validCommand = true;
                        if (this->nextTurn.compare(player1->getName())==0){
                            performTurn(player1,factory, tile, row);
                        } else {
                            performTurn(player2,factory, tile, row);
                        }
                        
                        if (emptyFactories()){    
                            moveTilesAndScore(player1);
                            moveTilesAndScore(player2);
                            player1->boardToString();
                            player2->boardToString();     
                        }

                        if (this->nextTurn.compare(player1->getName())==0){
                            nextTurn = player2->getName();
                        } else{
                            nextTurn = player1->getName();
                        }

                    } else {
                        cout << "You can't perform that move, try again..." << endl;
                    }

                } else if (command == "save") {
                    validCommand = true;
                    int inputLength = turn.length();
                    string filename = turn.substr(COMMAND_LENGTH + 1,
                                                  inputLength - 1 - COMMAND_LENGTH);
                    saveGame(filename);
                    cout << "Game saved." << endl;
                }else if(command == "exit"){
                    validCommand = true;
                    userExit = true;
                } else {
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
}

// Moving tiles at the end of round.
void GameEngine::moveTilesAndScore(shared_ptr<Player> player) {
    for(int j = 0; j < MAX_STORAGE_NUM; ++j){
        int rowNum = j+1;
        if(player->getStorageRow(rowNum)->isFull()) {
            char tile = player->getStorageRow(rowNum)->getOccupyingColour();
            player->getMosaic()->insertRow(rowNum, tile);
            score(player,rowNum,tile);
            player->getStorageRow(rowNum)->resetRow();
        }
    }
    brokenScore(player);
    player->getBroken()->clearRow();
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
               << player2->getBroken()->toString() << "\n";
    fileStream << boxLidToString() << "\n"
               << tileBagToString() << "\n"
               << seed;
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

bool GameEngine::validateTurn(int factoryN, char tile, char row) {
    // TODO implement
    /*
     * correct character length
     * factory in range
     * tile in range
     * row in range
     * factory has tile
     * validTileInRow() - checks if row can accept tile.
     */
    // Change this with something better
    char checkTile1=tile;
    char checkTile2=tile;
    bool validTurn = false;
    bool validInput=false;
    bool exists=false;
  
    if(tile==RED || tile==YELLOW || tile==BLACK || tile== BLUE || tile==LIGHT_BLUE ){
        if(factoryN>=0 && factoryN<=5 && (row=='1' || row=='2' || row=='3' || row=='4' || row=='5' || row=='B')){
           validInput=true;
        }
    }
     
    if (factoryN ==0 )
    {
         if ( validInput && (*factoryZero).getNumOfCoulour(std::move(checkTile1)) >0)
          {
         exists=true;
         }
    }
    
    if (factoryN>0 && (*factories[factoryN-1]).getNumberOfColour(std::move(checkTile2))>0)
    {
         exists=true;
    }
    
    if ((exists && validTileInRow(tile,row)) ||( row=='B' && exists)  )
    {
        validTurn=true;
    }

    return validTurn;
}

int GameEngine::rowChecker(char row){
    int r=0;
    char array[MAX_FACTORY_NUM]={'1','2','3','4','5'};
    for (int i = 0; i < MAX_FACTORY_NUM; i++) {
        if (row==array[i]){
            r=i+1;
        }
    }
    return r;
}

bool GameEngine::validTileInRow(char tile, char row){

    bool valid=false;
    bool exists = false;
    int r =this->rowChecker(row);

    if (this->nextTurn.compare( player1->getName())==0) {
        for (int i = 0; i < 9; i+=2){
            if (player1->getMosaic()->getRow(r)[i]==tile){
                exists=true;
            }  
        }
        if (!exists && !player1->getStorageRow(r)->isFull()){
            if (player1->getStorageRow(r)->getLength()==0){
                valid=true;
            } else if (player1->getStorageRow(r)->getOccupyingColour()==tile){
                valid=true;
            }
        }
    } else {
        for (int i = 0; i < 9; i+=2){
            if (player2->getMosaic()->getRow(r)[i]==tile) {
                exists=true;
            } 
        }
        if (!exists && !player2->getStorageRow(r)->isFull()){
            if (player2->getStorageRow(r)->getLength()==0){
                valid=true;
            } else if (player2->getStorageRow(r)->getOccupyingColour()==tile){
                valid=true;
            }
        }
    }
    return valid;
}

void GameEngine::performTurn(shared_ptr<Player> player,int factoryN, char tile, char row) {
  
    int r=this->rowChecker(row);
    // Assumes the move is already validated

    char tileE= tile;
    char tileA=tile;
    char Fp='F';
    // char tileC=tile;
    int timesInZ=(*factoryZero).getNumOfCoulour(std::move(tileE));
 
    if(row=='B')
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
            int s=(*factories[factoryN-1]).getNumberOfColour(std::move(test12));
            for (int i = 0; i <s ; i++){
                char test20=tile;
                player->getBroken()->addTile(std::move(test20));
            }
            for (int i = 0; i < s; i++)
            {
                char test15=tile;
                (*factories[factoryN-1]).removeTile(move(test15),factoryZero);
            }
        }
    }
        
    int avLength=r-player->getStorageRow(r)->getLength();
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
        } 
        else
        {
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

    } else if( row!='B'){
        char test5 = tile;
        int  timesInF=(*factories[factoryN-1]).getNumberOfColour(std::move(tileA));
        if(timesInF<=avLength){
            for (int i = 0; i < timesInF; ++i){
                char test = tile;
                player->getStorageRow(r)->addTile(std::move(test));
            }
            (*factories[factoryN-1]).removeTile(std::move(test5),factoryZero);
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
            (*factories[factoryN-1]).removeTile(std::move(test2),factoryZero);
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

void GameEngine::score(shared_ptr<Player> player,int row,char tile){
    shared_ptr<Mosaic> m=player->getMosaic();
    int x=0;
    for (int n = 0; n < 5; n++){
        if (m->get2DMosaic()[row-1][n]==tile){
            x=n;
        }
    }

    int begginingX=x;
   
    bool CANgU=true;// Can Go UP
    bool CANgD=true;// Can Go Down
    bool CANgR=true;// Can Go Right
    bool CANgL=true;// Can Go left
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
    if ((begginingX+1)>4)  {
        CANgR=false;
    }
            
    while ( CANgU ){     
        if(beggingY>0 &&  m->validTile(m->get2DMosaic()[beggingY-1][begginingX])){
            cout<<m->get2DMosaic()[beggingY-1][begginingX]<<endl;
            hadUp=true;
            beggingY--;
            score++;
        } else {
            beggingY=row-1;
            begginingX=x;
            CANgU=false;
        }
    }

    while ( CANgR ){
        if (begginingX<4 &&  m->validTile(m->get2DMosaic()[beggingY][begginingX+1])){
            cout<<m->get2DMosaic()[beggingY][begginingX+1]<<endl;
            hadRight=true;
            begginingX++;
            score++;
        } else {
            beggingY=row-1;
            begginingX=x;
            CANgR=false;
        }
    }

    while (CANgD ){
        cout<<beggingY<<endl;
        if ((beggingY)<4 && m->validTile(m->get2DMosaic()[beggingY+1][begginingX])  ){
            cout<<m->get2DMosaic()[beggingY+1][begginingX]<<endl;
            hadDown=true;
            beggingY++;
            score++;
        } else {
            beggingY=row-1;
            begginingX=x;
            CANgD=false;
        }
    }
       
    while (CANgL) {     
        if(begginingX>0 && m->validTile(m->get2DMosaic()[beggingY][begginingX-1])){
            cout<<m->get2DMosaic()[beggingY][begginingX-1]<<endl;
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

void GameEngine::brokenScore(shared_ptr<Player> player){
    int brokenScore[MAX_BROKEN_TILES] = {-1, -2, -4, -6, -8, -11, -14};
    int prevScore=(*player).getPoints();
    int lostPoints=0;

    for(int i = 0; i != MAX_BROKEN_TILES; ++i){
        if(player->getBroken()->getLength() == i+1) {
            lostPoints = brokenScore[i];
        }
    }

    if (prevScore+lostPoints<0) {
        (*player).setPoints(0);
    } else {
        (*player).setPoints(prevScore+lostPoints);
    }
    cout<<"Players/ "<<(*player).getName()<<" Final Points :"<<(*player).getPoints()<<endl;
}

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

void GameEngine::fillBagFromBoxSeed(int seed) {
    std::uniform_int_distribution<int> uniform_dist(0, TOTAL_TILES - 1);
    std::default_random_engine engine(seed);
    std::set<int> selected;

    while(tileBag->size() != TOTAL_TILES){
        int index = uniform_dist(engine);
        if(selected.find(index) == selected.end()){
            tileBag->addFront(std::move(boxLid.at(index)));
        }
    }
    boxLid.fill('\0');
}

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
        factories[i] = new Factory(i+1);
        for(int t = 0; t < NUM_OF_TILES; t++){
            factories[i]->setTile(t, std::move(tileBag->get(0)));
            tileBag->removeFront();
        }
    }
}

void GameEngine::setActivePlayer() {
    if(nextTurn == player1->getName()){
        activePlayer = player1;
    }else{
        activePlayer = player2;
    }
}

void GameEngine::displayTurnUpdate() {
    cout << "TURN FOR PLAYER: " << activePlayer->getName() << endl;
    cout << "Factories: \n" << factoriesToString() << "\n" << endl;
    cout << activePlayer->getName() << "'s board:\n" <<
         activePlayer->boardToString() << endl;
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