/*
 * A testing class for Player, StorageRow and BrokenRow
 */

#include "Player.h"

#include <iostream>

int main()
{
    Player* p1 = new Player("Nikita", 40);
    Player* p2 = new Player("Michael", 30);

    std::cout << "p1 name: " << p1->getName() << ", points: " << p1->getPoints() << std::endl;
    std::cout << "p2 name: " << p2->getName() << ", points: " << p2->getPoints() << std::endl;

    p1->setPoints(0);
    p2->setPoints(100);
    std::cout << "Points changed" << std::endl;

    std::cout << "p1 points: " << p1->getPoints() << std::endl;
    std::cout << "p2 points: " << p2->getPoints() << std::endl;

    StorageRow* p1r1 = p1->getStorageRow(1);
    std::cout << "\np1r1: ";
    for(int i = 0; i < p1r1->getMaxTiles(); i++)
    {
        if(i >= p1r1->getLength())
        {
            std::cout << '.';
        } else{
            char nextTile = p1r1->getTileAt(i);
            std::cout << nextTile;
        }
    }
    std::cout << "\n";

    StorageRow* p2r3 = p2->getStorageRow(3);
    std::cout << "p2r3: ";
    for(int i = 0; i < p2r3->getMaxTiles(); i++)
    {
        if(i >= p2r3->getLength())
        {
            std::cout << '.';
        } else{
            char nextTile = p2r3->getTileAt(i);
            std::cout << nextTile;
        }
    }
    std::cout << "\n";

    StorageRow* p1r5 = p1->getStorageRow(5);
    std::cout << "p1r5: ";
    for(int i = 0; i < p1r5->getMaxTiles(); i++)
    {
        if(i >= p1r5->getLength())
        {
            std::cout << '.';
        } else{
            char nextTile = p1r5->getTileAt(i);
            std::cout << nextTile;
        }
    }
    std::cout << "\n";

    char redTile = 'R';
    char blueTile = 'B';
    char blueTile2 = 'B';
    char blackTile = 'U';

    p1->getStorageRow(1)->addTile(std::move(redTile));
    p2->getStorageRow(3)->addTile(std::move(blueTile));
    p2->getStorageRow(3)->addTile(std::move(blueTile2));
    p1->getStorageRow(5)->addTile(std::move(blackTile));

    std::cout << "\np1r1: ";
    for(int i = 0; i < p1r1->getMaxTiles(); i++)
    {
        if(i >= p1r1->getLength())
        {
            std::cout << '.';
        } else{
            char nextTile = p1r1->getTileAt(i);
            std::cout << nextTile;
        }
    }
    std::cout << "\n";

    std::cout << "p2r3: ";
    for(int i = 0; i < p2r3->getMaxTiles(); i++)
    {
        if(i >= p2r3->getLength())
        {
            std::cout << '.';
        } else{
            char nextTile = p2r3->getTileAt(i);
            std::cout << nextTile;
        }
    }
    std::cout << "\n";

    std::cout << "p1r5: ";
    for(int i = 0; i < p1r5->getMaxTiles(); i++)
    {
        if(i >= p1r5->getLength())
        {
            std::cout << '.';
        } else{
            char nextTile = p1r5->getTileAt(i);
            std::cout << nextTile;
        }
    }
    std::cout << "\n";

    std::cout << "\np1r1 occupying colour: " << p1r1->getOccupyingColour() << std::endl;
    std::cout << "p2r3 occupying colour: " << p2r3->getOccupyingColour() << std::endl;
    std::cout << "p1r5 occupying colour: " << p1r5->getOccupyingColour() << std::endl;

    std::cout << "\np1r1 full: " << p1r1->isFull() << std::endl;
    std::cout << "p2r3 full: " << p2r3->isFull() << std::endl;
    std::cout << "p1r5 full: " << p1r5->isFull() << std::endl;

    p1r1->clearCompleteRow();

    std::cout << "\nrow1 cleared" << std::endl;
    std::cout << "p1r1: ";
    for(int i = 0; i < p1r1->getMaxTiles(); i++)
    {
        if(i >= p1r1->getLength())
        {
            std::cout << '.';
        } else{
            char nextTile = p1r1->getTileAt(i);
            std::cout << nextTile;
        }
    }

    std::cout << "\n\np1r1 length: " << p1r1->getLength() << std::endl;
    std::cout << "p2r3 length: " << p2r3->getLength() << std::endl;
    std::cout << "p1r5 length: " << p1r5->getLength() << std::endl;

    BrokenRow* p1b = p1->getBroken();

    std::cout << "\np1 broken: ";
    for(int i = 0; i < MAX_TILES; i++)
    {
        if(i >= p1b->getLength())
        {
            std::cout << '.';
        } else{
            char nextTile = p1b->getTileAt(i);
            std::cout << nextTile;
        }
    }

    std::cout << "\nTiles added to broken row" << std::endl;

    char yellowTile = 'Y';
    char yellowTile2 = 'Y';
    char lightTile = 'L';
    p1b->addTile(std::move(yellowTile));
    p1b->addTile(std::move(yellowTile2));
    p1b->addTile(std::move(lightTile));

    std::cout << "p1 broken: ";
    for(int i = 0; i < MAX_TILES; i++)
    {
        if(i >= p1b->getLength())
        {
            std::cout << '.';
        } else{
            char nextTile = p1b->getTileAt(i);
            std::cout << nextTile;
        }
    }
}