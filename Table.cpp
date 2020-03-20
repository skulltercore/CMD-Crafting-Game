
#include "Table.h"

Table::Table()
{

}

void Table::addItem(Item i)
{
	itemList.push_back(i);
}

void Table::printItems()//Print Items On Table
{
	system("cls");
	cout << "On the table in front of you, you can see:" << endl;

	for (auto i : itemList)
	{
		if (i.getAmount() > 0)
		{
			cout << "-> " << i.getAmount() << " ";

			if (i.hasUnit)
			{
				cout << i.unit;
				if(i.getAmount() > 1)
					cout << "s";

				cout << " of " << i.getName() << endl;
			}
			else
			{
				if (i.getAmount() > 1)
					cout << i.getName() << "S" << i.unit << endl;
				else
				cout << i.getName() << endl;
			}
			
		}
	}
}

bool Table::checkItemExists(string n)//Check if Item exists
{
	for (auto i : itemList)
	{
		if (i.getName() == n)
		{
			return true;
		}
	}
	return false;
}

bool Table::removeItemByName(string n)//Remove Item By Name
{
	for (auto &i : itemList)
	{
		if (i.getName() == n)
		{
			if (i.getAmount() > 0)
			{
				i.remove();
				return true;
			}
			else
			{
				system("cls");
				cout << "That item doen't exist!" << endl;
				return false;
			}
		}
	}
}

void Table::addItemByName(string n)//Add Item By Name
{
	for (auto &i : itemList)
	{
		if (i.getName() == n)
		{
			i.add();
		}
	}
}

Item Table::getItemByName(string n)// Get Item By Name
{
	for (auto i : itemList)
	{
		if (i.getName() == n)
		{
			return i;
		}
	}
}

Item* Table::checkRecipeItem(string n1, string n2)//Return Product of combined Items
{
	for (auto &i : itemList)
	{
		Recipe r = i.getRecipe();

		if (r.getItem1() == n1)
		{
			if (r.getItem2() == n2)
			{
				return &i;
			}
		}
		else
		if (r.getItem2() == n1)
		{
			if (r.getItem1() == n2)
			{
				return &i;
			}
		}
	}
}

bool Table::checkRecipeBool(string n1, string n2) //return whether Items can be combines
{
	for (auto i : itemList)
	{
		Recipe r = i.getRecipe();

		if (r.getItem1() == n1)
		{
			if (r.getItem2() == n2)
			{
				return true;
			}
		}
		else
			if (r.getItem2() == n1)
			{
				if (r.getItem1() == n2)
				{
					return true;
				}
			}
	}
	return false;
}

bool Table::printCraftAmount() //Display Items Crafted and The amount Crafted Of Each
{
	bool didCraft = false;

	for (auto i : itemList)
	{
		if (i.getCraftAmount() > 0)
		{
			cout << "-> " << i.getCraftAmount() << " ";

			if (i.hasUnit)
			{
				cout << i.unit;
				if (i.getCraftAmount() > 1)
					cout << "s";

				cout << " of " << i.getName() << endl;
			}
			else
			{
				if (i.getCraftAmount() > 1)
					cout << i.getName() << "S" << i.unit << endl;
				else
					cout << i.getName() << endl;
			}
			didCraft = true;
		}
	}

	return didCraft;
}