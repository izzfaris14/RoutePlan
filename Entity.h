#pragma once
#include <string>

using namespace std;

class Entity {
    string id;
    string dest;
    string timeStr;
    bool isAssigned; // fixes 1-to-1 bug
public:
    Entity(string id, string dest, string timeStr);
    virtual ~Entity() {} //virtual destructor for polymorphism


    string getId() const;
    string getDest() const;
    string getTimeStr() const;

	bool getIsAssigned() const;
	void setAssigned(bool assigned);

    virtual string getDeets() const = 0; //pure virtual function making this an abstract base class
    virtual bool isAvailable() const = 0;
};