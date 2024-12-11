// Vehicle.cpp
#include "Vehicle.h"


/**
 * The function `Vehicle::Vehicle` initializes a Vehicle object with the provided parameters.
 *
 * @param id The `id` parameter in the `Vehicle` constructor represents the unique identifier of the
 * vehicle. It is of type `std::string` and is used to uniquely identify each vehicle object.
 * @param mk The parameter `mk` represents the make of the vehicle being constructed in the `Vehicle`
 * constructor. It is a `std::string` type and is used to initialize the `make` member variable of the
 * `Vehicle` class.
 * @param mdl The parameter "mdl" in the constructor represents the model of the vehicle being created.
 * It is a `std::string` type and is used to initialize the `model` member variable of the `Vehicle`
 * class.
 * @param passengers The `passengers` parameter in the `Vehicle` constructor represents the number of
 * passengers that the vehicle can accommodate. It is an integer value that specifies the maximum
 * number of people that can ride in the vehicle at a given time.
 * @param storage The `storage` parameter in the `Vehicle` constructor represents the storage capacity
 * of the vehicle. It indicates how much storage space or capacity the vehicle has for carrying items
 * or cargo.
 * @param avail The `avail` parameter in the `Vehicle` constructor represents the availability of the
 * vehicle. It is a boolean value indicating whether the vehicle is currently available for use or not.
 */
Vehicle::Vehicle(const std::string& id, const std::string& mk, const std::string& mdl,
                 int passengers, int storage, bool avail)
    : vehicleID(id), make(mk), model(mdl), passengers(passengers), capacity(storage), availability(avail), lateFee(0.0) {}


// Getters

/**
 * This function returns the vehicle ID of a Vehicle object.
 *
 * @return The `vehicleID` of the `Vehicle` object is being returned.
 */
std::string Vehicle::getVehicleID() const { return vehicleID; }

/**
 * This function returns the make of the vehicle.
 *
 * @return The `make` member variable of the `Vehicle` class is being returned as a `std::string`.
 */
std::string Vehicle::getMake() const { return make; }

/**
 * This function returns the model of the vehicle.
 *
 * @return The `model` member variable of the `Vehicle` class is being returned as a `std::string`.
 */
std::string Vehicle::getModel() const { return model; }

/**
 * This function returns the number of passengers the vehicle can carry.
 *
 * @return The `passengers` member variable of the `Vehicle` class is being returned as an `int`.
 */
int Vehicle::getPassengers() const { return passengers; }

/**
 * This function returns the storage capacity of the vehicle.
 *
 * @return The `capacity` member variable of the `Vehicle` class is being returned as an `int`.
 */
int Vehicle::getCapacity() const { return capacity; }

/**
 * This function returns the availability status of the vehicle.
 *
 * @return The `availability` member variable of the `Vehicle` class is being returned as a `bool`.
 */
bool Vehicle::getAvailability() const { return availability; }

/**
 * This function returns the late fee per day for the vehicle.
 *
 * @return The `lateFee` member variable of the `Vehicle` class is being returned as a `double`.
 */
double Vehicle::getLateFee() const { return lateFee; }


// Setters

/**
 * This function sets the availability status of the vehicle.
 *
 * @param avail The `avail` parameter is a `bool` value that represents the availability status of the
 * vehicle. If `avail` is `true`, the vehicle is available for rent; otherwise, it is not available.
 */
void Vehicle::setAvailability(bool avail) { availability = avail; }

/**
 * This function sets the late fee per day for the vehicle.
 *
 * @param fee The `fee` parameter is a `double` value that represents the late fee per day for the
 * vehicle.
 */
void Vehicle::setLateFee(double fee) { lateFee = fee; }
