#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "Entity.h"

using namespace std;

Entity::Entity(string id, string dest, string timeStr)  : id(id), dest(dest), timeStr(timeStr), isAssigned(false) {}

string Entity::getId() const {
	return id;
}

string Entity::getDest() const {
	return dest;
}

string Entity::getTimeStr() const {
	return timeStr;
}

bool Entity::getIsAssigned() const {
	return isAssigned;
}

void Entity::setAssigned(bool assigned) {
	isAssigned = assigned;
}