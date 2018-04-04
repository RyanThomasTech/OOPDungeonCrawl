
#include "../include/NPCSuperCultist.hpp"

NPCSuperCultist::NPCSuperCultist() : NPCCultist("Addled Cultist",10,3){
	this->turnCounter=0;
}

void NPCSuperCultist::TakeTurn(CombatUnit* target){
	std::cout<<"turn counter: "<<turnCounter<<std::endl;
	if (turnCounter%3 == 0 && turnCounter != 0){
		CastHealthDrain(target);
	} else if (this->turnCounter%2 == 0) {
		std::cout<<"Betwixt his ravings, the addled cultist begins a low, moaning chant."<<std::endl;
	} else {
		Attack(target);
	}
	turnCounter++;
}

void NPCSuperCultist::CastHealthDrain(CombatUnit* target){
	std::cout<<"The addled cultist's chant comes to a crescendo. You feel weaker."<<std::endl;
	target->ModifyHealth(-5);
	this->ModifyHealth(2);
}
