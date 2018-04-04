#ifndef NPCINITIATE_HPP
#define NPCINITIATE_HPP

#include "Enemy.hpp"

class NPCInitiate:public Enemy{
	public:
		NPCInitiate();
		void TakeTurn(CombatUnit* target);
};

#endif
