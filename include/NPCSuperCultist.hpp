#ifndef NPCSUPERCULTIST_HPP
#define NPCSUPERCULTIST_HPP

#include "NPCCultist.hpp"

class NPCSuperCultist:public NPCCultist{
	protected:
		void CastHealthDrain(CombatUnit* target);
	public:
		NPCSuperCultist();
		void TakeTurn(CombatUnit* target);
};

#endif
