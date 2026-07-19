#pragma once
#include<string>
#include<ctime>
#include "Entity.h"



class Shuttle : public Entity {
	int capacity;
public:
	Shuttle(std::string id, std::string dest, std::string timeStr, int capacity);
	std::string getDeets() const override;
	int getCapacity() const;
};
