// SUV.cpp
#include "SUV.h"
#include <iostream>

// Constructor
SUV::SUV(const std::string& id, const std::string& mk, const std::string& mdl,
         int passengers, int storage, bool avail)
    : Vehicle(id, mk, mdl, passengers, storage, avail) {
    setLateFee(15.0); // Fixed late fee rate for SUV
}

// Implement getBaseRentalRate
double SUV::getBaseRentalRate() const {
    return 80.0; // Example rate
}
