// Van.cpp
#include "Van.h"
#include <iostream>

// Constructor
Van::Van(const std::string& id, const std::string& mk, const std::string& mdl,
         int passengers, int storage, bool avail)
    : Vehicle(id, mk, mdl, passengers, storage, avail) {
    setLateFee(20.0); // Fixed late fee rate for Van
}

// Destructor
Van::~Van() {}

// Override displayVehicle
void Van::displayVehicle() const {
    std::cout << "### Van Details ###\n";
    std::cout << "ID: " << getVehicleID() << "\nMake: " << getMake() << "\nModel: " << getModel()
              << "\nPassenger Capacity: " << getPassengers()
              << "\nStorage Capacity: " << getCapacity()
              << "\nAvailable: " << (getAvailability() ? "Yes" : "No")
              << "\nLate Fee: $" << getLateFee() << "/day\n\n";
}
