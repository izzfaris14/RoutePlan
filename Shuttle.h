#pragma once
#include<string>
#include "Entity.h"



class Shuttle : public Entity {
	int cap;
public:
	Shuttle(std::string id, std::string dest, std::string timeStr, int cap);
	int getCapacity() const;
	std::string getDeets() const override;
};
