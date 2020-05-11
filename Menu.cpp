
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
    string p1Name = "";
    string p2Name = "";
    ifstream inStream(filename);
    
    validPlayerNames(inStream, &p1Name, &p2Name, &valid);
    validPlayerPoints(inStream, &valid);
    validNextPlayer(inStream, p1Name, p2Name, &valid);
    validFactoryZero(inStream, &valid);
    validFactory(inStream, &valid);

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
    for(int i = 0; i < NUM_OF_PLAYERS; ++i){
        inStream >> points;
        if(!inStream.good()){
            *valid = false;
        }
    }
}

void Menu::validNextPlayer(istream& inStream, string p1Name, string p2Name, bool* valid) {
    string line = "";
    getline(inStream, line);
    if(line.compare(p1Name) != 0 && line.compare(p2Name) != 0){
        *valid = false;
    }
}

void Menu::validFactoryZero(istream& inStream, bool* valid){
    string line = "";
    getline(inStream, line);
    for(string::iterator c = line.begin(); c != line.end(); ++c){
         validFacZandBrokenChar(*c, valid);
    }
}

// Check length of string and whether each character is valid.
void Menu::validFactory(istream& inStream, bool* valid) {
    string line = "";
    getline(inStream, line);
    validFactoryLength(line, valid);
    for(string::iterator c = line.begin(); c != line.end(); ++c){
        validFactoryChar(*c, valid);
    }
}

void Menu::validFactoryChar(char c, bool* valid) {
     if(c != BLUE && c != YELLOW && c != RED && c != BLACK && c != LIGHT_BLUE && c != FIRST_PLAYER_MARKER) {
        *valid = false;
    }
}

void Menu::validFactoryLength(string line, bool* valid) {
    const int maxStrLength = 7;
    if(line.size() != maxStrLength) {
        *valid = false;
    }
}

void Menu::validFacZandBrokenChar(char c, bool* valid){
    if(c != BLUE && c != YELLOW && c != RED && c != BLACK && c != LIGHT_BLUE && c != FIRST_PLAYER_MARKER) {
        *valid = false;
    }
}


// TODO: CHECK number of chARS IN STIRNG
void Menu::validMosaics(istream& inStream, bool* valid){
    string line = "";
    for(int i = 0; i < NUM_OF_PLAYERS; ++i){
         getline(inStream, line);
         for(string::iterator c = line.begin(); c != line.end(); ++c){
             validMosaicChar(*c, valid);
         }

    }
}

// TODO: CHECK EACH ROW NUMBER.
void Menu::validStorageRows(istream& inStream, bool* valid){
    string line = "";
    for(int i = 0; i < NUM_OF_PLAYERS; ++i){
        getline(inStream, line);
        for(string::iterator c = line.begin(); c != line.end(); ++c){
            validStorageChar(*c, valid);
        }
        
    }
}

void Menu::validStorageChar(char c, bool* valid){
     if(c != BLUE && c != YELLOW && c != RED && c != BLACK && c != LIGHT_BLUE && c != EMPTY) {
        *valid = false;
    }
}

void Menu::validMosaicChar(char c, bool* valid){
    if( c != BLUE && c != YELLOW && c != RED && c != BLACK && c != LIGHT_BLUE &&
        c != EMPTY_BLUE && c != EMPTY_YELLOW && c != EMPTY_RED && c != EMPTY_BLACK && c != EMPTY_LIGHT_BLUE) {
        *valid = false;
    }
}



