#pragma once
#include <string>

/*
 * ============================================================================
 * Class: Entity
 * Author: Farid Abqary
 * Description: Abstract base class defining common attributes (ID, destination,
 * time) and polymorphic interfaces for all transport entities.
 * ============================================================================
 */

class Entity {
private:
    std::string id;
    std::string dest;
    std::string timeStr;
    bool isAssigned;

public:
    Entity(const std::string& id, const std::string& dest, const std::string& timeStr);
    virtual ~Entity() {}

    std::string getId() const;
    std::string getDest() const;
    std::string getTimeStr() const;
    bool getIsAssigned() const;

    void setAssigned(bool assigned);

    virtual std::string getDeets() const = 0;
    virtual bool isAvailable() const = 0;
    virtual int getCapacity() const = 0;
};
