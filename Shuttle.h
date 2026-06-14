#pragma once

#include "Entity.h"

using namespace std;

class Shuttle : public Entity {
public:
	Shuttle(string id, string dest, string timeStr);
	string getDeets() const;
};
