#include "Entity.h"

/*
 * ============================================================================
 * Class: Entity
 * Author: Farid Abqary
 * Description: Abstract base class defining common attributes (ID, destination,
 * time) and polymorphic interfaces for all transport entities.
 * ============================================================================
 */

using namespace std;

/*
 * Function: Entity (Constructor)
 * Author: Farid Abqary
 * Description: Initializes the base Entity with an ID, destination, and time. Time Complexity: O(1)
 * Parameters: id (string), dest (string), timeStr (string)
 * Returns: N/A
 */
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
