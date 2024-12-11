// SUV.cpp
#include "SUV.h"
#include <iostream>

/**
 * @brief Construct a new SUV object
 *
 * @param id The unique identifier for the SUV
 * @param mk The make of the SUV
 * @param mdl The model of the SUV
 * @param passengers The number of passengers the SUV can carry
 * @param storage The storage capacity of the SUV
 * @param avail The availability status of the SUV
 */
SUV::SUV(const std::string& id, const std::string& mk, const std::string& mdl,
         int passengers, int storage, bool avail)
    : Vehicle(id, mk, mdl, passengers, storage, avail) {
    setLateFee(15.0); // Fixed late fee rate for SUV
}

/**
 * @brief Get the base rental rate for the SUV
 *
 * @return double The base rental rate for the SUV
 */
double SUV::getBaseRentalRate() const {
    return 80.0; // Example rate
}