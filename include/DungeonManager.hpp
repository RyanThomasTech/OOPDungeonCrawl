#ifndef DUNGEONMANAGER_HPP
#define DUNGEONMANAGER_HPP

#include "Graph.hpp"
#include "Gameworld.hpp"
#include "Item.hpp"
#include "Potion.hpp"
#include "Key.hpp"
#include "Granaten.hpp"
#include "NPCInitiate.hpp"
#include "NPCCultist.hpp"
#include "NPCSuperCultist.hpp"
#include "NPCDaemon.hpp"
#include "NPCElderEntity.hpp"

class DungeonManager {
	private:
		unsigned seed;
		std::vector<int> genericRooms;
		std::vector<int> debrisRooms;
		std::vector<Enemy*> enemiesVector;
		void InitializeDifficultyVars();
		void CreateRoomsVector();
		void FillEnemyVector();
		int debrisSculptureCount;
		int debrisStorageCount;
		int debrisRemainsCount;
		int itemsPotionCount;
		int itemsGranatenCount;
		int itemsKeyCount;
		int enemiesInitiateCount;
		int enemiesCultistCount;
		int enemiesSuperCultistCount;
		int enemiesDaemonCount;
		int enemiesAberrationCount;
		void PopulateItems();
		void PopulateDebris();
		void PopulateEnemies();
		Graph* map;
		Gameworld* world;
	public:
		void Play();
		DungeonManager(Gameworld* world);

};

#endif
