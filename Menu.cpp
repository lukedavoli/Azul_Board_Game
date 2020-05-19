
#include "Menu.h"


void Menu::displayWelcome()
{
    std::cout << "Welcome to Azul!\n" <<
                 MEDIUM_LB <<
                 std::endl;
}

void Menu::displayMenu(int seed, bool seedUsed)
{
    gameEngine=  make_shared<GameEngine>();
    bool quit = false;
    while(!quit)
    {
        std::cout << "Menu\n" <<
                  SHORT_LB << "\n" <<
                  "1. New Game\n" <<
                  "2. Load Game\n" <<
                  "3. Credits\n" <<
                  "4. Quit\n" <<
                  std::endl;

        int menuSelection = -1;

        std::cout << PROMPT;
        std::cin >> menuSelection;
        std::cout << "\n";

        if(menuSelection == 1)
        {
            gameEngine->newGame(seed, seedUsed);
        }
        else if(menuSelection == 2)
        {
            loadGame();
        }
        else if(menuSelection == 3)
        {
            showCredits();
        }
        else if(menuSelection == 4 || !cin.good())
        {
            quit = true;
            std::cout << "Goodbye" << std::endl;
        }
        else
        {
            std::cout << "Invalid option, please try again.";
        }
    }
}

void Menu::showCredits()
{
    std::cout << LONG_LB << std::endl;
    for(int i = 0; i < STUDENTS; i++)
    {
        std::cout << "Name: " << names[i] << std::endl;
        std::cout << "Student ID: " << ids[i] << std::endl;
        std::cout << "Email: " << emails[i] << std::endl;

        if(i != STUDENTS - 1)
        {
            std::cout << "\n";
        }
    }
    std::cout << LONG_LB << "\n" << std::endl;
}


void Menu::loadGame()
{
    string filename = "";
    cout << "Enter the filename from which to load the game" << std::endl;
    cout << PROMPT;
    cin >> filename;
         
    if(fileExists(filename)){
        if(validFile(filename)){
            cout << "Loading game..." << endl;
            gameEngine->loadGame(filename);

        } else{
            cout << MEDIUM_LB << endl;
            cout << "Invalid file." << endl;
            cout << MEDIUM_LB << endl;
        }
    } else {
        cout << MEDIUM_LB << endl;
        cout << "File doesn't exist." << endl;
        cout << MEDIUM_LB << endl;
    }

    //TODO check that file contains a valid game (format of valid game TBC)
    //TODO load game and continue
}

bool Menu::fileExists(string filename){
    bool exists = false;
    ifstream inStream(filename);
    if(inStream.good()){
        exists = true;
    }
    inStream.close();
    return exists;
}

bool Menu::validFile(string filename){
    bool valid = true;
    string line = "";
    string p1Name = "";
    string p2Name = "";
    ifstream inStream(filename);
    validPlayerNames(inStream, &p1Name, &p2Name, &valid);
    validPlayerPoints(inStream, &valid);
    validNextPlayer(inStream, p1Name, p2Name, &valid);
    getline(inStream, line);
    validFactoryZero(inStream, &valid);
    validFactory(inStream, &valid);
    validMosaics(inStream, &valid);
    validStorage(inStream, &valid);
    validBrokenStorage(inStream, &valid);
    validBag(inStream, &valid);
    validBoxLid(inStream, &valid);
    inStream.close();

    validTiles(filename, &valid);

    return valid;
}

void Menu::validPlayerNames(istream& inStream, string* p1Name, string* p2Name, bool* valid){
    string line = "";
    for(int i = 0; i < NUM_OF_PLAYERS; ++i){
        inStream >> line;
        if(!inStream.good()){
            *valid = false;
        } else if(i == 0){
            *p1Name = line;
        } else if(i == 1){
            *p2Name = line;
        }
    }
}

void Menu::validPlayerPoints(istream& inStream, bool* valid) {
    int points = 0;
    if(*valid == true){
        for(int i = 0; i < NUM_OF_PLAYERS; ++i){
            if(*valid == true) {
                inStream >> points;
                if(!inStream.good()){
                    *valid = false;
                    cout << "Error - Invalid Player Points." << endl;
                }
            } 
        }
    }
}

void Menu::validNextPlayer(istream& inStream, string p1Name, string p2Name, bool* valid) {
    string nextPlayer = "";
    if(*valid == true){
        inStream >> nextPlayer;
        if(nextPlayer.compare(p1Name) != 0 && nextPlayer.compare(p2Name) != 0){
        *valid = false;
        cout << "Error - Invalid Next Player: "<< nextPlayer << endl;
        }
    }
   
}

void Menu::validFactoryZero(istream& inStream, bool* valid){
    string line = "";
    if(*valid == true){
        getline(inStream, line);
        if(line.size() != 0 && line.size() != 1){
            for(string::iterator c = line.begin(); c != line.end(); ++c){
                if(*valid){
                    if(*c != ' ' && *c != '\n' && *c != '\r'){
                        validFacZandBrokenChar(*c, valid);
                    }
                }
            }
        }
    }
}

void Menu::validFactory(istream& inStream, bool* valid) {
    string line = "";
    if(*valid == true){
        for(int i = 0; i < MAX_FACTORY_NUM; ++i){
        getline(inStream, line);
        validFactoryLength(line, valid, i);
            for(string::iterator c = line.begin(); c != line.end(); ++c){
                if(*c != ' ' && *c != '\n' && *c != '\r'){
                    validFactoryChar(*c, valid, i);
                }
            }
        }
    }
}

void Menu::validFactoryChar(char c, bool* valid, int i) {
    if(c != BLUE && c != YELLOW && c != RED && c != BLACK && c != LIGHT_BLUE && c != EMPTY) {
        *valid = false;
        cout << "Error - Invalid Factory Character: " << c << " in Factory " << i+1 << endl;
    }
}

void Menu::validFactoryLength(string line, bool* valid, int i) {

    if(line.size() != MAX_CHARS_FOR_FACTORY && (line.size() != (MAX_CHARS_FOR_FACTORY + 1))) {
        *valid = false;
        cout << "Error - Invalid Factory Length: " << line.size() << " in Factory " << i+1 << endl;
    }
}

void Menu::validFacZandBrokenChar(char c, bool* valid){
    if(c != BLUE && c != YELLOW && c != RED && c != BLACK && c != LIGHT_BLUE && c != FIRST_PLAYER_MARKER) {
        *valid = false;
        cout << "Error - Invalid Factory Zero or Broken Storage Character: " << c << endl;
    }
}


void Menu::validMosaics(istream& inStream, bool* valid){
    string line = "";
    if(*valid == true){
        for(int i = 0; i < NUM_OF_PLAYERS; ++i){
            for(int rowNum = 0; rowNum < MAX_MOSAIC_ROW_NUM; ++rowNum){
                getline(inStream, line);
                if(line.size() != MAX_CHARS_FOR_MOSAIC &&  (line.size() != (MAX_CHARS_FOR_MOSAIC+1))) {
                    *valid = false;
                    cout << "Error - Invalid Mosaic Size: " << line.size() << " in Mosaic Row " << rowNum+1 << endl;
                } else if(*valid) {
                    validMosaicRow(line, valid, rowNum);
                }   
            }   
        }
    }
}

void Menu::validMosaicChar(string row, bool* valid, int rowNum){
    char tiles[MAX_MOSAIC_ROW_NUM] = {BLUE, YELLOW, RED, BLACK, LIGHT_BLUE};
    int startingPoint[MAX_MOSAIC_ROW_NUM] = {0, 4, 3, 2, 1};
    int start = startingPoint[rowNum];
   
    for(int i = 0; i != MAX_MOSAIC_ROW_NUM; ++i){
        if(*valid) {
            if(!(row[i] == tiles[start%5] || row [i] == tolower(tiles[start%5]))) {
                 *valid = false;
                 cout << "Error - Invalid Mosaic Character: " << row[i] << " in Mosaic Row " << rowNum+1 <<
                 " Column " << i + 1 << endl;
            }
            ++start;
        }    
    }
}

void Menu::validMosaicRow(string row, bool* valid, int rowNum) {
    string mosaicRow = "00000";
    int index = 0;
    for(int i = 0; i != MAX_CHARS_FOR_MOSAIC; ++i){
        if(i%2 == 1){
            if((row[i] != ' ') && (*valid)) {
                *valid = false;
                cout << "Error - Invalid Mosaic Character: " << row[i] << " in Mosaic Row " << rowNum+1 << endl;
            }
        } else {
            mosaicRow[index] = row[i];
            ++index;
        }
    }
    if(*valid){
        validMosaicChar(mosaicRow, valid, rowNum);
    }
}


void Menu::validStorage(istream& inStream, bool* valid){
    string line = "";
    if(*valid == true){
        for(int i = 0; i < NUM_OF_PLAYERS; ++i){
            for(int i = 0; i < STORAGE_ROWS; ++i){
                getline(inStream, line);
                validStorageSize(inStream, valid, i, line);
                if(*valid){
                    validStorageRow(i, valid, line);
                }
            }
        }
    }
}

/*  If index == 0, then there should be only 1 character, if it is larger than 1, 
    then the string should be 2*index + 1 characters.
    R           = 1 character       index = 0
    B B         = 3 characters      index = 1
    Y Y Y       = 5 characters      index = 2
    U U U U     = 7 characters      index = 3
    L L L L L   = 9 characters      index = 4
*/

void Menu::validStorageSize(istream& inStream, bool* valid, int index, string line) {
    if(*valid == true){
        if(index == 0){
            if(line.size() != 1 && line.size() != 2){
                *valid = false;
                cout << "Error - Invalid Storage Size: "<< line.size() << " in Storage Row " << index + 1 << endl;
            }
    } else if(index > 0){
            int size = line.size();
            int expSize = (2*index + 1);
            if(size != expSize && (size != (expSize + 1))){
                *valid = false;
                cout << "Error - Invalid Storage Size: "<< line.size() << " in Storage Row " << index + 1 << endl;
            }
        }
    }
}

void Menu::validStorageRow(int i, bool* valid, string line) {
    int index = 0;
    string row = "00000";
    int size = line.size();
    for(int j = 0; j != size; ++j){
        if(j%2 == 1){
            if((line[j] != ' ' && line[j] != '\n' && line[j] != '\r') && (*valid)){
                *valid = false;
                cout << "Error - Invalid Storage Character: " 
                << line[j] << " in Storage Row " << i+1 << endl;
            }
        } else {
            row[index] = line[j];
            ++index;
        }
    }
    validCharsInStorage(row, valid, i+1);
    
}

void Menu::validCharsInStorage(string row, bool* valid, int rowNum){
    if(rowNum == 1){
        validStorageChar(row[0], valid, rowNum);
    } else if(rowNum > 1) {
        validStorageChar(row[0], valid, rowNum);
        if(*valid){
            for(int i = 1; i < rowNum; ++i){
                if(*valid){
                    if(!((row[i] == row[i-1]) || (row[i] == EMPTY))){
                        *valid = false;
                        cout << "Error - Invalid Storage Character: "<< row[i] 
                        << " in Storage Row " << rowNum << endl;
                    }
                }
            }
        }
    }
}

void Menu::validStorageChar(char c, bool* valid, int i){
     if(c != BLUE && c != YELLOW && c != RED && c != BLACK && c != LIGHT_BLUE && c != EMPTY) {
        *valid = false;
        cout << "Error - Invalid Storage Character: "<< c << " in Storage Row " << i << endl;
    }
}

void Menu::validBrokenStorage(istream& inStream, bool* valid){
    string line = "";
    if(*valid == true){
        for(int i = 0; i < NUM_OF_PLAYERS; ++i){
            getline(inStream, line);
            if(line.size() > MAX_CHARS_FOR_BROKEN){
                *valid = false;
                cout << "Error - Invalid Broken Storage Size: " << line.size() << endl;
            } else if(*valid && line.size() != 0 && line.size() != 1){
                for(string::iterator c = line.begin(); c != line.end(); ++c){
                    if(*valid){
                        if(*c != ' ' || *c != '\n' || *c != '\r'){
                        validFacZandBrokenChar(*c, valid);
                        }
                    }
                }
            }
        }
    }
}

void Menu::validBag(istream& inStream, bool* valid){
    string line = "";
    if(*valid == true){
        getline(inStream, line);
        if(line.size() > MAX_CHARS_FOR_BAG) {
            *valid = false;
            cout << "Error - Invalid Bag Size: " << line.size() << endl;
        } else if(*valid && line.size() != 0 && line.size() != 1){
            for(string::iterator c = line.begin(); c != line.end(); ++c){
                if(*valid){
                    if(*c != ' ' && *c != '\n' && *c != '\r'){
                        validBoxOrBagChar(*c, valid);
                    }
                }
            }
        }
    }
}

void Menu::validBoxLid(istream& inStream, bool* valid) {
    string line = "";
    if(*valid == true){
        getline(inStream, line);
        if(line.size() > MAX_CHARS_FOR_BOX) {
            *valid = false;
            cout << "Error - Invalid Lid Size: " << line.size() << endl;
        } else if(*valid && line.size() != 0 &&  line.size() != 1){
            for(string::iterator c = line.begin(); c != line.end(); ++c){
                if(*valid){
                    if(*c != ' ' && *c != '\n' && *c != '\r'){
                        validBoxOrBagChar(*c, valid);
                    }
                }
                
            }
        }
    }
}

void Menu::validBoxOrBagChar(char c, bool* valid) {
    if(c != BLUE && c != YELLOW && c != RED && c != BLACK && c != LIGHT_BLUE) {
        *valid = false;
        cout << "Error - Invalid Bag/Lid Character: " << c << endl;
    }
}

void Menu::validSeed(istream& inStream, bool* valid){
    int seed = 0;
    if(*valid == true){
        inStream >> seed;
        if(!inStream.good()){
            *valid = false;
            cout << "Error - Invalid seed" << endl;
        }
    }
    
}

void Menu::validTiles(string filename, bool* valid){
    ifstream inStream(filename);
    int skipLines = 5;
    string line = "";
    int redTiles = 0;
    int blueTiles = 0;
    int blackTiles = 0;
    int yellowTiles = 0;
    int lightBlueTiles = 0;

    // Skip the first five lines.
    for(int i = 0; i < skipLines; ++i){
        inStream >> line;
    }

    char c = ' ';
    while(inStream.good()){
        inStream.get(c);
        if(c == RED){
            ++redTiles;
        } else if(c == BLUE){
            ++blueTiles;
        } else if(c == BLACK){
            ++ blackTiles;
        } else if(c == YELLOW){
            ++yellowTiles;
        } else if(c == LIGHT_BLUE) {
            ++lightBlueTiles;
        }
    }
    inStream.close();

    if(*valid){
        if(!(redTiles == 20 && blueTiles == 20 && blackTiles == 20 && yellowTiles == 20 && lightBlueTiles == 20)) {
            *valid = false;
            cout << "Error - Invalid number of tiles: " << "R = " << redTiles << ", B = " 
                << blueTiles << ", U = " << blackTiles << ", Y = " << yellowTiles << ", L = " << lightBlueTiles << endl;
        }
    }
   
    
}



