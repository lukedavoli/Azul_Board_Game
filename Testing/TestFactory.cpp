#include "Factory.h"
#include <iostream>
#include <utility>

using std::cout;
using std::endl;
int main()
{
    FactoryZero* fz =new FactoryZero();
    Factory* f = new Factory(5);

    //Test get number (Factory)
    cout<<"Factory NUM:"<<(*f).getNumber()<<endl;
    
    //Test adding tiles (Factory)
    (*f).addToFactory('R');
    (*f).addToFactory('B');
    cout<<"Factory "<<(*f).getNumber()<<" has :";
    (*f).print();
    cout<<endl;
     
    //Test get number (Factory)
    (*f).addToFactory('R');
     cout<<"Factory "<<(*f).getNumber()<<" has :";
    (*f).print();
    cout<<endl;

    //Test copy constructor , get number of times in the factory(Factory)
    Factory* f2= new Factory(*f);
    cout<<"Copied factory number:"<<(*f2).getNumber()<<endl;
    cout<<"Has:";(*f2).print();
    cout<<endl;
    cout<<"After adding a second red. (to the first factory )"<<endl;
    cout<<"Red is: "<<(*f).getNumberOfColour('R')<<" times inside this factory"<<endl;
    cout<<"Blue is: "<<(*f).getNumberOfColour('B')<<" times inside this factory"<<endl;
     
     //Test remove tile (Factory)
    (*f).removeTile('B',fz);
    cout<<"Factory "<<(*f).getNumber()<<" has :";
     (*f).print();
    cout<<". After removing  blue."<<endl;
    cout<<"Red is: "<<(*f).getNumberOfColour('R')<<" times inside this factory"<<endl;
    cout<<"Blue is: "<<(*f).getNumberOfColour('B')<<" times inside this factory"<<endl;
    cout<<"In factory zero:"<<endl;
    (*fz).print();
    cout<<endl;

    //Test move constructor (Factory)
    (*f).addToFactory('Y');
    Factory* fm = new Factory(std::move(*f));
    cout<<"'Moved' factory has number:"<<(*fm).getNumber()<<endl;
    cout<<"Has: ";
    (*fm).print();
    cout<<endl;
     
   
   // Test get number (Factory Zero)
    cout<<"Factory zero has number:"<<(*fz).getFNum()<<endl;
   
    // Test add tile (Factory Zero)
    (*fz).addToFac('Y');
    cout<<"Factory zero has:";
    (*fz).print();
    cout<<endl;
    
    // Test rmeove tile (Factory Zero)
    (*fz).removeTile('Y');
    cout<<"Factory zero has (After removing Y):";
    (*fz).print();
    cout<<endl;

    // Test  get number of times in the factory   (Factory Zero)
    cout<<"Inside factory zero tile Red is:"<< (*fz).getNumOfCoulour('R')<<" times"<<endl;
    
    // Test Copy Constructor (Factory Zero)
    FactoryZero* fz2 = new FactoryZero(*fz);
    cout<<"Copied factory zero has:";
    (*fz2).print();
    cout<<endl;
    // Test Move Constructor (Factory Zero)
    FactoryZero* fz3 = new FactoryZero(std::move(*fz));
    cout<<"'Moved' factory zero has:";
    (*fz3).print();
    cout<<endl;
    //(*fz).print();
     


}

