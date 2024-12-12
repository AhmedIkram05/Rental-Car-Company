// Van.cpp
#include "Van.h"
#include <iostream>


/**
 * The Van constructor initializes a Van object with specific attributes and sets a fixed late fee
 * rate.
 *
 * @param id The `id` parameter is a `std::string` representing the unique identifier of the Van.
 * @param mk The parameter `mk` in the `Van` constructor likely stands for the make of the van. It is
 * used to initialize the make of the vehicle when a `Van` object is created.
 * @param mdl The parameter `mdl` in the `Van` constructor stands for the model of the van being
 * created. It is a `std::string` type parameter that represents the model name of the van.
 * @param passengers The `passengers` parameter in the `Van` constructor represents the maximum number
 * of passengers that the van can accommodate.
 * @param storage The `storage` parameter in the `Van` constructor likely refers to the storage
 * capacity of the van. It represents the amount of space available in the van for carrying goods,
 * luggage, or other items. This parameter is used to initialize the storage capacity of the `Van`
 * object being created.
 * @param avail The `avail` parameter in the `Van` constructor is a boolean flag indicating whether the
 * van is available for use or not. If `avail` is `true`, it means the van is available, and if it is
 * `false`, it means the van is not available for use.
 */
Van::Van(const std::string& id, const std::string& mk, const std::string& mdl,
         int passengers, int storage, bool avail)
    : Vehicle(id, mk, mdl, passengers, storage, avail) {
    setLateFee(20.0); // Fixed late fee rate for Van
}

/**
 * The getBaseRentalRate function in the Van class returns a base rental rate of 100.0.
 *
 * @return The function `getBaseRentalRate` is returning a `double` value of 100.0.
 */
double Van::getBaseRentalRate() const {
    return 100.0; // Example rate
}
