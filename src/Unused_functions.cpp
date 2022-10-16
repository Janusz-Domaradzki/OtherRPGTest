

void remove_item2(int unsigned slot)
{
	if(slot > 3) cout << "Inventory slot doesn't exist" << endl;
	else
	{
		Inventory2.erase(Inventory2.begin()+slot-1);
		switch(Inventory2[slot-1]->item_type)
		{
			case weapon:
			dmg -= Inventory2[slot-1]->item_stat;
			break;
			case armor:
			df -= Inventory2[slot-1]->item_stat;
			break;
			case useable:
			break;
			default:
			cout << "Item type does not exist in this section of code" << endl;
			break;
		}
	}
}

void equip_item2(shared_ptr<Item> item, unsigned int slot)
{
	if(slot > 3) 
	{
		cout << "Inventory slot doesn't exist" << endl;
	}
	else
	{
		Inventory2.insert(Inventory2.begin()+slot-1, item);
		switch(Inventory2[slot-1]->item_type)
		{
			case weapon:
			dmg += Inventory2[slot-1]->item_stat;
			break;
			case armor:
			df += Inventory2[slot-1]->item_stat;
			break;
			case useable:
			break;
			default:
			cout << "Item type does not exist in this section of code" << endl;
			break;
		}
	}
}