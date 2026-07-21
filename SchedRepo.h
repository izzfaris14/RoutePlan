#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Shuttle.h"
#include "Passenger.h"
#include "Route.h"

class SchedRepo {
private:
    std::vector<std::unique_ptr<Shuttle>> shuttles;
    std::vector<std::unique_ptr<Passenger>> passengers;
    std::vector<Route> matchedRoutes;

public:
    // Application Lifecycle: Create
    void addShuttle(std::unique_ptr<Shuttle> s);
    void addPassenger(std::unique_ptr<Passenger> p);
    void addRoute(const Route& r);

    // Application Lifecycle: Update (Edit)
    bool editShuttle(const std::string& id, const std::string& newDest, const std::string& newTime, int newCap);
    bool editPassenger(const std::string& id, const std::string& newDest, const std::string& newTime, int newSize);

    // Application Lifecycle: Delete
    bool removeShuttle(const std::string& id);
    bool removePassenger(const std::string& id);

    void clearRoutes();

    // Encapsulated Retrieval with Bounds Checking
    size_t getShuttleCount() const;
    Shuttle* getShuttle(size_t index) const;

    size_t getPassengerCount() const;
    Passenger* getPassenger(size_t index) const;

    size_t getRouteCount() const;
    const Route& getRoute(size_t index) const;
};