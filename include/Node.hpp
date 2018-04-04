#ifndef NODE_HPP
#define NODE_HPP

#include "Enemy.hpp"

#include <cstdlib>
#include <vector>

class Node {
	private:
		int createdOrder;
		bool southWall;
		bool northWall;
		bool eastWall;
		bool westWall;
		int debrisVal;
		bool hasItem;
		bool hasCombat;
		std::vector<Enemy*> enemiesInRoom;

	public:
		std::vector<Enemy*> GetEnemies();
		void AddEnemy(Enemy* enemy);
		bool HasItem();
		bool HasCombat();
		void HasItem(bool value);
		void SetDebrisVal(int value);
		int GetDebrisVal();
		bool visited;
		Node(int createdOrder);
		int GetCreatedOrder();
		bool HasSouthWall();
		bool HasNorthWall();
		bool HasEastWall();
		bool HasWestWall();
		void DemolishWall(bool north, bool south, bool east, bool west);
};

#endif
