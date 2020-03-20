//5COSC001W - CW - Joseph Calabro

//If you see errors everywhere - Right Click On "Crafting Game CW" in the Solution Explorer, select "Retarget Projects" and click "OK".
//After doing this the code will run, the errors will still be displayed though. To get rid of them fully close and open visual studio.

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <list>
#include <fstream>
#include <Windows.h> 
#include <algorithm>
#include <cctype>

#include "Recipe.h"
#include "Item.h"
#include "Table.h"
#include "Player.h"

using namespace std;

#define std_con_out GetStdHandle(STD_OUTPUT_HANDLE)

//Commands
string CMD[12];

string input;
string message;
string winMessage;
vector<string> tokens; 

Item winOBJ;
bool win = false;
bool uniqueRecipes = true;
bool namedAll = false;


enum concol // enumeration type
{
	black = 0, dark_blue = 1, dark_green = 2,
	dark_aqua, dark_cyan = 3,
	dark_red = 4,
	dark_purple = 5, dark_pink = 5, dark_magenta = 5,
	dark_yellow = 6,
	dark_white = 7,
	gray = 8,
	blue = 9,
	green = 10,
	aqua = 11, cyan = 11,
	red = 12,
	purple = 13, pink = 13, magenta = 13,
	yellow = 14,
	white = 15
};


void SetCMD()
{
	CMD[0] = "LOOK";
	CMD[1] = "TAKE";
	CMD[2] = "DROP";
	CMD[3] = "COMBINE";
	CMD[4] = "ALL";
	CMD[5] = "QUIT";
}

bool caseInSensStringCompare(string & str1, string &str2)
{
	return ((str1.size() == str2.size()) && equal(str1.begin(), str1.end(), str2.begin(), [](char & c1, char & c2) {
		return (c1 == c2 || toupper(c1) == toupper(c2));
	}));
}

void setcolor(concol textcol, concol backcol)
{
	unsigned short wAttributes = (backcol << 4) | textcol;
	SetConsoleTextAttribute(std_con_out, wAttributes);
}

void splitLine(string in) //Splits string into each word and places each work in a new vector position
{
	tokens.clear();

	std::string str(in);
	std::string buf;                 // Create a buffer string
	std::stringstream ss(str);       // Put string in a stream

	while (ss >> buf)
		tokens.push_back(buf);
}

bool is_unique(std::vector<string> vec)
{
	std::sort(vec.begin(), vec.end());
	return std::unique(vec.begin(), vec.end()) == vec.end();
}

void checkDoubleRecipe() //Opens the text file and counts the number of rooms
{
	string line = "";
	fstream stream;
	stream.open("Game.txt");

	vector<string> recipeList;


	while (getline(stream, line))
	{
		splitLine(line);

		if (line != "")
		{
			if (tokens[0] == "RECIPE")
			{
				recipeList.push_back(line);
			}
		}
	}

	stream.close();

	if (!is_unique(recipeList))
		uniqueRecipes = false;

}


void ReadFromFile(Table* table)
{
	string line = "";

	fstream stream;

	//Set up all the variables we need to read data into from the text file
	//once all the appropriate data is gathered we will create a new room object using it
	
	bool unit = false, isRecipe = false;
	string name, units = "";
	int amount, points = 0;
	Recipe r;

	stream.open("Game.txt");

	while (getline(stream, line)) //Goes through each line of the text file
	{
		splitLine(line); //Splits each line into words using the function above //tokens[0] represents the first word in a line, tokens[1] is the second... etc...

		if (tokens.size() > 1) //If there are multiple words in a line and the first word is a key word, then we know the next is data we need
		{
			if (tokens[0] == "NAME") //GET ITEM NAME
			{
				name = tokens[1];

				if (tokens[1] == "ALL" || tokens[1] == "all" || tokens[1] == "All")
					namedAll = true;
			}
			if (tokens[0] == "WIN") //GET ITEM NAME
			{
				winOBJ.setName(tokens[1]);
			}
			else
			if (tokens[0] == "UNIT") //GET ITEM NAME
			{
				units = tokens[1];
				unit = true;
			}
			else
			if (tokens[0] == "AMOUNT") //GET Amount
			{
				amount = stoi(tokens[1]);
			}
			else
			if (tokens[0] == "POINTS") //GET Points
			{
				points = stoi(tokens[1]);
			}
			if (tokens[0] == "RECIPE") //GET Recipe
			{
				r = Recipe(tokens[1], tokens[2]);
				isRecipe = true;
			}
		}

		if (line == "MES")//Get Message
		{
			getline(stream, message);
		}
		else
		if (line == "WIN-MES")//Get Win Message
		{
			getline(stream, winMessage);
		}
		else
		if (line == "$$--END--ITEM--$$")//End Of Item so time to create it with all our variables
		{
			if (isRecipe)//has recipe
			{
				if (unit)//has unit
				{
					Item i(name, units, r, amount, points);
					table->addItem(i);
				}
				else
				{
					Item i(name, r, amount, points);
					table->addItem(i);
				}
			}
			else//no recipe
			{
				if (unit)//has unit
				{
					Item i(name, units, amount, points);
					table->addItem(i);
				}
				else
				{
					Item i(name, amount, points);
					table->addItem(i);
				}
			}
			//Reset Values
			unit = false;
			name = "";
			units = "";
			amount = 0;
			points = 0;
			isRecipe = false;
			r = Recipe();

		}

	}
	stream.close(); //close text file
}


int main()
{

	SetConsoleTitle(TEXT("Crafting Game - By Joseph Calabro"));//Give Console a nice name

	SetCMD();//set commands

	Player p;//create player
	Table* t = new Table();//create table

	checkDoubleRecipe();//check if two items have the same recipe
	ReadFromFile(t);//read data from file

	

	while (!caseInSensStringCompare(input, CMD[5]))        //while the player hasn't quit run the games main loop
	{
		if (!uniqueRecipes)//If all recipes arent unique then we cant run the game so break out of while loop and give an error message
			break;

		if (namedAll)//If we have an item named "ALL" we cant call the drop all command so we break and give an arror message
			break;

		for (int i = 0; i < 5; i++) //every game loop we want to check if the player has the win obj, if they do then we break out of the while loop
		{
			if (winOBJ.getName() == p.inHands[i].name)
			{
				win = true; //so we can display the win message
				break;     //break out of for loop
			}
		}
		if (win)
		{
			break; //break out of while loop
		}

		cout << endl;
		cout << message << endl;

		input = "";

		while (input.find_first_not_of(' ') == std::string::npos) //The player has to input something otherwise the split will cause an error
			std::getline(cin, input); //Get User Input

		splitLine(input); //Split user input

		if (caseInSensStringCompare(tokens[0], CMD[0])) //------------------------------>LOOK
		{
			t->printItems();
			p.printItems();
		}
		else
		if (caseInSensStringCompare(tokens[0], CMD[1]))
		{
			if (tokens.size() > 1)//Did they specify what to take
			{
				if (t->checkItemExists(tokens[1])) //--------------------------------->TAKE
				{
					if (p.checkHandsFree())//Make sure at least one hand is empty
					{
						if(t->removeItemByName(tokens[1]))//if we have more than 0 of that item on the table we remove it
							p.addItem(t->getItemByName(tokens[1]));//add to hand
					}
					else
					{
						system("cls");
						cout << "Your hands are full!" << endl;
					}
				}
				else
				{
					system("cls");
					cout << "That item doen't exist!" << endl;
				}
			}
			else
			{
				system("cls");
				cout << "What will you take?" << endl;
			}
		}
		else
		if(caseInSensStringCompare(tokens[0], CMD[2])) //--------------------------------------------------->DROP
		{
			if (tokens.size() > 1)//specify what to drop
			{
				if (!caseInSensStringCompare(tokens[1], CMD[4]))//drop all
				{
					if (p.isItemHeld(tokens[1]))//are they holding item
					{
						if (tokens[1] != "empty")//if theyre trying to break the game by droping my empty check 
						{
							p.dropItem(tokens[1]);//remove from hand
							t->addItemByName(tokens[1]);//increment count on table
						}
						else
						{
							system("cls");
							cout << "HAHAHAHA.... nice try..." << endl; 
						}
					}
					else
					{
						system("cls");
						cout << "You are not holding a " << tokens[1] << "!" << endl;
					}
				}
				else
				{
					if (!(p.inHands[0].name == "empty" && p.inHands[1].name == "empty"))
					{
						p.dropAllItems(t);//drop all
					}
					else
					{
						system("cls");
						cout << "You have nothing to drop!" << endl;
					}
				}
			}
			else
			{
				system("cls");
				cout << "What will you drop?" << endl;
			}
			
		}
		else
		if (caseInSensStringCompare(input, CMD[3])) //-----------------------------------------> COMBINE
		{
			if (!p.checkHandsFree())//make sure hands are full
			{
				if (t->checkRecipeBool(p.inHands[0].name, p.inHands[1].name))//make sure recipe exists with held items
				{
					p.combineItems(t->checkRecipeItem(p.inHands[0].name, p.inHands[1].name));//combine items
				}
			}
			else
			{
				system("cls");
				cout << "You need to be holding two items to craft!" << endl;
			}
		}
	}

	system("cls");

	if (win)
	{
		cout << winMessage << endl;//win message yay
	}

	if (!uniqueRecipes)
	{
		cout << "ERROR: The game file contains two or more Items with the same recipe." << endl; //cant have two recipes the same
	}
	else
	if (namedAll)
	{
		cout << "ERROR: Item name can't be 'All'. Please change the games file." << endl; //cant have item named all
	}	
	else
	{

		cout << endl;
		cout << "Thank you for playing! You earned a total of: " << p.getScore() << " points!" << endl;//display points
		cout << "You managed to craft:" << endl;

		if (!t->printCraftAmount())//if the player quits with out crafting then we shame them
			cout << "NOTHING......" << endl;

		cout << endl;
	}
	

	system("pause");
}

