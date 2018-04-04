#include "../include/NPCDaemon.hpp"

NPCDaemon::NPCDaemon() : Aberration("Daemon", 13, 3){
}

void NPCDaemon::TakeTurn(CombatUnit* target){
	if (turnCounter%3 == 0 && turnCounter != 0){
		Attack(target);
	} else {
		std::cout<<"The daemon shimmers in your vision, fluttering in and out of this dimension"<<std::endl;
	}
	BloodThinning(target);
	turnCounter++;
}
		
