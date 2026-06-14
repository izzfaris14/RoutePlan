#include"Shuttle.h"
#include<iostream>


using namespace std;

Shuttle::Shuttle(string id, string dest, string timeStr) : Entity(id, dest, timeStr) {}

string Shuttle::getDeets() const {
	return "Shuttle ID: " + getId() + ", Dest " + getDest() + ", Time:" + getTimeStr();
}