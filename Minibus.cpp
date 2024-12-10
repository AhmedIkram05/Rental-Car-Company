// Minibus.cpp
#include "Minibus.h"
#include <iostream>

// Constructor
Minibus::Minibus(const std::string& id, const std::string& mk, const std::string& mdl,
               int passengers, int storage, bool avail)
    : Vehicle(id, mk, mdl, passengers, storage, avail) {
    setLateFee(12.0); // Fixed late fee rate for Minibus
}

// Implement getBaseRentalRate
double Minibus::getBaseRentalRate() const {
    return 80.0; // Example rate
}
