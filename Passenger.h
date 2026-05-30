#pragma once
#include "Entity.h"

using namespace std;

class Passenger : public Entity {
public:
	Passenger(string id, string dest, time_t time) : Entity(id, dest, time) {}
};