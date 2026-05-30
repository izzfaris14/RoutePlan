#pragma once

#include "Entity.h"

using namespace std;

class Shuttle : public Entity {
public:
	Shuttle(string id, string dest, time_t time) : Entity(id, dest, time) {}
};

