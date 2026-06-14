#pragma once

#include <string>
#include<ctime>

using namespace std;

class Entity {
	string id;
	string dest;
	string timeStr;

public:
	Entity(string id, string dest, string timeStr);
	virtual ~Entity() = default;

	virtual string getDetails() const = 0;
	string getId() const;
	string getDest() const;
	string getTimeStr() const;

	virtual string getDeets() const=0;
};
