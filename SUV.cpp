// SUV.cpp
#include "SUV.h"
#include <iostream>

// Constructor
SUV::SUV(const std::string& id, const std::string& mk, const std::string& mdl,
         int passengers, int storage, bool avail)
    : Vehicle(id, mk, mdl, passengers, storage, avail) {
    setLateFee(15.0); // Fixed late fee rate for SUV
}

// Destructor
SUV::~SUV() {}

// Override displayVehicle
void SUV::displayVehicle() const {
    std::cout << "### SUV Details ###\n";
    std::cout << "ID: " << getVehicleID() << "\nMake: " << getMake() << "\nModel: " << getModel()
              << "\nPassenger Capacity: " << getPassengers()
              << "\nStorage Capacity: " << getCapacity()
              << "\nAvailable: " << (getAvailability() ? "Yes" : "No")
              << "\nLate Fee: $" << getLateFee() << "/day\n\n";
}