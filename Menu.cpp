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
            newGame();
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
        else if(std::cin.eof())
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

void Menu::newGame()
{
    std::string p1Name = "";
    std::string p2Name = "";

    std::cout << "Starting a New Game\n" << std::endl;
    std::cout << "Enter a name for player 1" << std::endl;
    std::cout << PROMPT;
    std::cin >> p1Name;
    std::cout << "Enter a name for player 2" << std::endl;
    std::cout << PROMPT;
    std::cin >> p2Name;

    std::cout << "\nLet's Play!\n" << std::endl;

    //TODO start game
}

void Menu::loadGame()
{
    std::string filename;

    std::cout << "Enter the filename from which to load the game" << std::endl;
    std::cout << PROMPT;
    std::cin >> filename;

    //TODO check that file exists
    //TODO check that file contains a valid game (format of valid game TBC)
}



