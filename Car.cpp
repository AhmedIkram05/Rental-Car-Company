// Car.cpp
#include "Car.h"
#include <iostream>

// Constructor
Car::Car(const std::string& id, const std::string& mk, const std::string& mdl,
         int passengers, int storage, bool avail)
    : Vehicle(id, mk, mdl, passengers, storage, avail) {
    setLateFee(10.0);
}

// Destructor
Car::~Car() {}

// Override displayVehicle
void Car::displayVehicle() const {
    std::cout << "### Car Details ###\n";
    std::cout << "ID: " << getVehicleID() << "\nMake: " << getMake() << "\nModel: " << getModel()
              << "\nPassenger Capacity: " << getPassengers()
              << "\nStorage Capacity: " << getCapacity()
              << "\nAvailable: " << (getAvailability() ? "Yes" : "No")
              << "\nLate Fee: $" << getLateFee() << "/day\n\n";
}
