#include "../include/CombatUnit.hpp"


CombatUnit::CombatUnit(std::string name, int health, int damageMod){
	this->health = health;
	this->damageMod = damageMod;
	this->name = name;
	defending = false;
}

void CombatUnit::Attack(CombatUnit* target){
	if (target->IsDefending()){
		std::cout<<target->name<<" defends against the attack!"<<std::endl;
		target->IsDefending(false);
	} else {
		target->ModifyHealth(-damageMod);
		std::cout<<name<<" attacks!"<<std::endl;
	}
}

void CombatUnit::ModifyHealth(int change){
	health+=change;
}

std::string CombatUnit::GetName(){
	return name;
}

int CombatUnit::GetHealth(){
	return health;
}

bool CombatUnit::IsAlive(){
	if (health > 0){
		return true;
	}
	return false;
}

void CombatUnit::IsDefending(bool value){
	defending = value;
}

bool CombatUnit::IsDefending(){
	return defending;
}
