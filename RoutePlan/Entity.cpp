#include "Entity.h"

using namespace std;

Entity::Entity(const string& id, const string& dest, const string& timeStr)
    : id(id), dest(dest), timeStr(timeStr), isAssigned(false) {
}

string Entity::getId() const {
    return id;
}

string Entity::getDest() const {
    return dest;
}

string Entity::getTimeStr() const {
    return timeStr;
}

bool Entity::getIsAssigned() const {
    return isAssigned;
}

void Entity::setAssigned(bool assigned) {
    isAssigned = assigned;
}