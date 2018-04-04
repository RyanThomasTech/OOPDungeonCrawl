#include "../include/Enemy.hpp"

Enemy::Enemy(std::string name, int health, int damageMod) : CombatUnit(name, health, damageMod){
	active=true;
}

bool Enemy::IsActive(){
	return active;
}

void Enemy::IsActive(bool value){
	active = value;
	turnCounter=0;
}
