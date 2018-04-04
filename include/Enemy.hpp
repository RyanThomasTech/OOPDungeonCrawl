#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "CombatUnit.hpp"

class Enemy:public CombatUnit{
	protected:
		int turnCounter;
		bool active;
	public:
		bool IsActive();
		void IsActive(bool value);
		Enemy(std::string name, int health, int damageMod);
		std::string name;
		virtual void TakeTurn(CombatUnit* target) = 0;
};

#endif
