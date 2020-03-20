#pragma once
#ifndef  Player_H
#define Player_H
#include <iostream>
#include <list>
#include <string>
#include "Item.h"
#include "Table.h"
using namespace std;

class Player
{
public:
	Item inHands[2];
	int score;

	Player();

	bool checkHandsFree();

	void addItem(Item n);

	void printItems();

	void dropItem(string n);

	void dropAllItems(Table* t);

	bool isItemHeld(string n);

	void combineItems(Item* i);

	int getScore();

};

#endif