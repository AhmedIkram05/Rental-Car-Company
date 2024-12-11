// Customer.cpp
#include "Customer.h"
#include "DateUtils.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

// Constructor
Customer::Customer(int id, const std::string& nm) : customerID(id), name(nm), loyaltyPoints(0) {}

// Destructor
Customer::~Customer() {}

// Getters

/**
 * This function returns the customer ID of a Customer object.
 *
 * @return The `customerID` of the `Customer` object is being returned.
 */
int Customer::getCustomerID() const { return customerID; }

/**
 * This function returns the name of the customer.
 *
 * @return The `name` member variable of the `Customer` class is being returned as a `std::string`.
 */
std::string Customer::getName() const { return name; }

/**
 * This function returns a vector of RentalInfo objects representing vehicles rented by a customer.
 *
 * @return A vector of RentalInfo objects representing the vehicles that the customer has rented.
 */
std::vector<RentalInfo> Customer::getRentedVehicles() const { return rentedVehicles; }

/**
 * This function returns the loyalty points of a customer.
 *
 * @return The loyalty points of the customer.
 */
int Customer::getLoyaltyPoints() const { return loyaltyPoints; }


/**
 * The rentVehicle function adds a rental record for a vehicle to a customer's list of rented vehicles
 * and prints out the details of the rental.
 *
 * @param vehicle The `vehicle` parameter is a `std::shared_ptr` to a `Vehicle` object, which
 * represents the vehicle that the customer wants to rent.
 * @param rentDate The `rentDate` parameter in the `rentVehicle` function represents the date on which
 * the vehicle is being rented by the customer. It is a string that typically contains the date in a
 * specific format, such as "YYYY-MM-DD".
 * @param dueDate The `dueDate` parameter in the `rentVehicle` function represents the date by which
 * the rented vehicle is expected to be returned by the customer. It is the date when the rental period
 * ends, and the customer is required to return the vehicle to the rental service.
 */
void Customer::rentVehicle(const std::shared_ptr<Vehicle>& vehicle, const std::string& rentDate, const std::string& dueDate) {
    rentedVehicles.push_back(RentalInfo{ vehicle, rentDate, dueDate });
    std::cout << "Vehicle ID " << vehicle->getVehicleID() << " rented on " << rentDate << ", due on " << dueDate << ".\n";
}

/**
 * The function `returnVehicle` in C++ checks and processes the return of a rented vehicle by a
 * customer, calculating any late fees if applicable.
 *
 * @param vehicle The `vehicle` parameter is a `std::shared_ptr<Vehicle>` which represents the vehicle
 * that the customer wants to return. This shared pointer points to an instance of a `Vehicle` class.
 * @param returnDate The `returnDate` parameter in the `returnVehicle` function represents the date
 * when the customer is returning the rented vehicle. This date is used to calculate if the vehicle is
 * being returned late and to determine the number of days late, if any.
 *
 * @return The function `returnVehicle` returns an integer value representing the number of days late
 * the vehicle was returned by the customer. If the vehicle was returned on time or early, it returns
 * 0.
 */
int Customer::returnVehicle(const std::shared_ptr<Vehicle>& vehicle, const std::string& returnDate) {
    // Check if the vehicle was rented by this customer
    if (!hasRentedVehicle(vehicle)) {
        throw std::runtime_error("Vehicle was not rented by this customer.");
    }

    // Find the rental information for the vehicle
    auto it = std::find_if(rentedVehicles.begin(), rentedVehicles.end(),
                           [&](const RentalInfo& rental) { return rental.vehicle->getVehicleID() == vehicle->getVehicleID(); });

    if (it != rentedVehicles.end()) {
        // Calculate days late
        if (DateUtils::daysDifference(it->rentDate, returnDate) < 0) {
            throw std::runtime_error("Return date cannot be before rent date.");
        }
        int daysLate = DateUtils::daysDifference(it->dueDate, returnDate);
        rentedVehicles.erase(it); // Remove the rental information
        return daysLate > 0 ? daysLate : 0; // Return the number of days late, or 0 if not late
    } else {
        throw std::runtime_error("Error: Vehicle ID " + vehicle->getVehicleID() + " not found in rentals.");
    }
}

/**
 * The function checks if a customer has rented a specific vehicle by comparing vehicle IDs.
 *
 * @param vehicle The `vehicle` parameter is a `std::shared_ptr` to a `Vehicle` object. It is used to
 * check if the customer has rented a specific vehicle by comparing the `vehicleID` of the rented
 * vehicles with the `vehicleID` of the provided `vehicle`.
 *
 * @return The function `hasRentedVehicle` returns a boolean value indicating whether the customer has
 * rented a specific vehicle.
 */
bool Customer::hasRentedVehicle(const std::shared_ptr<Vehicle>& vehicle) const {
    return std::any_of(rentedVehicles.begin(), rentedVehicles.end(),
                       [&](const RentalInfo& rental) { return rental.vehicle->getVehicleID() == vehicle->getVehicleID(); });
}

/**
 * The function "applyLoyaltyDiscount" deducts loyalty points if the customer has enough points for a
 * discount.
 *
 * @return The `applyLoyaltyDiscount` function returns a boolean value - `true` if the customer has
 * enough loyalty points to apply a discount, and `false` otherwise.
 */
bool Customer::applyLoyaltyDiscount() {
    const int discountThreshold = 100; // Points needed for discount
    if (loyaltyPoints >= discountThreshold) {
        loyaltyPoints -= discountThreshold; // Deduct points if eligible
        return true;
    }
    return false;
}

/**
 * The function `addLoyaltyPoints` increments the loyalty points by a given amount and ensures they do
 * not go negative.
 *
 * @param points The `points` parameter in the `addLoyaltyPoints` method represents the number of
 * loyalty points to be added to the customer's current loyalty points balance. This value can be
 * positive (to add points) or negative (to deduct points).
 */
void Customer::addLoyaltyPoints(int points) {
    loyaltyPoints += points;
    if (loyaltyPoints < 0) loyaltyPoints = 0; // Ensure points do not go negative
    std::cout << "Loyalty Points Updated: " << loyaltyPoints << "\n";
}

/**
 * This function sets the loyalty points for a customer.
 *
 * @param points The `points` parameter in the `setLoyaltyPoints` function represents the number of
 * loyalty points that will be set for the customer.
 */
void Customer::setLoyaltyPoints(int points) {
    loyaltyPoints = points;
}

/**
 * The function `addRental` adds a rental information object to a vector of rented vehicles.
 *
 * @param rental The parameter `rental` in the `addRental` function is of type `RentalInfo`, which is
 * likely a struct or class containing information about a vehicle rental such as the vehicle type,
 * rental duration, rental cost, etc.
 */
void Customer::addRental(const RentalInfo& rental) {
    rentedVehicles.push_back(rental);
}

/**
 * The function `toRow` converts a `Customer` object into a vector of strings representing its
 * attributes.
 *
 * @return The `toRow` function of the `Customer` class is returning a `std::vector<std::string>`
 * containing information about the customer. The vector contains the customer's ID, name, loyalty
 * points, and a string of rented vehicle IDs separated by commas.
 */
std::vector<std::string> Customer::toRow() const {
    std::vector<std::string> row;
    row.emplace_back(std::to_string(customerID));
    row.emplace_back(name);
    row.emplace_back(std::to_string(loyaltyPoints));

    // Concatenate rented vehicle IDs separated by commas
    std::string rentedVehiclesStr;
    for (const auto& rental : rentedVehicles) {
        rentedVehiclesStr += rental.vehicle->getVehicleID() + ", ";
    }
    if (!rentedVehiclesStr.empty()) {
        rentedVehiclesStr = rentedVehiclesStr.substr(0, rentedVehiclesStr.size() - 2); // Remove trailing comma and space
    }
    row.emplace_back(rentedVehiclesStr);

    return row;
}
