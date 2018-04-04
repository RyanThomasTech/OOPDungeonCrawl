#include "../include/Item.hpp"

Item::Item(std::string name){
	this->name = name;
	active = false;
}

std::string Item::GetName(){
	return name;
}

bool Item::IsActive(){
	return active;
}

void Item::IsActive(bool value){
	active=value;
}
