#ifndef NPCELDERENTITY_HPP
#define NPCELDERENTITY_HPP

#include "Aberration.hpp"

class NPCElderEntity : public Aberration{
	public:
		NPCElderEntity();
		void TakeTurn(CombatUnit* target);
		void BigBoiSmash(CombatUnit* target);
};

#endif
