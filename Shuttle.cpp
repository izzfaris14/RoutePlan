#include"Shuttle.h"
#include<iostream>

using namespace std;

Shuttle::Shuttle(string id, string dest, time_t time) : Entity(id, dest, time) {}