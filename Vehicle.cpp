// Vehicle.cpp
#include "Vehicle.h"

// Parameterized Constructor
Vehicle::Vehicle(const std::string& id, const std::string& mk, const std::string& mdl,
                 int passengers, int storage, bool avail)
    : vehicleID(id), make(mk), model(mdl), passengers(passengers), capacity(storage), availability(avail), lateFee(0.0) {}

// Getters
std::string Vehicle::getVehicleID() const { return vehicleID; }
std::string Vehicle::getMake() const { return make; }
std::string Vehicle::getModel() const { return model; }
int Vehicle::getPassengers() const { return passengers; }
int Vehicle::getCapacity() const { return capacity; }
bool Vehicle::getAvailability() const { return availability; }
double Vehicle::getLateFee() const { return lateFee; }

// Setters
void Vehicle::setAvailability(bool avail) { availability = avail; }
void Vehicle::setLateFee(double fee) { lateFee = fee; }
