#pragma once
#include<string>
#include<ctime>
#include "Entity.h"



class Passenger : public Entity {
public:
	Passenger(string id, string dest, string timeStr);  
	string getDeets() const;
};