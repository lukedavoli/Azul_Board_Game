#include <iostream>
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
    while(std::cin.eof() || !quit )
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
         
        else if(menuSelection == 4)
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
    std::string filename;

    std::cout << "Enter the filename from which to load the game" << std::endl;
    std::cout << PROMPT;
    std::cin >> filename;

    //TODO check that file exists
    //TODO check that file contains a valid game (format of valid game TBC)
    //TODO load game and continue
}



