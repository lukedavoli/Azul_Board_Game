#ifndef LINKED_LIST_H
#define LINKED_LIST_H 
#include <utility>
using std::move;

class Node {
public:
   Node(char value, Node* next);
   char value;
   Node* next;
};

class LinkedList {
public:
   LinkedList();
   LinkedList( LinkedList& other);
   ~LinkedList();

   /**
    * Return the current size of the Linked List.
    */
     int size()  ;

   /**
    * output: Get the value at the given index.
    * input: Index must be >=0 and < size()
    * 
    */
   char get( int index)  ;

   /**
    * Add the value to the back of the Linked List
    */
   void addBack(char&& value);

   /**
    * Add the value to the front of the Linked List
    */
   void addFront(char&& value);

   /**
    * Remove the value at the back of the Linked List
    * It used under the codition that the Linked List 
    * is not empty
    */
   void removeBack();

   /**
    * Remove the value at the front of the Linked List
    * It used under the codition that the Linked List 
    * is not empty
    */
   void removeFront();

   /**
    * Removes all values from the Linked List
    */
   void clear();
  
   //Prints all values from the Linked List
   void print();

private:

   Node* head;
   int length;
};

#endif // LINKED_LIST_H
