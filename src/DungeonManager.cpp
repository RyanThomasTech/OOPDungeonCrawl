#include "../include/DungeonManager.hpp"
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <random>
#include <algorithm>


DungeonManager::DungeonManager(Gameworld* world){
	this->world = world;
	map = world->GetMap();
	seed = std::chrono::system_clock::now().time_since_epoch().count();
	InitializeDifficultyVars();
	CreateRoomsVector();
	PopulateDebris();
	PopulateItems();
	PopulateEnemies();
}

void DungeonManager::InitializeDifficultyVars(){
	
	//if difficulty or map size were optional, those options would affect initialization here
	debrisSculptureCount=3;
	debrisStorageCount=5;
	debrisRemainsCount=6;
	itemsPotionCount=4;
	itemsGranatenCount=3;
	itemsKeyCount=5;
	enemiesInitiateCount=6;
	enemiesCultistCount=4;
	enemiesSuperCultistCount=2;
	enemiesDaemonCount=2;
	enemiesAberrationCount=3;
}

void DungeonManager::Play(){
	world->Play();
}

void DungeonManager::CreateRoomsVector(){
	for (int i = 1; i<24; i++){		//don't add 0 or 24(final room) to the list
		genericRooms.push_back(i);
	}
}

void DungeonManager::PopulateItems(){
	shuffle (debrisRooms.begin(), debrisRooms.end(), std::default_random_engine(seed));
	for (int i : debrisRooms){
		Node* room = map->AccessRoom(i);
		if (!room->HasItem()){
			if (itemsPotionCount>0){	//there is currently no linkage between items
				room->HasItem(true);	//and rooms, but this framework for spawning
				itemsPotionCount--;	//would be useful if there were
				world->itemsInWorld.push_back(new Potion());
			} else if (itemsGranatenCount>0){
				room->HasItem(true);
				itemsGranatenCount--;
				world->itemsInWorld.push_back(new Granaten());
			} else if (itemsKeyCount>0){
				room->HasItem(true);
				itemsKeyCount--;
				world->itemsInWorld.push_back(new Key());
			} else {
				shuffle (world->itemsInWorld.begin(), world->itemsInWorld.end(), std::default_random_engine(seed));
				break;
			}
		}
	}
}

void DungeonManager::PopulateDebris(){
	//storing an array of ints, then loading nodes seems
	shuffle (genericRooms.begin(), genericRooms.end(), std::default_random_engine(seed));
	for (int i : genericRooms){		//inefficient. Maybe there's a better way.
		Node* room = map->AccessRoom(i);
		if (room->GetDebrisVal()==0){
			if (debrisSculptureCount>0){
				room->SetDebrisVal(1);
				debrisSculptureCount--;
			} else if (debrisStorageCount>0){
				room->SetDebrisVal(2);
				debrisStorageCount--;
			} else if (debrisRemainsCount>0){
				room->SetDebrisVal(3);
				debrisRemainsCount--;
			} else {
				break;
			}
			debrisRooms.push_back(i);
		}
	}
}

void DungeonManager::PopulateEnemies(){
	//srand(time(NULL));
	FillEnemyVector();
	shuffle (enemiesVector.begin(), enemiesVector.end(), std::default_random_engine(seed));
	shuffle (genericRooms.begin(), genericRooms.end(), std::default_random_engine(seed));
	int enemiesInRoom = 0;
	for (int i : genericRooms){
		Node* room = map->AccessRoom(i);
		if ( enemiesVector.empty() ){
			break;
		}

		/*int enemyAmtDetermine = rand()%6 +1;
		if ( enemyAmtDetermine == 6){
			enemiesInRoom=2;
		}*/

		enemiesInRoom=1;
		while (enemiesInRoom>0 && !enemiesVector.empty()){
			room->AddEnemy(enemiesVector.front());
			enemiesVector.erase(enemiesVector.begin());
			enemiesInRoom--;
		}
	}
	
	//populate boss
	Node* bossRoom = map->AccessRoom(24);
	bossRoom->AddEnemy(new NPCElderEntity());
}

void DungeonManager::FillEnemyVector(){
	while (enemiesInitiateCount>0){
		enemiesVector.push_back(new NPCInitiate());
		enemiesInitiateCount--;
	}
	while (enemiesCultistCount>0){
		enemiesVector.push_back(new NPCCultist());
		enemiesCultistCount--;
	}
	while (enemiesSuperCultistCount>0){
		enemiesVector.push_back(new NPCSuperCultist());
		enemiesSuperCultistCount--;
	}
	while (enemiesDaemonCount>0){
		enemiesVector.push_back(new NPCDaemon());
		enemiesDaemonCount--;
	}
	while (enemiesAberrationCount>0){
		enemiesVector.push_back(new Aberration());
		enemiesAberrationCount--;
	}
}
