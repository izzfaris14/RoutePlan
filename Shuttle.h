#pragma once
#include<string>
#include "Entity.h"



class Shuttle : public Entity {
	int cap;
public:
	Shuttle(std::string id, std::string dest, std::string timeStr, int cap=15);
	int getCapacity() const;
	void setCapacity(int c);
	std::string getDeets() const override;
	bool isAvailable() const override;
};
