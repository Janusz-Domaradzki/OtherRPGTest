#ifndef CHARACTER_HH
#define CHARACTER_HH

#include "Item.hh"
#include <vector>

#define BASE_XP 0
#define BASE_XP_CAP 15
#define XP_SCALAR 5
#define XP_LVLSCALAR 2

#define HP_BIG_SCALAR 5
#define HP_SMALL_SCALAR 0.5
#define DMG_BIG_SCALAR 1
#define DMG_SMALL_SCALAR 0.05
#define DF_BIG_SCALAR 0.2
#define DF_SMALL_SCALAR 0.01
#define ATCK_RANGE 4

class Entity
{
	int lvl, max_lvl;
	int hp, max_hp;
	int dmg;
	int df;
	string name;

	int xp_val;

	public:

	shared_ptr<Item> Inventory;

	Entity(string cname, int slvl = 1, int shp = 20, int sdmg = 5, int sdf = 2, int sxp_val = 10);

	~Entity() { if(Inventory) Inventory.reset(); }

	void equip_item(shared_ptr<Item> i);

	void clear_inventory();

	int get_lvl() {return lvl;}

	int get_hp() {return hp;}

	int get_maxhp() {return max_hp;}	

	int get_dmg() {return dmg;}

	int get_df() {return df;}

	string get_name() {return name;}

	virtual void print_stats();

	void take_dmg(int dmg_taken);

	int deal_dmg();

	void heal_dmg(int heal_value);

	void lvl_scale();

	int get_xpval() {return xp_val;}

};

class Player: public Entity
{	
	int xp;
	int xp_cap;

public:

	Player(string pname, int plvl, int php, int pdmg, int pdf);

	~Player() {;}

	virtual void print_stats();

	void xp_increase(int enemy_xpval, int enemy_lvl);
};



#endif