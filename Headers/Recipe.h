#pragma once
#ifndef  RECIPE_H
#define RECIPE_H
#include <iostream>
#include <string>
using namespace std;

class Recipe
{
public:
	string item1, item2;

	Recipe(string i1, string i2);

	Recipe();

	string getItem1();
	string getItem2();

};

#endif