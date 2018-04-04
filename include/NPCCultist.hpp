
#ifndef NPCCULTIST_HPP
#define NPCCULTIST_HPP

#include "Enemy.hpp"

class NPCCultist:public Enemy{
	public:
		NPCCultist();
		NPCCultist(std::string name, int health, int damageMod);
		void TakeTurn(CombatUnit* target);
};

#endif
