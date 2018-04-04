#include "../include/Granaten.hpp"

Granaten::Granaten() : Item("GRANATEN!"){
}

void Granaten::Effect(CombatUnit* target){
	target->ModifyHealth(-10);
}
