#include <time.h>
#include "Character.hh"




void Fight(shared_ptr<Player> Player1, shared_ptr<Entity> Enemy1, bool &contact);

void Item_pick(shared_ptr<Player> Player1, shared_ptr<Entity> Enemy1);


int main()
{
	srand(time(NULL));

	shared_ptr<Item> Battle_Axe = make_shared<Item>("Battle Axe", weapon, 2);
	shared_ptr<Item> Bronze_Helmet = make_shared<Item>("Bronze Helmet", armor, 1);

	string player_name;
	cout << "Greetings! Insert your character name: ";
	cin >> player_name;
	
	shared_ptr<Player> Player1 = make_shared<Player>(player_name, 1, 20, 4, 2);
	shared_ptr<Entity> Enemy1= make_shared<Entity>("Enemy", 1, 15, 3, 1, 10, Bronze_Helmet);

	bool contact = true;

	//Player1->equip_item(Battle_Axe, 1); 
	Player1->equip_item(Battle_Axe, 1);

	Fight(Player1, Enemy1, contact);

	//Player1->remove_item(1); 
	//Player1->remove_item(2);

	Player1->print_stats();

	Player1->remove_item(1);
	Player1->remove_item(2); 

	Enemy1.reset();
	Player1.reset();

	Battle_Axe.reset();
	Bronze_Helmet.reset();

	return 0;
}



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
				Item_pick(Player1, Enemy1);
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

void Item_pick(shared_ptr<Player> Player1, shared_ptr<Entity> Enemy1)
{
	shared_ptr<Item> drop = Enemy1->drop_item();
	if(drop != nullptr)
	{
		char choice;
		cout << Enemy1->get_name() << " dropped " << drop->get_item_name() << endl;
		cout << "Do you want to equip it? (y/n): ";
		cin >> choice;
		if(choice == 'y')
		{
			int item_slot;
			char sure = 'y';
			cout << "Choose inventory slot: ";
			cin >> item_slot;
			while(Player1->Inventory[item_slot-1] != nullptr && sure == 'y')
			{
				cout << "Do you want to replace the item? (y/n): ";
				cin >> sure;
				if(sure == 'n')
				{
					cout << "Choose other slot: ";
					cin >> item_slot;
					sure = 'y';
				}
				else Player1->remove_item(item_slot);
			}
			if(sure == 'y') Player1->equip_item(drop, item_slot);	
		}
	}
}