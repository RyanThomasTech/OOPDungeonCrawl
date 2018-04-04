#include "../include/PlayerCharacter.hpp"

PlayerCharacter::PlayerCharacter() : CombatUnit("Player", 25, 3){
	srand (time(NULL));
}

void PlayerCharacter::TakeItem(Item* item){
	inventory.push_back(item);
}

void PlayerCharacter::PrintInventory(){
	std::cout<<"Rummaging through your bag, you find..."<<std::endl;
	for (Item* item : inventory){
		std::cout<<item->GetName()<<std::endl;
	}
}

bool PlayerCharacter::HasItem(std::string itemname){
	for (Item* item : inventory){
		if (item->GetName() == itemname){
			return true;
		}
	}
	return false;
}

void PlayerCharacter::UseItem(std::string itemName, CombatUnit* target){
	if (!this->HasItem(itemName)){
		std::cout<<"invalid item used"<<std::endl;
	} else {
		for (Item* item : inventory){
			if (item->GetName()==itemName){
				item->Effect(target);
				delete item;
				break;
			}
		}
	}
}

void PlayerCharacter::LightAttack(CombatUnit* target){
	this->Attack(target);
}

void PlayerCharacter::HeavyAttack(CombatUnit* target){
	int hitRoll = rand()%3 + 1;
	std::cout<<"You wind up for a big swing and... ";
	if (hitRoll==1){
		std::cout<<"you missed!"<<std::endl;
	} else {
		std::cout<<"you hit!"<<std::endl;
		int damage = -(this->damageMod*2);
		target->ModifyHealth(-10);
	}
}

void PlayerCharacter::Brace(){
	this->IsDefending(true);
}
