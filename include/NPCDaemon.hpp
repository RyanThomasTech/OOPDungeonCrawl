#ifndef NPCDAEMON_HPP
#define NPCDAEMON_HPP

#include "Aberration.hpp"

class NPCDaemon:public Aberration{
	public:
		NPCDaemon();
		void TakeTurn(CombatUnit* target);
};

#endif
