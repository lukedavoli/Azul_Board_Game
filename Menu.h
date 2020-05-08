#ifndef MENU_H
#define MENU_H
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <fstream>
#include <string>
#include "GameEngine.h"


using std::ifstream;
using std::cout;
using std::cin;

#define SHORT_LB "----"
#define MEDIUM_LB "-------------------"
#define LONG_LB "----------------------------------"

#define PROMPT "> "

#define STUDENTS 3
#define S1_NAME  "Michael Lyberopoulos"
#define S2_NAME  "Nikita Phung"
#define S3_NAME  "Luke Davoli"
#define S1_SID   "s3787260"
#define S2_SID   "s3783287"
#define S3_SID   "s3782747"
#define S1_EMAIL "s3787260@student.rmit.edu.au"
#define S2_EMAIL "s3783287@student.rmit.edu.au"
#define S3_EMAIL "s3782747@student.rmit.edu.au"



class Menu{
public:
    //Welcome message to be displayed once at the beginning of the program
    void displayWelcome();

    //Opens the menu
    void displayMenu();

    //Displays students name, id and email
    void showCredits();

private:
    std::string names[STUDENTS] = {S1_NAME, S2_NAME, S3_NAME};
    std::string ids[STUDENTS] = {S1_SID, S2_SID, S3_SID};
    std::string emails[STUDENTS] = {S1_EMAIL, S2_EMAIL, S3_EMAIL};
    
    shared_ptr<GameEngine> gameEngine;

    //Takes a filename to load a saved game.
    void loadGame();
    // Booleans to check the file.
    bool fileExists(string filename);
    bool validFile(string filename);
};


#endif //APT_A2_MENU_H
#endif
