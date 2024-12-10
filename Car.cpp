// Car.cpp
#include "Car.h"
#include <iostream>

// Constructor
Car::Car(const std::string& id, const std::string& mk, const std::string& mdl,
         int passengers, int storage, bool avail)
    : Vehicle(id, mk, mdl, passengers, storage, avail) {
    setLateFee(10.0);
}

// Implement getBaseRentalRate
double Car::getBaseRentalRate() const {
    return 50.0; // Example rate
}
