#pragma once

#include <string>
#include<ctime>

using namespace std;

class Entity {
	string id;
	string dest;
	time_t time;

public:
	Entity(string id, string dest, time_t time) : id(id), dest(dest), time(time) {}
	virtual ~Entity() = default;

	virtual void displayInfo() const;
	string getId() const { return id; }
	string getDest() const { return dest; }
	time_t getTime() const { return time; }
};
