#ifndef POTION_HPP
#define POTION_HPP

#include "Item.hpp"

class Potion: public Item{
	public:
		Potion();
		void Effect(CombatUnit* target);
};

#endif
