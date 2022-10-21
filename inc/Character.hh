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
	unsigned int lvl, max_lvl;
	unsigned int hp, max_hp;
	unsigned int dmg;
	unsigned int df;
	string name;

	unsigned int xp_val;

	shared_ptr<Item> drop;	

	public:

	vector<shared_ptr<Item>> Inventory;

	Entity(string cname, unsigned int slvl = 1, unsigned int shp = 20, unsigned int sdmg = 5, 
		unsigned int sdf = 2, unsigned int sxp_val = 10, shared_ptr<Item> dropping = nullptr);

	~Entity() {;}

	void equip_item(const shared_ptr<Item> item, int slot);

	int remove_item(int slot);

	void add_item_stats(const shared_ptr<Item> i);

	void remove_item_stats(const shared_ptr<Item> i);

	int get_lvl() {return lvl;}

	int get_hp() {return hp;}

	int get_maxhp() {return max_hp;}	

	int get_dmg() {return dmg;}

	int get_df() {return df;}

	string get_name() {return name;}

	virtual void print_stats();

	void take_dmg(unsigned int dmg_taken);

	const int deal_dmg();

	void heal_dmg(unsigned int heal_value);

	void lvl_scale();

	int get_xpval() {return xp_val;}

	const shared_ptr<Item> & drop_item();

};

class Player: public Entity
{	
	unsigned int xp;
	unsigned int xp_cap;

public:

	Player(string pname, unsigned int plvl, unsigned int php, unsigned int pdmg, unsigned int pdf);

	~Player() {;}

	virtual void print_stats();

	void xp_increase(unsigned int enemy_xpval, unsigned int enemy_lvl);

};



#endif