// Van.cpp
#include "Van.h"
#include <iostream>

// Constructor
Van::Van(const std::string& id, const std::string& mk, const std::string& mdl,
         int passengers, int storage, bool avail)
    : Vehicle(id, mk, mdl, passengers, storage, avail) {
    setLateFee(20.0); // Fixed late fee rate for Van
}

// Implement getBaseRentalRate
double Van::getBaseRentalRate() const {
    return 100.0; // Example rate
}
