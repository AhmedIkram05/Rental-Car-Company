// Car.cpp
#include "Car.h"
#include <iostream>


/**
 * The Car constructor initializes a Car object with the provided parameters and sets a late fee of
 * 10.0.
 *
 * @param id The `id` parameter is a `std::string` that represents the unique identifier of the car.
 * @param mk The parameter `mk` in the `Car` constructor likely stands for the make of the car. It is
 * being passed as a `std::string` parameter to initialize the `Car` object with the specified make.
 * @param mdl The parameter `mdl` in the `Car` constructor refers to the model of the car being
 * created. It is a `std::string` type parameter that stores the model name of the car.
 * @param passengers The `passengers` parameter in the `Car` constructor represents the maximum number
 * of passengers that the car can accommodate.
 * @param storage The `storage` parameter in the `Car` constructor likely refers to the storage
 * capacity of the car. It is an integer value representing the amount of storage space available in
 * the car for carrying items or luggage.
 * @param avail The `avail` parameter in the `Car` constructor is a boolean flag indicating whether the
 * car is available for use or not. If `avail` is `true`, it means the car is available, and if it is
 * `false`, it means the car is not available for use.
 */
Car::Car(const std::string& id, const std::string& mk, const std::string& mdl,
         int passengers, int storage, bool avail)
    : Vehicle(id, mk, mdl, passengers, storage, avail) {
    setLateFee(10.0);
}

/**
 * The `getBaseRentalRate` function in the `Car` class returns the base rental rate for a car, which
 * is set to 50.0 in this example.
 *
 * @return The base rental rate for a car, which is a `double` value representing the cost of renting
 * the car per day.
 */
double Car::getBaseRentalRate() const {
    return 50.0; // Example rate
}
