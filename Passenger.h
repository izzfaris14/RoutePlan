#pragma once
#include "Entity.h"
#include <string>

class Passenger :public Entity {
	int gSize;
public:
	Passenger(std::string id, std::string dest, std::string timeStr, int gSize);
	int getGroupSize() const;
	std::string getDeets() const override;
};