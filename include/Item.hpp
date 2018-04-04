#ifndef ITEM_HPP
#define ITEM_HPP

#include <cstdlib>
#include <string>

#include "CombatUnit.hpp"

class Item{
	protected:
		enum itemType { potion, granaten, key };
		std::string name;
		bool active;
	public:
		bool IsActive();
		void IsActive(bool value);
		std::string GetName();
		Item(std::string name);
		virtual void Effect(CombatUnit* target) = 0;
};

#endif
