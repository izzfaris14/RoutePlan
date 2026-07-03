#pragma once
#include "Entity.h"



class Passenger : public Entity {
	int groupSize; //capacity of the passenger group
public:
	Passenger(std::string id, std::string dest, std::string timeStr, int groupSize);

	int getGroupSize() const;
	std::string getDeets() const override;
};