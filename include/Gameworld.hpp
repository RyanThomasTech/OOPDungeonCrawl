#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include "Graph.hpp"
#include "CombatUnit.hpp"
#include "PlayerCharacter.hpp"
#include "Item.hpp"

class Gameworld{
	public:
		Gameworld();
		std::vector<Item*> itemsInWorld;
		Graph* GetMap();
		void Play();
	private:
		PlayerCharacter* player;
		Graph* map;
		void CoreGameplayLoop();
		int playerLocationNodeNumber;
		enum encounterStatus { 	gameover, roaming, dialogue, combat };
		enum userCommand { 	invalid, north, south, east, west, search,
					take, leave, open, inventory, 
					light, heavy, physical, granaten, potion, empty,
					attack, defend, item };
		encounterStatus currentGameState;
		void PrintEnemiesInRoom(Node* currentRoom);
		void PrintRoamingMessage(Node* currentRoom);
		void PrintSearchFailure();
		void PrintDebrisMessage(Node* currentRoom);
		void PrintWallsOfRoom(Node* currentRoom);
		void PrintPlayerInventory();
		void ActivateItemGiveToPlayer(PlayerCharacter* player, bool playerTakesItem);
		void ItemPickupDialogue();
		userCommand ParseUserInput();
		void RoamingLoop();
		void DialogueLoop();
		void CombatLoop();
		bool ActionIsValidInThisRoom(userCommand action, Node* currentRoom);
		void PerformAction(userCommand action, Node* currentRoom);
		void PerformCombatAction(userCommand action, CombatUnit* enemy);
		bool VerifyRoamingActions(userCommand action, Node* currentRoom);
		bool VerifyDialogueActions(userCommand action, Node* room);
		userCommand VerifyCombatActions();
};

#endif
