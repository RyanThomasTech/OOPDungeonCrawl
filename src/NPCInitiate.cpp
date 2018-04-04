#include "../include/NPCInitiate.hpp"

NPCInitiate::NPCInitiate() : Enemy("Initiate",5,1){
	this->turnCounter=0;
}

void NPCInitiate::TakeTurn(CombatUnit* target){
	if (turnCounter%2==0){
		Attack(target);
	} else {
		std::cout<<"The initiate's hands shake violently and he whimpers in fear."<<std::endl;
	}
	turnCounter++;
}
