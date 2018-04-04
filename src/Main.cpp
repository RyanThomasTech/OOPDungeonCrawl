#include "../include/DungeonManager.hpp"
#include <cstdlib>
#include <iostream>
int main(){
	std::cout<<"Starting game."<<std::endl;
	DungeonManager* dm = new DungeonManager(new Gameworld());
	dm->Play();
}
