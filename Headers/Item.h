#pragma once
#ifndef  ITEM_H
#define ITEM_H
#include <iostream>
#include <string>
#include "Recipe.h"
using namespace std;

class Item
{
public:
	string name, unit;
	Recipe recipe;
	int amount, points;
	bool first, hasUnit;
	int craftAmount;

	Item(string Itemname, Recipe r, int a, int p);

	Item(string ItemName, string u, Recipe r, int a, int p);

	Item(string Itemname, int a, int p);

	Item(string ItemName, string u, int a, int p);

	Item();

	void creation();

	void remove();

	void add();

	string getName();
	void setName(string n);

	string getUnit();
	void setUnit(string u);


	int getPoints();

	Recipe getRecipe();

	int getAmount();
	void setAmount(int a);

	int getCraftAmount();

};

#endif
