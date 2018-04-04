#ifndef GRANATEN_HPP
#define GRANATEN_HPP

#include "Item.hpp"

class Granaten : public Item{
	public:
		Granaten();
		void Effect(CombatUnit* target);
};

#endif
