#ifndef ITEM_HH
#define ITEM_HH

#include <iostream>
#include <string>
#include <stdlib.h>
#include <memory>

using namespace std;

enum i_type {weapon, armor, potion, useless};

enum i_stat {damage, defense, value, literally_zero};

struct Item
{
	string item_name;
	i_type item_type;
	int item_stat;

	Item(string name = "", i_type type = useless, int stat = 0);
	~Item() {;}

};

ostream & operator<<(ostream & os, const Item & item);




#endif