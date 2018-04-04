#include "../include/NPCCultist.hpp"

NPCCultist::NPCCultist() : Enemy("Cultist", 8, 1){
	this->turnCounter=0;
}

NPCCultist::NPCCultist(std::string name, int health, int damageMod) : Enemy(name, health, damageMod){
}

void NPCCultist::TakeTurn(CombatUnit* target){
	if (turnCounter%2==0){
		Attack(target);
	} else {
		std::cout<<"The cultist raves and babbles to himself incoherently."<<std::endl;
	}
	turnCounter++;
}
