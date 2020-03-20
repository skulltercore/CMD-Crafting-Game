
#include "Player.h"

Player::Player() //Constructor set hands to empty
{
	inHands[0].setName("empty");
	inHands[1].setName("empty");

	score = 0;
}

bool Player::checkHandsFree()//returns if either hand is empty
{
	if (inHands[0].name == "empty" || inHands[1].name == "empty")
		return true;
	else
		return false;
}

void Player::addItem(Item i) //Adds Item to hand
{
	if (inHands[0].getName() == "empty")
	{
		inHands[0] = i;

		system("cls");
		if (inHands[0].hasUnit)
			cout << "You picked up 1 " << inHands[0].getUnit() << " of " << inHands[0].getName() << endl;
		else
			cout << "You picked up 1 " << inHands[0].getName() << endl;
	}
	else
	{
		inHands[1] = i;

		system("cls");
		if (inHands[1].hasUnit)
			cout << "You picked up 1 " << inHands[1].getUnit() << " of " << inHands[1].getName() << endl;
		else
			cout << "You picked up 1 " << inHands[1].getName() << endl;
	}
}

void Player::printItems() //Prints Held Items
{
	cout << endl;

	if (inHands[0].getName() == "empty" && inHands[1].getName() == "empty")
	{
		cout << "You are currently holding no items" << endl;
	}
	else
	{
		if (inHands[0].getName() != "empty")
		{
			if (inHands[0].hasUnit)
			{
				cout << "You are holding 1 " << inHands[0].getUnit() << " of " << inHands[0].getName() << " in your left hand." << endl;
			}
			else
			{
				cout << "You are holding 1 " << inHands[0].getName() << " in your left hand." << endl;
			}
		}

		if (inHands[1].getName() != "empty")
		{
			if (inHands[1].hasUnit)
			{
				cout << "You are holding 1 " << inHands[1].getUnit() << " of " << inHands[1].getName() << " in your right hand." << endl;
			}
			else
			{
				cout << "You are holding 1 " << inHands[1].getName() << " in your right hand." << endl;
			}
		}
	}
}

void Player::dropItem(string n) //Drops Items
{
	if (inHands[0].name == n)
	{
		system("cls");
		if (inHands[0].hasUnit)
			cout << "You dropped 1 " << inHands[0].getUnit() << " of " << inHands[0].getName() << endl;
		else
			cout << "You dropped 1 " << inHands[0].getName() << endl;

		inHands[0].name = "empty";
	}
	else
	if (inHands[1].name == n)
	{
		system("cls");
		if (inHands[1].hasUnit)
			cout << "You dropped 1 " << inHands[1].getUnit() << " of " << inHands[1].getName() << endl;
		else
			cout << "You dropped 1 " << inHands[1].getName() << endl;

		inHands[1].name = "empty";
	}
}

void Player::dropAllItems(Table* t) //Drop All Items
{
	system("cls");

	if (inHands[0].name != "empty")
	{
		if (inHands[0].hasUnit)
			cout << "You dropped 1 " << inHands[0].getUnit() << " of " << inHands[0].getName() << endl;
		else
			cout << "You dropped 1 " << inHands[0].getName() << endl;

		t->addItemByName(inHands[0].name);

		inHands[0].name = "empty";
	}
	
	if (inHands[1].name != "empty")
	{
		if (inHands[1].hasUnit)
			cout << "You dropped 1 " << inHands[1].getUnit() << " of " << inHands[1].getName() << endl;
		else
			cout << "You dropped 1 " << inHands[1].getName() << endl;

		t->addItemByName(inHands[1].name);

		inHands[1].name = "empty";
	}
}

bool Player::isItemHeld(string n) //Check if specified Item Is Held
{
	if (inHands[0].name == n || inHands[1].name == n)
		return true;
	else
		return false;
	
}

void Player::combineItems(Item* i) //Combine Held Items
{
	system("cls");

	if (inHands[0].hasUnit)
		cout << "You have combined 1 " << inHands[0].getUnit() << " of " << inHands[0].getName();
	else
		cout << "You have combined 1 " << inHands[0].getName();

	if (inHands[1].hasUnit)
		cout << " with 1 " << inHands[1].getUnit() << " of " << inHands[1].getName() << "!" << endl;
	else
		cout << " with 1 " << inHands[1].getName() << "!" << endl;

	inHands[0].name = "empty";
	inHands[1].name = "empty";
	
	i->creation();

	score += i->getPoints();

	inHands[0] = *i;
}

int Player::getScore()
{
	return score;
}