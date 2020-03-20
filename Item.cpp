
#include "Item.h"

Item::Item(string ItemName, Recipe r, int a, int p) //Constructor
{
	name = ItemName;
	recipe = r;
	amount = a;
	points = p;
	first = true;
	hasUnit = false;
	craftAmount = 0;
}
Item::Item(string ItemName, string u, Recipe r, int a, int p) //Overload
{
	name = ItemName;
	unit = u;
	recipe = r;
	amount = a;
	points = p;
	first = true;
	hasUnit = true;
	craftAmount = 0;
}

Item::Item(string ItemName, int a, int p) //Overload
{
	name = ItemName;
	amount = a;
	points = p;
	first = true;
	hasUnit = false;
	craftAmount = 0;
}
Item::Item(string ItemName, string u, int a, int p) //Overload
{
	name = ItemName;
	unit = u;
	amount = a;
	points = p;
	first = true;
	hasUnit = true;
	craftAmount = 0;
}

Item::Item()//Default
{

}

void Item::creation() //Display Create Message & Increment Craft Amount
{
	if (first)
	{
		if(hasUnit)
			cout << "You have created your first " << getUnit() << " of " << getName() << "! you have earned " << getPoints() << " points!" << endl;
		else
			cout << "You have created your first " << getName() << "! you have earned " << getPoints() << " points!" << endl;

		first = false;
	}
	else
	{
		if (hasUnit)
			cout << "You have created another " << getUnit() << " of " << getName() << "!" << endl;
		else
			cout << "You have created another " << getName() << "!" << endl;
	}

	craftAmount++;
}

void Item::remove() //Remove Item From Table
{
	setAmount(getAmount() -1);
}

void Item::add() //Add Item to Table
{
	setAmount(getAmount() + 1);
}

string Item::getName() //getName
{
	return name;
}

string Item::getUnit() //getUnit
{
	return unit;
}

int Item::getPoints() //getName
{
	return points;
}

int Item::getAmount() //getAmount
{
	return amount;
}

Recipe Item::getRecipe() //getRecipe
{
	return recipe;
}
int Item::getCraftAmount() //getCraftAmount
{
	return craftAmount;
}


void Item::setName(string n) //setName
{
	name = n;
}

void Item::setUnit(string u) //setUnit
{
	unit = u;
}

void Item::setAmount(int a) //setAmount
{
	amount = a;
}