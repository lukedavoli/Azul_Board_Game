#ifndef MENU_H
#define MENU_H


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

#define NUM_OF_PLAYERS 2
#define MAX_CHARS_FOR_MOSAIC 9
#define MAX_CHARS_FOR_FACTORY 7
#define MAX_CHARS_FOR_BROKEN 13
#define MAX_CHARS_FOR_BAG 199
#define MAX_CHARS_FOR_BOX 199




class Menu{
public:
    //Welcome message to be displayed once at the beginning of the program
    void displayWelcome();

    //Opens the menu
    void displayMenu(int seed, bool seedUsed);

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

    void validPlayerNames(istream& inStream, string* p1Name, string* p2Name, bool* valid);
    void validPlayerPoints(istream& inStream, bool* valid);
    void validNextPlayer(istream& inStream, string p1Name, string p2Name, bool* valid);

    void validFactoryZero(istream& inStream, bool* valid);
    void validFacZandBrokenChar(char c, bool* valid);

    void validFactory(istream& inStream, bool* valid);
    void validFactoryLength(string line, bool* valid);
    void validFactoryChar(char c, bool* valid);

    void validMosaics(istream& inStream, bool* valid);
    void validMosaicChar(char c, bool* valid);

    void validStorageRows(istream& inStream, bool* valid);
    void validStorageSize(istream& inStream, bool* valid, int index, string line);
    void validStorageChar(char c, bool* valid);
 
    void validBrokenStorage(istream& inStream, bool*valid);

    void validBag(istream& inStream, bool* valid);
    void validBoxLid(istream& inSTream, bool* valid); 

};


#endif // MENU_H
