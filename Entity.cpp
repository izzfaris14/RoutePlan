#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "Entity.h"

using namespace std;

Entity::Entity(string id, string dest, string timeStr)  : id(id), dest(dest), timeStr(timeStr) {}

string Entity::getId() const {
	return id;
}

string Entity::getDest() const {
	return dest;
}

string Entity::getTimeStr() const {
	return timeStr;
}

