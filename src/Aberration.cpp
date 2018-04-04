#include "../include/Aberration.hpp"

Aberration::Aberration(std::string name, int health, int damageMod) : Enemy(name, health, damageMod){
}

Aberration::Aberration() : Enemy("Aberration", 12, 0){
}

void Aberration::BloodThinning(CombatUnit* target){
	std::cout<<"Confronted with the affront to reality, you feel your pulse rising and head swimming. You need to get away from here."<<std::endl;
	target->ModifyHealth(-1);
}

void Aberration::TakeTurn(CombatUnit* target){
	if (turnCounter%3==0){
		std::cout<<"The figure in front of you wobbles, as if viewed through rippling water. Something feels horribly wrong."<<std::endl;
	}
	BloodThinning(target);
	turnCounter++;
}


