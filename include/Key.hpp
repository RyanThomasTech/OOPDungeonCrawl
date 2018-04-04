#ifndef KEY_HPP
#define KEY_HPP

#include "Item.hpp"

class Key : public Item{
	private:
	public:
		Key();
		void Effect(CombatUnit* target);
};

#endif
