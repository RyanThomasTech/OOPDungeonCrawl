#include "../include/NPCElderEntity.hpp"

NPCElderEntity::NPCElderEntity() : Aberration("Elder Entity", 15, 5){
}

void NPCElderEntity::TakeTurn(CombatUnit* target){
	if (turnCounter%4==0 && turnCounter!=0){
		BigBoiSmash(target);
	} else if (turnCounter%2==0){
		Attack(target);
	} else {
		std::cout<<"Your resolution wanes as the entity in front of you echoes thunderously through your psyche."<<std::endl;
	}
	BloodThinning(target);
	turnCounter++;
}

void NPCElderEntity::BigBoiSmash(CombatUnit* target){
	std::cout<<"Big boi smash activated!"<<std::endl;
	target->ModifyHealth(-8);
}
