#pragma once
#include<string>
#include<ctime>
#include "Entity.h"



class Shuttle : public Entity {
public:
	Shuttle(string id, string dest, string timeStr);
	string getDeets() const;
};
