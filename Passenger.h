#pragma once
#include "Entity.h"

using namespace std;

class Passenger : public Entity {
public:
	Passenger(string id, string dest, string timeStr);  
};