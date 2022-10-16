#include <time.h>
#include "Character.hh"




void Fight(shared_ptr<Player> Player1, shared_ptr<Entity> Enemy1, bool &contact)
{
	char choice;
	while(contact)
	{
		Player1->print_stats();
		Enemy1->print_stats();
		cout << "Actions: \n 1. Attack\n";
		cout << "Choose action: ";
		cin >> choice;
		switch(choice)
		{
			case '1':
			Enemy1->take_dmg(Player1->deal_dmg());
			break;
			default:
			cout << "You don't have that action!" << endl;
			continue;
			break;
		}

		if(Enemy1->get_hp() <= 0) 
			{
				cout << "You've defeated " << Enemy1->get_name() << "!\n";
				Player1->xp_increase(Enemy1->get_xpval(), Enemy1->get_lvl());
				contact = false;
				Enemy1.reset();
				break;
			}

		Player1->take_dmg(Enemy1->deal_dmg());

		if(Player1->get_hp() <= 0)
		{
			cout << "You've been defeated!" << endl;
			contact = false;
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
	cout << "Hello! Insert your character name: ";
	cin >> player_name;
	
	shared_ptr<Player> Player1 = make_shared<Player>(player_name, 1, 20, 4, 2);
	shared_ptr<Entity> Enemy1= make_shared<Entity>("Enemy", 1, 15, 3, 1, 10);

	bool contact = true;

	Player1->equip_item(Battle_Axe, 1); 
	cout << "Test12" << endl;
	Player1->equip_item(Bronze_Helmet, 2);

	Fight(Player1, Enemy1, contact);

	Player1->remove_item(1); 
	Player1->remove_item(2);

	Player1->print_stats();

	Enemy1.reset();
	Player1.reset();

	Battle_Axe.reset();
	Bronze_Helmet.reset();

	return 0;
}