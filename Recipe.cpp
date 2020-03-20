
#include "Recipe.h"

Recipe::Recipe(string i1, string i2)//Create recipe
{
	item1 = i1;
	item2 = i2;
}

Recipe::Recipe()//default Constructor
{
	item1 = "NULL";
	item2 = "NULL";
}

string Recipe::getItem1() //Get Item 1
{
	return item1;
}

string Recipe::getItem2() //Get Item 2
{
	return item2;
}