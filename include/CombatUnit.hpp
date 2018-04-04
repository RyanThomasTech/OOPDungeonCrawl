#ifndef COMBATUNIT_HPP
#define COMBATUNIT_HPP

#include <cstdlib>
#include <iostream>
#include <string>

class CombatUnit{
	protected:
		std::string name;
		int health;
		int damageMod;
		bool defending;
		void Attack(CombatUnit* target);
	public:
		CombatUnit(std::string name, int health, int damageMod);
		void ModifyHealth(int change);
		int GetHealth();
		std::string GetName();
		bool IsDefending();
		void IsDefending(bool value);
		bool IsAlive();
};

#endif
