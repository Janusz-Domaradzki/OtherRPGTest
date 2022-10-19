#ifndef ITEM_HH
#define ITEM_HH

#include <iostream>
#include <string>
#include <stdlib.h>
#include <memory>

using namespace std;

enum i_type {weapon, armor, useable, useless};

enum i_stat {damage, defense, value, literally_zero};

enum i_material {copper, iron};

class Item
{
	string item_name;
	i_type item_type;
	int item_stat;

	public:

	Item(string name = "", i_type type = useless, int stat = 0);
	~Item() {;}

	string get_item_name() {return item_name;}

	i_type get_item_type() {return item_type;}

	int get_item_stat() {return item_stat;}

};





#endif