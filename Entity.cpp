#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "Entity.h"

using namespace std;

Entity::Entity(string id, string dest, time_t time) : id(id), dest(dest), time(time) {}

void Entity::displayInfo() const {
	cout << "ID: " << id << endl;
	cout << "Destination: " << dest << endl;
	cout << "Time: " << ctime(&time);
}

string Entity::getId() const {
	return id;
}

string Entity::getDest() const {
	return dest;
}

time_t Entity::getTime() const {
	return time;
}

