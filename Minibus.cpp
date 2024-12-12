// Minibus.cpp
#include "Minibus.h"
#include <iostream>


/**
 * The Minibus constructor initializes a Minibus object with specific attributes and sets a fixed late
 * fee rate.
 *
 * @param id The `id` parameter is a `std::string` representing the unique identifier of the Minibus.
 * @param mk The parameter `mk` in the `Minibus` constructor likely stands for the make of the minibus.
 * It is used to initialize the make of the minibus object being created.
 * @param mdl The parameter `mdl` in the `Minibus` constructor refers to the model of the minibus being
 * created. It is a `std::string` type parameter that stores the model information of the minibus.
 * @param passengers The `passengers` parameter in the `Minibus` constructor represents the maximum
 * number of passengers that the minibus can accommodate.
 * @param storage The `storage` parameter in the `Minibus` constructor likely refers to the storage
 * capacity of the minibus. It specifies the amount of space available in the minibus for storing
 * luggage, equipment, or other items.
 * @param avail The `avail` parameter in the `Minibus` constructor is a boolean value that indicates
 * whether the minibus is available for use or not. If `avail` is `true`, it means the minibus is
 * available, and if it is `false`, it means the minibus is not available
 */
Minibus::Minibus(const std::string& id, const std::string& mk, const std::string& mdl,
               int passengers, int storage, bool avail)
    : Vehicle(id, mk, mdl, passengers, storage, avail) {
    setLateFee(12.0); // Fixed late fee rate for Minibus
}

/**
 * The getBaseRentalRate function in the Minibus class returns a base rental rate of 65.0.
 *
 * @return The function `getBaseRentalRate()` is returning a `double` value of 65.0, which represents
 * the base rental rate for a minibus in this example.
 */
double Minibus::getBaseRentalRate() const {
    return 65.0; // Example rate
}
