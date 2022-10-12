#include <time.h>
#include "Character.hh"

void Fight(Player &Player1, Entity &Enemy1, bool &contact)
{
	char choice;
	while(contact)
	{
		Player1.print_stats();
		Enemy1.print_stats();
		cout << "Actions: \n 1. Attack\n";
		cout << "Choose action: ";
		cin >> choice;
		switch(choice)
		{
			case '1':
			Enemy1.take_dmg(Player1.deal_dmg());
			break;
			default:
			cout << "You don't have that action!" << endl;
			continue;
			break;
		}

		if(Enemy1.get_hp() <= 0) 
			{
				cout << "You've defeated " << Enemy1.get_name() << "!\n";
				Player1.xp_increase(Enemy1.get_xpval(), Enemy1.get_lvl());
				contact = false;
				break;
			}

		Player1.take_dmg(Enemy1.deal_dmg());

		if(Player1.get_hp() <= 0)
		{
			cout << "You've been defeated!" << endl;contact = false;

			break;
		}

	}
}

int main()
{
	srand(time(NULL));
	shared_ptr<Item> Battle_Axe = make_shared<Item>("Battle Axe", weapon, 2);
	shared_ptr<Item> Bronze_Helmet = make_shared<Item>("Bronze Helmet", armor, 1);

	string player_name;
	cout << "Hello! Choose your character name: ";
	cin >> player_name;
	
	Player Player1(player_name, 1, 20, 4, 2);
	Entity Enemy1("Enemy", 1, 15, 3, 2, 10);

	bool contact = true;

	Player1.equip_item(Battle_Axe);

	Player1.clear_inventory();

	Fight(Player1, Enemy1, contact);

	Player1.print_stats();

	return 0;
}