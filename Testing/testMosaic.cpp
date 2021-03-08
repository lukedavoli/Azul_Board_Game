#include "Mosaic.h"
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;

#define MAX 5

// For each row insert tile "t"
void insertTest(Mosaic* m, char t);

int main(int argc, char const *argv[])
{
    Mosaic* m = new Mosaic();
    cout << "For each row insert R and U" << endl;
    insertTest(m, 'R');
    insertTest(m, 'U');

    m->printMosaic();
    cout << endl;
    m->print2DMosaic();
    cout << endl;

    cout << "For each row insert Y, B and L" << endl;

    insertTest(m, 'Y');
    insertTest(m, 'B');
    insertTest(m, 'L');

    m->printMosaic();
    cout << endl;
    m->print2DMosaic();
    cout << endl;

    cout << "<<Reset Mosaic>>" << endl;
    m->clear();
    m->printMosaic();
    cout << endl;
    m->print2DMosaic();
    cout << endl;

    string line1 = "b Y r u L";
    cout << "Load into row 1: " + line1 << endl;
    m->loadRow(1, line1);
    m->printMosaic();
    cout << endl;

    string line2 = "B y R U L";
    cout << "Load into row 4: " + line2 << endl;
    m->loadRow(4, line2);
    m->printMosaic();
    cout << endl;

    string line3 = "";
    cout << "Load into row 3: " + line3 << endl;
    m->loadRow(3, line3);
    m->printMosaic();
    cout << endl;

    string line4 = "B Y R U L";
    cout << "Load into row 10: " + line4 << endl;
    m->loadRow(10, line4);
    m->printMosaic();
    cout << endl;
    m->print2DMosaic();
    cout << endl;

    cout << "Get Row 1: " << m->getRow(1) << endl;

    cout << "Get Row 2: " << m->getRow(2) << endl;

    cout << "Get Row 3: " << m->getRow(3) << endl;

    cout << "Get Row 4: " << m->getRow(4) << endl;

    cout << "Get Row 5: " << m->getRow(5) << endl;
    
    cout << "Get Row 10: " << m->getRow(10) << endl;
    
    cout << "Get Row 1000: " << m->getRow(1000) << endl;

    cout << endl;
    cout << "<<Reset Mosaic>>"<< endl;
    m->clear();
    cout << "Insert H into Row 1" << endl;
    m->insertRow(1, 'H');
    m->printMosaic();
    cout << endl;

    return 0;
}

void insertTest(Mosaic* m, char t) {

    for(int i = 0; i != MAX; ++i){
        m->insertRow(i+1, t);
    }
}
