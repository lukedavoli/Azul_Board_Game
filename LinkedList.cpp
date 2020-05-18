#include "LinkedList.h"
#include <iostream>

Node::Node(char value, Node *next) :
 value(value),
 next(next)
{
}

LinkedList::LinkedList()
{
    this->head = nullptr;
    this->length = 0;
}

LinkedList::LinkedList(LinkedList &other) : LinkedList()
{

    for (int i = 0; i < other.size(); i++)
    {

        this->addBack(other.get(i));
    }
}

LinkedList::~LinkedList()
{
    clear();
}

int LinkedList::size()
{
    return length;
}

char LinkedList::get(int index)
{
    int count = 0;
    Node *current = head;
    char returnValue = 10;
    if (index == 0)
    {
        returnValue = head->value;
    }

    while (count < index)
    {

        ++count;
        current = current->next;

        returnValue = current->value;
    }

    return returnValue;
}

void LinkedList::addFront(char&& value)
{
    Node *toAdd = new Node(value, nullptr);

    if (head == nullptr)
    {
        head = toAdd;
    }
    else
    {
        Node *current = head;
        toAdd->next = current;
        head = toAdd;
    }
    this->length++;
}

void LinkedList::addBack(char&& value)
{
    Node *toAdd = new Node(value, nullptr);

    if (head == nullptr)
    {
        head = toAdd;
    }
    else
    {
        Node *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = toAdd;
    }
    this->length++;
}

void LinkedList::removeBack()
{

    if (head->next == nullptr)
    {
        removeFront();
    }
    else
    {
        Node *prev = nullptr;
        Node *current = head;

        while (current->next != nullptr)
        {
            prev = current;
            current = current->next;
        }

        prev->next = current->next;
        delete current;
    }
    if (size() > 0)
    {
        this->length--;
    }
}

void LinkedList::removeFront()
{
   Node* current = head->next;
   delete head;
   head = current;
    if (size() > 0)
    {
        this->length--;
    }
}

void LinkedList::clear()
{
    while (head != nullptr)
    {
        removeFront();
    }
    this->length = 0;
}

void LinkedList::print()
{

    for (int i = 0; i < size(); i++)
    {
        std::cout << get(i) << " ";
    }
}