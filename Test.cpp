#include "Mosaic.h"
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;
int main(int argc, char const *argv[])
{
    Mosaic* m = new Mosaic();
    // char newString[5] = {'\0'};
    // string s = "b y r u l";
    // cout << s << endl;
    // cout << newString << endl;
    // m->removeWhiteSpaceFromRow(s, newString);
    // cout << newString << endl;

    m->updateMosaic();
    m->printMosaic();
    return 0;
}
