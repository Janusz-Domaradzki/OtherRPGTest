#include "Character.hh"


Entity::Entity(string cname, int slvl, int shp, int sdmg, int sdf, int sxp_val)
	{
		lvl = slvl;
		hp = shp + (lvl-1) * HP_BIG_SCALAR + (lvl-1) * HP_SMALL_SCALAR;
		dmg = sdmg + (lvl-1) * DMG_BIG_SCALAR + (lvl-1) * DMG_SMALL_SCALAR;
		df = sdf + (lvl-1) * DF_BIG_SCALAR + (lvl-1) * DF_SMALL_SCALAR;

		max_hp = hp;

		name = cname;

		xp_val = sxp_val;


	}

void Entity::equip_item(shared_ptr<Item> i)
{
	Inventory = i;
	switch(Inventory->item_type)
	{
		case weapon:
		dmg += Inventory->item_stat;
		break;
		case armor:
		df += Inventory->item_stat;
		break;
		case useable:
		break;
		default:
		cout << "Item type does not exist in this section of code" << endl;
		break;
	}
}

void Entity::clear_inventory()
{
	switch(Inventory->item_type)
	{
		case weapon:
		dmg -= Inventory->item_stat;
		break;
		case armor:
		df -= Inventory->item_stat;
		break;
		case useable:
		break;
		default:
		cout << "Item type does not exist in this section of code" << endl;
		break;
	}
	Inventory = nullptr;
}


void Entity::print_stats()
	{
		cout << "===== " << name << " == Lvl: " << get_lvl() << " =====" << endl;
		cout << "|| HP: " << get_hp() << "/" << get_maxhp() << endl;
	}

void Entity::take_dmg(int dmg_taken) 
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

void Entity::heal_dmg(int heal_value)
{
	if(heal_value > max_hp) hp = max_hp;
	else hp += heal_value;	
}

Player::Player(string pname, int plvl, int php, int pdmg, int pdf) : Entity(pname, plvl, php, pdmg, pdf)
	{
		xp = BASE_XP;
		xp_cap = BASE_XP_CAP + XP_SCALAR + XP_LVLSCALAR * (plvl-1);
	}

void Player::print_stats()
	{
		cout << "===== " << get_name() << " == Lvl: " << get_lvl() << " =====" << endl;
		cout << "|| XP: " << xp << "/" << xp_cap << endl;
		cout << "|| HP: " << get_hp() << "/" << get_maxhp() << endl;
		cout << "|| Inventory: ";
		if(!Inventory)  cout << "Empty" << endl;
		else cout << Inventory->item_name << endl;
		//cout << "DMG: " << get_dmg() << endl;
		//cout << "ARMOR: " << get_df() << endl;
	}

void Player::xp_increase(int enemy_xpval, int enemy_lvl)
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