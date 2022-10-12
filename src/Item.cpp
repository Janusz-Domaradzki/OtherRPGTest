#include "Item.hh"


Item::Item(string name, i_type type, int stat)
{
	item_name = name;
	item_type = type;
	item_stat = stat;
}

ostream & operator<<(ostream & os, const Item & itemm)
{
	os << itemm.item_name;
	return os;
}