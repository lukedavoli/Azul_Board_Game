
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
        getline(inStream, line);
        validNextPlayer(inStream, p1Name, p2Name, &valid);
        validFactoryZero(inStream, &valid);
        validFactory(inStream, &valid);
        validMosaics(inStream, &valid);
        validStorageRows(inStream, &valid);
        validBrokenStorage(inStream, &valid);
        validBag(inStream, &valid);
        validBoxLid(inStream, &valid);
    
    
    inStream.close();
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
    string line = "";
    if(*valid == true){
        getline(inStream, line);
        if(line.compare(p1Name) != 0 && line.compare(p2Name) != 0){
        *valid = false;
        cout << "Error - Invalid Next Player: "<< line << endl;
        }
    }
   
}

void Menu::validFactoryZero(istream& inStream, bool* valid){
    string line = "";
    if(*valid == true){
        getline(inStream, line);
        for(string::iterator c = line.begin(); c != line.end(); ++c){
        if(*c != ' '){
            validFacZandBrokenChar(*c, valid);
        }
    }
    }
   
}

void Menu::validFactory(istream& inStream, bool* valid) {
    string line = "";
    if(*valid == true){
        for(int i = 0; i < MAX_FACTORY_NUM; ++i){
        getline(inStream, line);
        validFactoryLength(line, valid);
            for(string::iterator c = line.begin(); c != line.end(); ++c){
                if(*c != ' '){
                    validFactoryChar(*c, valid);
                }
            }
        }
    }
}

void Menu::validFactoryChar(char c, bool* valid) {
    if(c != BLUE && c != YELLOW && c != RED && c != BLACK && c != LIGHT_BLUE) {
        *valid = false;
        cout << "Error - Invalid Factory Character: " << c << endl;
    }
}

void Menu::validFactoryLength(string line, bool* valid) {

    if(line.size() != MAX_CHARS_FOR_FACTORY) {
        *valid = false;
        cout << "Error - Invalid Factory Length: " << line.size() << endl;
    }
}

void Menu::validFacZandBrokenChar(char c, bool* valid){
    if(c != BLUE && c != YELLOW && c != RED && c != BLACK && c != LIGHT_BLUE && c != FIRST_PLAYER_MARKER) {
        *valid = false;
        cout << "Error - Invalid Factory Zero or Broken Storage Character: " << c << endl;
    }
}

/*  
    For each player:
        For each row:
        If line size is not 9 (max size for mosaic string = 5 tiles + 4 white space)
            Set valid to false
        Else if valid is still true:
        For each character in the string:
            If character is not white space.
            Check that each char within the row is valid.
*/

void Menu::validMosaics(istream& inStream, bool* valid){
    string line = "";
    if(*valid == true){
        for(int i = 0; i < NUM_OF_PLAYERS; ++i){
            for(int i = 0; i < MAX_MOSAIC_ROW_NUM; ++i){
                getline(inStream, line);
                if(line.size() != MAX_CHARS_FOR_MOSAIC) {
                    *valid = false;
                    cout << "Error - Invalid Mosaic Size: " << line.size() << endl;
                } else if(*valid) {
                    for(string::iterator c = line.begin(); c != line.end(); ++c) {
                        if(*c != ' '){
                            validMosaicChar(*c, valid);
                        }
                    }
                }   
            }   
        }
    }
}


void Menu::validMosaicChar(char c, bool* valid){
    if( c != BLUE && c != YELLOW && c != RED && c != BLACK && c != LIGHT_BLUE &&
        c != EMPTY_BLUE && c != EMPTY_YELLOW && c != EMPTY_RED && c != EMPTY_BLACK && c != EMPTY_LIGHT_BLUE) {
        *valid = false;
        cout << "Error - Invalid Mosaic Character: " << c << endl;
    }
}

/*  
    For each player:
        For each row:
        Check that the row is size is valid.
        If valid is still true:
        For each character in the string:
            If character is not white space.
            Check that each char within the row is valid.
*/
void Menu::validStorageRows(istream& inStream, bool* valid){
    string line = "";
    if(*valid == true){
        for(int i = 0; i < NUM_OF_PLAYERS; ++i){
            for(int i = 0; i < STORAGE_ROWS; ++i){
                getline(inStream, line);
                validStorageSize(inStream, valid, i, line);
                if(*valid){
                    for(string::iterator c = line.begin(); c != line.end(); ++c){
                        if(*c != ' '){
                            validStorageChar(*c, valid);
                        }
                    }
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
            if(line.size() != 1){
                *valid = false;
                cout << "Error - Invalid Storage Size: "<< line.size() << endl;
            }
    } else if(index > 0){
            int size = line.size();
            if(size != 2*index + 1){
                *valid = false;
                cout << "Error - Invalid Storage Size: "<< line.size() << endl;
            }
        }
    }
}

void Menu::validStorageChar(char c, bool* valid){
     if(c != BLUE && c != YELLOW && c != RED && c != BLACK && c != LIGHT_BLUE && c != EMPTY) {
        *valid = false;
        cout << "Error - Invalid Storage Character: "<< c << endl;
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
            } else if(*valid){
                for(string::iterator c = line.begin(); c != line.end(); ++c){
                    if(*c != ' '){
                        validFacZandBrokenChar(*c, valid);
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
        } else if(*valid){
            for(string::iterator c = line.begin(); c != line.end(); ++c){
                if(*c != ' '){
                    validFactoryChar(*c, valid);
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
            cout << "Error - Invalid Bag Size: " << line.size() << endl;
        } else if(*valid){
            for(string::iterator c = line.begin(); c != line.end(); ++c){
                if(*c != ' '){
                    validFactoryChar(*c, valid);
                }
            }
        }
    }
}



