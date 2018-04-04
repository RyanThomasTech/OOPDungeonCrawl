#ifndef ABERRATION_HPP
#define ABERRATION_HPP

#include "Enemy.hpp"

class Aberration:public Enemy{
	protected:
		void BloodThinning(CombatUnit* target);
	public:
		Aberration();
		Aberration(std::string name, int health, int damageMod);
		void TakeTurn(CombatUnit* target);
};

#endif
