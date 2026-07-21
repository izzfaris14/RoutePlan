#pragma once
#include <string>
#include "Entity.h"

class Shuttle : public Entity {
private: // Explicit encapsulation
    int cap;

public:
    
    Shuttle(const std::string& id, const std::string& dest, const std::string& timeStr, int cap);

    int getCapacity() const;
    void setCapacity(int c);
    std::string getDeets() const override;
    bool isAvailable() const override;
};