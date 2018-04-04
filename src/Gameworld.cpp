#include "../include/Gameworld.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <regex>

Gameworld::Gameworld(){
	std::cout<<"Creating map."<<std::endl;
	map = new Graph(25);
	player = new PlayerCharacter();
	std::cout<<"Map created."<<std::endl;
	playerLocationNodeNumber=0;
	currentGameState = roaming;
}

Graph* Gameworld::GetMap(){
	return map;
}

void Gameworld::Play(){
	std::cout<<"You awake on the cold stone floor with a killer headache. Your new robes are covered in vomit and blood--you wonder how much of it is yours. You stand up as the memories flood back to you. After briefly wondering where your shoes went, you begin to regret your decisions to join that death cult. You should get out of here."<<std::endl;
	CoreGameplayLoop();
}

void Gameworld::CoreGameplayLoop(){
	while(currentGameState!=gameover){
		switch(currentGameState) {
			case roaming:
				RoamingLoop();
				break;
			case dialogue:
				DialogueLoop();
				break;
			case combat:
				CombatLoop();
				break;
			default:
				break;
		}
	}
	std::cout<<"Game over. Thanks for playing!"<<std::endl;
}

void Gameworld::RoamingLoop(){
	while(currentGameState==roaming){
		Node* currentRoom = map->AccessRoom(playerLocationNodeNumber);
		if (currentRoom->HasCombat()){
			currentGameState=combat;
			break;
		}
		if (playerLocationNodeNumber==24){
			currentGameState=gameover;
			std::cout<<"You see a set of stairs leading up to a doorway. You follow it, and emerge into the kitchen of a nice, suburban ranch home. A kindly looking older woman asks if you're one of \"Tommy's friends\" and offers you some leftovers from last night's spaghetti dinner. You politely refuse and thank her for having you over before you slip out the front door. You made it!"<<std::endl;
			break;
		}
		PrintRoamingMessage(currentRoom);
		userCommand action = ParseUserInput();
		if(ActionIsValidInThisRoom(action, currentRoom)){
			PerformAction(action, currentRoom);
		} else {
			std::cout<<"You can't do that right now."<<std::endl;
		}
	}
}

void Gameworld::CombatLoop(){
	while (currentGameState==combat){
		Node* currentRoom = map->AccessRoom(playerLocationNodeNumber);
		PrintEnemiesInRoom(currentRoom);
		Enemy* enemy = currentRoom->GetEnemies().front();
		userCommand action = VerifyCombatActions();
		PerformCombatAction(action, enemy);
		if (!enemy->IsAlive()){
			std::cout<<"It seems as if you've survived."<<std::endl;
			enemy->IsActive(false);
			currentGameState=roaming;
			break;
		}
		enemy->TakeTurn(player);
		if (!player->IsAlive()){
			std::cout<<"Your vision fades to black..."<<std::endl;
			currentGameState=gameover;
		}
	}
}

void Gameworld::DialogueLoop(){		//TODO: break into multiple dialogue states to prevent overlap
	while (currentGameState==dialogue){
		Node* currentRoom = map->AccessRoom(playerLocationNodeNumber);
		userCommand action = ParseUserInput();
		if(ActionIsValidInThisRoom(action, currentRoom)){
			PerformAction(action, currentRoom);
		} else {
			std::cout<<"You can't do that right now."<<std::endl;
		}
	}
}


void Gameworld::PrintRoamingMessage(Node* currentRoom){
	PrintWallsOfRoom(currentRoom);
	PrintDebrisMessage(currentRoom);
	std::cout<<"{NORTH, SOUTH, EAST, WEST} to traverse"<<std::endl;
	std::cout<<"{SEARCH, INVENTORY}"<<std::endl;
}

void Gameworld::PrintEnemiesInRoom(Node* currentRoom){
	std::cout<<"You are face to face with... "<<std::endl;
	for (Enemy* enemy : currentRoom->GetEnemies()){
		std::cout<<enemy->GetName()<<": "<<enemy->GetHealth()<<std::endl;
	}
	std::cout<<"Player health: "<<player->GetHealth()<<std::endl;
}

void Gameworld::PrintWallsOfRoom(Node* currentRoom){
	std::cout<<"You see corridors leading in the ";
	if (!currentRoom->HasNorthWall()){
		std::cout<<"NORTH ";
	}
	if (!currentRoom->HasSouthWall()){
		std::cout<<"SOUTH ";
	}
	if (!currentRoom->HasEastWall()){
		std::cout<<"EAST ";
	}
	if (!currentRoom->HasWestWall()){
		std::cout<<"WEST ";
	} 
	std::cout<<" directions."<<std::endl;
}

void Gameworld::PrintDebrisMessage(Node* currentRoom){
	switch(currentRoom->GetDebrisVal()){
		case 0:
			std::cout<<"The room is clearly empty"<<std::endl;
			break;
		case 1:
			std::cout<<"There is rubble and debris throughout the room. Part of the ceiling seems to have collapsed."<<std::endl;
			break;
		case 2:
			std::cout<<"There are crates and barrels filled with various goods and supplies in this room."<<std::endl;
			break;
		case 3:
			std::cout<<"This room has been filled with the bleached remains of a variety of once-living creatures."<<std::endl;
			break;
		default:
			std::cout<<"Incorrect decoration value detected."<<std::endl;
			break;
	}
}

Gameworld::userCommand Gameworld::ParseUserInput(){
	userCommand cmd;
	std::string userInput;
	std::regex rgxNorth ("[Nn][A-Za-z]+[Hh]$");
	std::regex rgxEast ("(EAST|east)");
	std::regex rgxSouth ("[Ss][OUTout]*[Hh]$");
	std::regex rgxWest ("[Ww][A-Za-z]+[Tt]$");
	std::regex rgxTake ("^[Tt][Aa][Kk][Ee]");
	std::regex rgxLeave ("^[Ll][A-Za-z]+[Ee]");
	std::regex rgxSearch("^[Ss][A-Za-z]+[Hh]");
	std::regex rgxInventory("[Ii][A-Za-z]+[Yy]$");
	std::regex rgxLight("(LIGHT|light)");
	std::regex rgxHeavy("(HEAVY|heavy)");
	std::regex rgxPhysical("^[Pp][HYSICAhysica]+[Ll]");
	std::regex rgxGranaten("^[Gg][A-Za-z]+[Nn]");
	std::regex rgxPotion("(POTION|potion)");
	std::regex rgxAttack("(ATTACK|attack)");
	std::regex rgxDefend("(DEFEND|defend)");
	std::regex rgxItem("(ITEM|item)");

	while (userInput.length()==0){	//prevents blank input
		getline(std::cin,userInput);
	}

	if (std::regex_search(userInput, rgxNorth)){
		//std::cout<<"matched north"<<std::endl;
		cmd = north;
		return cmd;
	} else if(std::regex_search(userInput, rgxSouth)){
		//std::cout<<"matched south"<<std::endl;
		cmd = south;
		return cmd;
	} else if(std::regex_search(userInput, rgxEast)){
		//std::cout<<"matched east"<<std::endl;
		cmd = east;
		return cmd;
	} else if(std::regex_search(userInput, rgxWest)){
		//std::cout<<"matched west"<<std::endl;
		cmd = west;
		return cmd;
	} else if(std::regex_search(userInput, rgxSearch)){
		//std::cout<<"matched search"<<std::endl;
		cmd = search;
		return cmd;
	} else if(std::regex_search(userInput, rgxTake)){
		//std::cout<<"matched take"<<std::endl;
		cmd = take;
		return cmd;
	} else if(std::regex_search(userInput, rgxLeave)){
		//std::cout<<"matched leave"<<std::endl;
		cmd = leave;
		return cmd;
	} else if(std::regex_search(userInput, rgxInventory)){
		//std::cout<<"matched inventory"<<std::endl;
		cmd = inventory;
		return cmd;
	} else if(std::regex_search(userInput, rgxLight)){
		//std::cout<<"matched light"<<std::endl;
		cmd = light;
		return cmd;
	} else if(std::regex_search(userInput, rgxHeavy)){
		//std::cout<<"matched heavy"<<std::endl;
		cmd = heavy;
		return cmd;
	} else if(std::regex_search(userInput, rgxPhysical)){
		//std::cout<<"matched physical"<<std::endl;
		cmd = physical;
		return cmd;
	} else if(std::regex_search(userInput, rgxGranaten)){
		//std::cout<<"matched granaten"<<std::endl;
		cmd = granaten;
		return cmd;
	} else if(std::regex_search(userInput, rgxPotion)){
		//std::cout<<"matched potion"<<std::endl;
		cmd = potion;
		return cmd;
	} else if(std::regex_search(userInput, rgxAttack)){
		//std::cout<<"matched attack"<<std::endl;
		cmd = attack;
		return cmd;
	} else if(std::regex_search(userInput, rgxDefend)){
		//std::cout<<"matched defend"<<std::endl;
		cmd = defend;
		return cmd;
	} else if(std::regex_search(userInput, rgxItem)){
		//std::cout<<"matched item"<<std::endl;
		cmd = item;
		return cmd;
	} else {
		//std::cout<<"no match"<<std::endl;
		cmd = invalid;
		return cmd;
	}
}

bool Gameworld::ActionIsValidInThisRoom(userCommand action, Node* room){
	if (action==invalid){
		std::cout<<"invalid action state detected."<<std::endl;
		return false;
	} else if (currentGameState==roaming){
		return VerifyRoamingActions(action, room);
	} 
       	if (currentGameState==dialogue){
		return VerifyDialogueActions(action, room);
	} 
	//combat verification goes through another rout, as it does not require room
	return false;
}

void Gameworld::PerformAction(userCommand action, Node* currentRoom){
	switch(action){
		case north:
			playerLocationNodeNumber+=5;
			break;
		case south:
			playerLocationNodeNumber-=5;
			break;
		case east:
			playerLocationNodeNumber+=1;
			break;
		case west:
			playerLocationNodeNumber-=1;
			break;
		case search:
			if (currentRoom->HasItem()){
				currentGameState=dialogue;
				ItemPickupDialogue();
				break;
			}
			PrintSearchFailure();
			break;
		case take:
			ActivateItemGiveToPlayer(player, true);
			currentRoom->HasItem(false);
			currentGameState=roaming;
			break;
		case leave:
			ActivateItemGiveToPlayer(player, false);
			currentRoom->HasItem(false);
			currentGameState=roaming;
			break;
		case inventory:
			PrintPlayerInventory();
			break;
		default:
			std::cout<<"Action not listed in PerformAction(action, room)"<<std::endl;
			break;
	}
}

void Gameworld::PerformCombatAction(userCommand action, CombatUnit* enemy){
	player->IsDefending(false);	//whenever player starts turn, deactivate defense

	switch(action){
		case light:
			player->LightAttack(enemy);
			break;
		case heavy:
			player->HeavyAttack(enemy);
			break;
		case physical:
			player->Brace();
			break;
		case granaten:
			player->UseItem("GRANATEN!", enemy);
			break;
		case potion:
			player->UseItem("Potion", player);
			break;
		case empty:
			std::cout<<"You don't have that item."<<std::endl;
			break;
	}
}			

void Gameworld::PrintPlayerInventory(){
	player->PrintInventory();
}


void Gameworld::ActivateItemGiveToPlayer(PlayerCharacter* player, bool playerTakesItem){
	for (Item* item : itemsInWorld){
		if (!item->IsActive()){
			item->IsActive(true);
			if (playerTakesItem){
				player->TakeItem(item);
				std::cout<<"You got a "<<item->GetName()<<std::endl;
			}
			break;
		}
	}
}

void Gameworld::ItemPickupDialogue(){
	std::cout<<"While searching through the rubble, you find a ";
	for (Item* item : itemsInWorld){
		if (!item->IsActive()){	
			std::cout<<item->GetName();
			break;
		}
	}
	std::cout<<". Do you take it?"<<std::endl;
	std::cout<<"{TAKE, LEAVE}"<<std::endl;
}

void Gameworld::PrintSearchFailure(){
	std::cout<<"You search through the debris, but find nothing."<<std::endl;
}

Gameworld::userCommand Gameworld::VerifyCombatActions(){
	std::cout<<"{ATTACK, DEFEND, ITEM}"<<std::endl;
	userCommand action = ParseUserInput();
	switch(action){
		case attack:
			break;
		case defend:
			break;
		case item:
			break;
		default:
			std::cout<<"In a panic, you attack!"<<std::endl;
			action = attack;
			break;
	}
	
	switch(action){
		case attack:
			std::cout<<"{LIGHT, HEAVY}"<<std::endl;
			break;
		case defend:
			std::cout<<"{PHYSICAL, MENTAL}"<<std::endl;
			break;
		case item:
			std::cout<<"{GRANATEN!, POTION}"<<std::endl;
			break;
	}

	userCommand combatAction = ParseUserInput();
	
	switch(action){
		case attack:
			switch(combatAction){
				case light:
					return light;
					break;
				case heavy:
					return heavy;
					break;
				default:
					return light;
					break;
			}
			break;
		case defend:
			return physical;
			break;
		case item:
			switch(combatAction){
				case granaten:
					if (player->HasItem("GRANATEN!")){
							return granaten;
							break;
					}
					return empty;
					break;
				case potion:
					if (player->HasItem("Potion")){
						return potion;
						break;
					}
					return empty;
					break;
				default:
					return empty;
					break;
			}
			break;
		default:
			std::cout<<"invalid second combat selection"<<std::endl;
			break;
	}
}


bool Gameworld::VerifyDialogueActions(userCommand action, Node* room){
	switch(action){
		case take:
			if (room->HasItem()){
				return true;
			}
			return false;
			break;
		case leave:
			if (room->HasItem()){
				return true;
			}
			return false;
			break;
	}
}

bool Gameworld::VerifyRoamingActions(userCommand action, Node* room){
	switch(action){
		case north: 
			if (room->HasNorthWall()){
				return false;
			}
			return true;
			break;
		case south:
			if (room->HasSouthWall()){
				return false;
			} 
			return true;
			break;
		case east:
			if (room->HasEastWall()){
				return false;
			}
			return true;
			break;
		case west:
			if (room->HasWestWall()){
				return false;
			} 
			return true;
			break;
		case search:
			if (room->GetDebrisVal()>0){
				return true;
			}
			return false;
			break;
		case inventory:
			return true;
			break;
		default:
			return false;
			break;
	}
}
