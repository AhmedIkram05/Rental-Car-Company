// Minibus.cpp
#include "Minibus.h"
#include <iostream>

// Constructor
Minibus::Minibus(const std::string& id, const std::string& mk, const std::string& mdl,
               int passengers, int storage, bool avail)
    : Vehicle(id, mk, mdl, passengers, storage, avail) {
    setLateFee(12.0); // Fixed late fee rate for Minibus
}

// Destructor
Minibus::~Minibus() {}

// Override displayVehicle
void Minibus::displayVehicle() const {
    std::cout << "### Minibus Details ###\n";
    std::cout << "ID: " << getVehicleID() << "\nMake: " << getMake() << "\nModel: " << getModel()
              << "\nPassenger Capacity: " << getPassengers()
              << "\nStorage Capacity: " << getCapacity()
              << "\nAvailable: " << (getAvailability() ? "Yes" : "No")
              << "\nLate Fee: $" << getLateFee() << "/day\n\n";
}
