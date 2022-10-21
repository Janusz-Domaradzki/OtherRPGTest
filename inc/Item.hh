#ifndef ITEM_HH
#define ITEM_HH

#include <iostream>
#include <string>
#include <stdlib.h>
#include <memory>

using namespace std;

enum i_type {weapon, armor, potion, useless};

enum i_stat {damage, defense, value, literally_zero};

enum i_material {copper, iron};

class Item
{
	string item_name;
	i_type item_type;
	int item_stat, item_amount;
	bool to_use;


	public:

	Item(string name = "", i_type type = useless, int stat = 0, bool use = false, int amount = 0);
	~Item() {;}

	string get_item_name() {return item_name;}

	i_type get_item_type() {return item_type;}

	const int get_item_stat() {return item_stat;}

	const int get_item_amount() {return item_amount;}

	 bool if_to_use() {return to_use;}

	int reduce_amount();

};





#endif