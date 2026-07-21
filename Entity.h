#pragma once
#include <string>

class Entity {
private: // Explicit encapsulation to protect class invariants
    std::string id;
    std::string dest;
    std::string timeStr;
    bool isAssigned;

public:
    // Strings are passed by constant reference to prevent memory copying
    Entity(const std::string& id, const std::string& dest, const std::string& timeStr);

    // Virtual destructor ensures derived class destructors are called cleanly
    virtual ~Entity() {}

    std::string getId() const;
    std::string getDest() const;
    std::string getTimeStr() const;
    bool getIsAssigned() const;

    void setAssigned(bool assigned);

    // Pure virtual functions forcing polymorphic behavior in derived classes
    virtual std::string getDeets() const = 0;
    virtual bool isAvailable() const = 0;
};