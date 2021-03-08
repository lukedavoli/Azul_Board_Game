#include "LinkedList.h"
#include <iostream>

using std::cout;
using std::endl;
int main()
{

    LinkedList *list = new LinkedList();
    cout << "Size: " << (*list).size() << endl;
    (*list).addBack(5);
    cout << "First: " << (*list).get(0) << endl
         << "Size: " << (*list).size() << endl;

    (*list).removeBack();
    cout << "Size: " << (*list).size() << endl;

    (*list).addBack(3);
    cout << "First: " << (*list).get(0) << endl;
    cout << "Size: " << (*list).size() << endl;

    (*list).addBack(2);
    (*list).addBack(5);
    (*list).addBack(8);
    cout << "Second: " << (*list).get(1) << endl;
    cout << "Size (After adding three items to the back): " << (*list).size() << endl;
    cout << "The list is:";
    (*list).print();

    (*list).removeFront();
    cout << "Size (After removing front): " << (*list).size() << endl;
    cout << "First: " << (*list).get(0) << endl;

    (*list).addFront(100);
    cout << "Size  (After adding in front): " << (*list).size() << endl;
    
    (*list).removeBack();    
    cout << "The list is (After removing Back):"<<endl;
    (*list).print();

    LinkedList *l = new LinkedList(*list);
    cout << "Size (After adding in front): " << (*l).size() << endl;
    cout << "The new list is:" << endl;
    (*l).print();

    (*list).clear();
    cout << "Size (After clear on list): " << (*list).size() << endl;
}