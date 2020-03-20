#pragma once
#ifndef  TABLE_H
#define TABLE_H
#include <iostream>
#include <list>
#include <string>
#include "Item.h"
using namespace std;

class Table
{
public:
	list<Item> itemList;

	Table();

	void addItem(Item i);

	void printItems();

	bool checkItemExists(string n);

	bool removeItemByName(string n);

	void addItemByName(string n);

	Item getItemByName(string n);

	Item* checkRecipeItem(string n1, string n2);

	bool checkRecipeBool(string n1, string n2);

	bool printCraftAmount();

};

#endif