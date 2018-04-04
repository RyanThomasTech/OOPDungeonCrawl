#ifndef PLAYERCHARACTER_HPP
#define PLAYERCHARACTER_HPP

#include "CombatUnit.hpp"
#include "Item.hpp"
#include <cstdlib>
#include <vector>
#include <iostream>
#include <random>
#include <ctime>

class PlayerCharacter:public CombatUnit{
	private:
		int health;
		int damageMod;
		std::vector<Item*> inventory;
	public:
		PlayerCharacter();
		void TakeItem(Item* item);
		void PrintInventory();
		bool HasItem(std::string item);
		void UseItem(std::string item, CombatUnit* target);
		void LightAttack(CombatUnit* target);
		void HeavyAttack(CombatUnit* target);
		void Brace();
};	

#endif
