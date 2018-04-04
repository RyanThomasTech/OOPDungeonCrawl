#include "../include/Node.hpp"

Node::Node(int created){
	debrisVal = 0;
	hasItem=false;
       visited = false;
       this->createdOrder = created;
       northWall=true;
       southWall=true;
       eastWall=true;
       westWall=true;
}

bool Node::HasItem(){
	return hasItem;
}

void Node::HasItem(bool value){
	hasItem = value;
}

int Node::GetDebrisVal(){
	return debrisVal;
}

void Node::SetDebrisVal(int value){
	debrisVal = value;
}

int Node::GetCreatedOrder(){
	return createdOrder;
}

bool Node::HasSouthWall(){
	return southWall;
}

bool Node::HasNorthWall(){
	return northWall;
}

bool Node::HasEastWall(){
	return eastWall;
}

bool Node::HasWestWall(){
	return westWall;
}

void Node::DemolishWall(bool north, bool south, bool east, bool west){
	if (north){
		northWall=false;
	} else if (south){
		southWall=false;
	} else if (east){
		eastWall=false;
	} else if (west){
		westWall=false;
	}
}

std::vector<Enemy*> Node::GetEnemies(){
	return enemiesInRoom;
}

void Node::AddEnemy(Enemy* enemy){
	enemiesInRoom.push_back(enemy);
}

bool Node::HasCombat(){
	if (!enemiesInRoom.empty()){
		return enemiesInRoom.front()->IsActive();
	}
	return false;
}

