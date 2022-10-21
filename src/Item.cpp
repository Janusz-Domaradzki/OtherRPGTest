#include "Item.hh"


Item::Item(string name, i_type type, int stat, bool use, int amount)
{
	item_name = name;
	item_type = type;
	item_stat = stat;
	item_amount = amount;
	to_use = use;
}


int Item::reduce_amount()
{
	this->item_amount--;
	return item_amount;
}
