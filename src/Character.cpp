#include "Character.hh"


Entity::Entity(string cname, unsigned int slvl, unsigned int shp, 
	unsigned int sdmg, unsigned int sdf, unsigned int sxp_val, shared_ptr<Item> dropping)
	{
		lvl = slvl;
		hp = shp + (lvl-1) * HP_BIG_SCALAR + (lvl-1) * HP_SMALL_SCALAR;
		dmg = sdmg + (lvl-1) * DMG_BIG_SCALAR + (lvl-1) * DMG_SMALL_SCALAR;
		df = sdf + (lvl-1) * DF_BIG_SCALAR + (lvl-1) * DF_SMALL_SCALAR;

		max_hp = hp;

		name = cname;

		xp_val = sxp_val;

		for(int i=0; i<3; i++)
		{
			Inventory.push_back(nullptr);
		}

		drop = dropping;

	}


void Entity::add_item_stats(shared_ptr<Item> i)
{
	switch(i->item_type)
		{
			case weapon:
			dmg += i->item_stat;
			break;
			case armor:
			df += i->item_stat;
			break;
			case useable:
			break;
			default:
			cout << "Item type does not exist in this section of code" << endl;
			break;
		}
}


void Entity::remove_item_stats(shared_ptr<Item> i)
{
	switch(i->item_type)
	{
		case weapon:
		dmg -= i->item_stat;
		break;
		case armor:
		df -= i->item_stat;
		break;
		case useable:
		break;
		default:
		cout << "Item type does not exist in this section of code" << endl;
		break;
	}
}

void Entity::equip_item(shared_ptr<Item> item, int slot)
{
	if(slot > 3) cout << "Inventory slot doesn't exist" << endl;
	else
	{
		if(!this->remove_item(slot))
		{
			Inventory[slot-1] = item;
			this->add_item_stats(Inventory[slot-1]);
		}
		else cout << "Can't find the item" << endl;

	}
}


int Entity::remove_item(int slot)
{
	if(slot > 3) cout << "Inventory slot doesn't exist" << endl;
	else
	{
		if(Inventory[slot-1] != nullptr) 
		{
			this->remove_item_stats(Inventory[slot-1]);
			Inventory[slot-1] = nullptr;
		}
	}
	return 0;
}


void Entity::print_stats()
	{
		cout << "===== " << name << " == Lvl: " << get_lvl() << " =====" << endl;
		cout << "|| HP: " << get_hp() << "/" << get_maxhp() << endl;
	}

void Entity::take_dmg(unsigned int dmg_taken) 
	{	
		int dmg_after_df = dmg_taken - (int) df*0.2;
		if(dmg_after_df < 1) hp -= 1;
		else hp -= (dmg_taken - (int) df*0.2);
	}

int Entity::deal_dmg()
	{
		int x = rand()%ATCK_RANGE + get_dmg() - 2;
		if(x<1) x = 1;
		cout << name << " attacks for " << x << " points of dmg." << endl;
		return x;
	}

void Entity::lvl_scale()
	{
		lvl++;
		max_hp += HP_BIG_SCALAR + (lvl-1) * HP_SMALL_SCALAR;
		hp = max_hp;
		dmg += DMG_BIG_SCALAR + (lvl-1) * DMG_SMALL_SCALAR;
		df += DF_BIG_SCALAR + (lvl-1) * DF_SMALL_SCALAR;
	}

void Entity::heal_dmg(unsigned int heal_value)
{
	if(heal_value > max_hp) hp = max_hp;
	else hp += heal_value;	
}

shared_ptr<Item> Entity::drop_item()
{
	return this->drop;
}


Player::Player(string pname, unsigned int plvl, unsigned int php, unsigned int pdmg, unsigned int pdf) : Entity(pname, plvl, php, pdmg, pdf)
	{
		xp = BASE_XP;
		xp_cap = BASE_XP_CAP + XP_SCALAR + XP_LVLSCALAR * (plvl-1);
	}

void Player::print_stats()
	{
		cout << "===== " << get_name() << " == Lvl: " << get_lvl() << " =====" << endl;
		cout << "|| XP: " << xp << "/" << xp_cap << endl;
		cout << "|| HP: " << get_hp() << "/" << get_maxhp() << endl;
		cout << "|| Inventory: |";
		for(unsigned int i = 0; i < Inventory.size(); i++)
		{
			cout << i+1 << ". ";
			if(Inventory[i] != nullptr) cout << Inventory[i]->item_name;
			else cout << "Empty slot";
			cout << " |";
		}
		cout << endl;
		cout << "DMG: " << get_dmg() << endl;
		cout << "ARMOR: " << get_df() << endl;
	}

void Player::xp_increase(unsigned int enemy_xpval, unsigned int enemy_lvl)
	{
		int lvl_diff = get_lvl() - enemy_lvl;
		int xp_gained;

		if(lvl_diff < 4 && lvl_diff >= -3) xp_gained = (enemy_xpval - 0.25*lvl_diff*enemy_xpval);
		else if(lvl_diff < -3) xp_gained = 2*enemy_xpval;
		else xp_gained = 0; 

		xp += xp_gained;
		cout << "+" << xp_gained << " XP gained!" << endl;
		
		if(xp >= xp_cap)
		{
			lvl_scale();
			cout << "You've reached level " << get_lvl() << "!\n";
			xp = 0;
			xp_cap += XP_SCALAR + XP_LVLSCALAR * (get_lvl() - 1);
		}
		
	}