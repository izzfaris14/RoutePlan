#include<iostream>
#include "Passenger.h"

using namespace std;

Passenger::Passenger(string id, string dest, time_t time) : Entity(id, dest, time) {}