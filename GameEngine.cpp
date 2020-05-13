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

                    cout <<factory<<","<<tile<<","<<row<<endl;

                    if(validateTurn(factory, tile, row)) {
                        validCommand = true;
                        performTurn(factory, tile, row);
                        if (this->nextTurn.compare(player1->getName())==0)
                        {
                            nextTurn = player2->getName();
                        }
                        else
                        {
                            nextTurn = player1->getName();
                        }
                    }else{
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
           cout<<"test1"<<endl;
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
    
    if (exists && validTileInRow(tile,row) )
    {
        cout<<"Yeees"<<endl;
        validTurn=true;
    }
    

    return validTurn;
}

bool GameEngine::validTileInRow(char tile, char row){
    // Checks if row can accept tile
    // If mosaic row doesnt have the tile
        // If storage row isnt full
            // If storage row is empty
                // valid = true;
            // Else (there are other tile(s) in the row)
                // If storage rowTile == tile (same colour)
                    //valid = true
    bool valid=false;
    bool exists = false;
    int r;
    if(row=='1'){
        r=1;
    }
    else if (row=='2')
    {
        r=2;
    }
    else if (row=='3')
    {
        r=3;
     }
    else if (row=='4')
    {
        r=4;    
    }
    else
    {
        r=5;
    }
    
    if (this->nextTurn.compare( player1->getName())==0)
    {
        for (int i = 0; i < 9; i+=2)
        {
              
            if (player1->getMosaic()->getRow(r)[i]==tile)
            {
                exists=true;
            }
              
        }
         if (!exists && !player1->getStorageRow(r)->isFull())
         {
             if (player1->getStorageRow(r)->getLength()==0)
             {
                 valid=true;
             }
             else if (player1->getStorageRow(r)->getOccupyingColour()==tile)
             {
               valid=true;
             }
              
             
             
         }
         
        
          }
    
     else
     {
          for (int i = 0; i < 9; i+=2)
        {
              
            if (player2->getMosaic()->getRow(r)[i]==tile)
            {
                exists=true;
            }
              
        }
         if (!exists && !player2->getStorageRow(r)->isFull())
         {
             if (player2->getStorageRow(r)->getLength()==0)
             {
                 valid=true;
             }
             else if (player2->getStorageRow(r)->getOccupyingColour()==tile)
             {
               valid=true;
             }
              
             
             
         }
         
        
        }
    
                    return valid;

}

void GameEngine::performTurn(int factoryN, char tile, char row) {
     int r;
     
    if(row=='1'){
        r=1;
    }
    else if (row=='2')
    {
        r=2;
    }
    else if (row=='3')
    {
        r=3;
     }
    else if (row=='4')
    {
        r=4;    
    }
    
    
    else 
    {
        r=5;
    }
    
    
    
    // Assumes the move is already validated
      char tileE= tile;
      char tileA=tile;
      char Fp='F';
      char tileC=tile;
       
    //   cout<< timesInZ<<endl;
              int timesInZ=(*factoryZero).getNumOfCoulour(std::move(tileE));
     
     
      if (this->nextTurn.compare(player1->getName())==0)    
      {
        if (row=='B')
          {
              player1->getBroken()->addTile(std::move(tileC));
          }
          
          int avLength=r-player1->getStorageRow(r)->getLength();
          if(factoryN==0 && row!='B'){
          
           if(timesInZ<=avLength){
               
               char test3=tile;
           for (int i = 0; i < timesInZ; ++i)
           {
               char test=tile;
               player1->getStorageRow(r)->addTile(std::move(test));

           }
           if ((*factoryZero).getNumOfCoulour(std::move(Fp))==1)  
           {
                player1->getBroken()->addTile(std::move('F'));
               (*factoryZero).removeTile(std::move('F'));
           }
           (*factoryZero).removeTile(std::move(test3));
           }
           else
           {
             char test4=tile;
              
             for (int i = 0; i < avLength; ++i)
           {
               char test =tile;
               player1->getStorageRow(r)->addTile(std::move(test));
           }
           
            for (int i = 0; i < (timesInZ-avLength); ++i)
           {
               char test10 =tile;
                player1->getBroken()->addTile(std::move(test10));
           }
           if ((*factoryZero).getNumOfCoulour('F')==1)  
           {
               player1->getBroken()->addTile(std::move('F'));
               (*factoryZero).removeTile(std::move('F'));
           }
           
                (*factoryZero).removeTile(std::move(test4));
           }
           
           }
       else if(  row!='B')
       {    char test5 = tile;
            int  timesInF=(*factories[factoryN-1]).getNumberOfColour(std::move(tileA));

           if(timesInF<=avLength){
            for (int i = 0; i < timesInF; ++i)
            {
              char test = tile;
              player1->getStorageRow(r)->addTile(std::move(test));
            }
        
                (*factories[factoryN-1]).removeTile(std::move(test5),factoryZero);
             }
            else
            {
                char test2=tile;
                for (int i = 0; i < avLength; i++)
                {
                 char test = tile;
                 player1->getStorageRow(r)->addTile(std::move(test));

                }
                
                 for (int i = 0; i <(timesInF- avLength); i++)
                 {
                    char test=tile;
                     player1->getBroken()->addTile(std::move(test));
                 }
                 (*factories[factoryN-1]).removeTile(std::move(test2),factoryZero);
                 
                 
            }
            
       }
       

       }
       else
       {
            if (row=='B')
          {
              player2->getBroken()->addTile(std::move(tileC));
          }
             int avLength=r-player2->getStorageRow(r)->getLength();
        if(factoryN==0  && row!='B'){
           if(timesInZ<=avLength){
               char test3=tile;
           for (int i = 0; i < timesInZ; ++i)
           {
               char test=tile;
               player2->getStorageRow(r)->addTile(std::move(test));

           }
           if ((*factoryZero).getNumOfCoulour(std::move(Fp))==1)  
           {
                player2->getBroken()->addTile(std::move('F'));
               (*factoryZero).removeTile(std::move('F'));
           }
           
           
           (*factoryZero).removeTile(std::move(test3));
           }
           else
           {
             char test4=tile;
             for (int i = 0; i < avLength; ++i)
           {
               char test =tile;
               player2->getStorageRow(r)->addTile(std::move(test));
           }
            for (int i = 0; i < (timesInZ-avLength); ++i)
           {
               char test =tile;
                player2->getBroken()->addTile(std::move(test));
           }
           if ((*factoryZero).getNumOfCoulour('F')==1)  
           {
               player2->getBroken()->addTile(std::move('F'));
               (*factoryZero).removeTile(std::move('F'));
           }
           
                (*factoryZero).removeTile(std::move(test4));
           }
           
           }
        else if( row!='B')
        {
             char test5 = tile;
            int  timesInF=(*factories[factoryN-1]).getNumberOfColour(std::move(tileA));

           if(timesInF<=avLength){
            for (int i = 0; i < timesInF; ++i)
            {
              char test = tile;
              player2->getStorageRow(r)->addTile(std::move(test));
            }
        
                (*factories[factoryN-1]).removeTile(std::move(test5),factoryZero);
             }
            else
            {
                char test2=tile;
                for (int i = 0; i < avLength; i++)
                {
                 char test = tile;
                 player2->getStorageRow(r)->addTile(std::move(test));

                }
                
                 for (int i = 0; i <(timesInF- avLength); i++)
                 {
                    char test=tile;
                     player2->getBroken()->addTile(std::move(test));
                 }
                 (*factories[factoryN-1]).removeTile(std::move(test2),factoryZero);
                 
                 
            }
        }
        
            
       }
       
      
    // TODO implement
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

// Moving tiles at the end of round.
void GameEngine::moveTilesEOR(shared_ptr<Player> player) {
    if(factoriesEmpty()){
        for(int i = 0; i < NUM_OF_PLAYERS; ++i){
            for(int j = 0; j < MAX_STORAGE_NUM; ++j){
                int rowNum = j+1;
                if(player->getStorageRow(rowNum)->isFull()) {
                    char tile = player->getStorageRow(rowNum)->getFirstTile();
                    player->getMosaic()->insertRow(rowNum, tile);
                }
            }
        }
    }
}

bool GameEngine::factoriesEmpty(){
    bool empty = false;
    if(factoryZero->getSize() == 0){
        for(int i = 0; i  < MAX_FACTORY_NUM; ++i){
            if(factories[i]->isClear()){
                empty = true;
            }
        }
    }
    return empty;
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
    while(boxLid[i] != '\000'){
        strBoxLid += boxLid[i];
        if(boxLid[i + 1] != '\000'){
            strBoxLid += " ";
        }
    }
}

string GameEngine::tileBagToString(){
    string strBag = "";
    int size = tileBag->size();
    for (int i = 0; i < size; i++)
    {
        strBag += tileBag->get(i);
        if(i != size - 1){
            strBag += " ";
        }
    }
}


   
 

