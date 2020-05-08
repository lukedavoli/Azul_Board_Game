
#include "Menu.h"


void Menu::displayWelcome()
{
    std::cout << "Welcome to Azul!\n" <<
                 MEDIUM_LB <<
                 std::endl;
}

void Menu::displayMenu()
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
            gameEngine->newGame();
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
    ifstream inStream(filename);
    string line = " ";
    // while(!inStream.eof()){
    //     // Check if each line is valid.
    //     getline(inStream, line);
    // }
    inStream.close();
    return valid;
}



