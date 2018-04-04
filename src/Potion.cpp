#include "../include/Potion.hpp"

Potion::Potion() : Item("Potion"){
}

void Potion::Effect(CombatUnit* target){
	target->ModifyHealth(5);
}
