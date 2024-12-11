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
int Customer::getCustomerID() const { return customerID; }
std::string Customer::getName() const { return name; }
std::vector<RentalInfo> Customer::getRentedVehicles() const { return rentedVehicles; }
int Customer::getLoyaltyPoints() const { return loyaltyPoints; }

// Rent a vehicle
void Customer::rentVehicle(const std::shared_ptr<Vehicle>& vehicle, const std::string& rentDate, const std::string& dueDate) {
    rentedVehicles.push_back(RentalInfo{ vehicle, rentDate, dueDate });
    std::cout << "Vehicle ID " << vehicle->getVehicleID() << " rented on " << rentDate << ", due on " << dueDate << ".\n";
}

// Return a vehicle
int Customer::returnVehicle(const std::shared_ptr<Vehicle>& vehicle, const std::string& returnDate) {
    if (!hasRentedVehicle(vehicle)) {
        throw std::runtime_error("Vehicle was not rented by this customer.");
    }

    auto it = std::find_if(rentedVehicles.begin(), rentedVehicles.end(),
                           [&](const RentalInfo& rental) { return rental.vehicle->getVehicleID() == vehicle->getVehicleID(); });

    if (it != rentedVehicles.end()) {
        // Calculate days late
        if (DateUtils::daysDifference(it->rentDate, returnDate) < 0) {
            throw std::runtime_error("Return date cannot be before rent date.");
        }
        int daysLate = DateUtils::daysDifference(it->dueDate, returnDate);
        rentedVehicles.erase(it);
        return daysLate > 0 ? daysLate : 0;
    } else {
        throw std::runtime_error("Error: Vehicle ID " + vehicle->getVehicleID() + " not found in rentals.");
    }
}



// Check if customer has rented a specific vehicle
bool Customer::hasRentedVehicle(const std::shared_ptr<Vehicle>& vehicle) const {
    return std::any_of(rentedVehicles.begin(), rentedVehicles.end(),
                       [&](const RentalInfo& rental) { return rental.vehicle->getVehicleID() == vehicle->getVehicleID(); });
}

// Apply loyalty discount
bool Customer::applyLoyaltyDiscount() {
    const int discountThreshold = 100; // Points needed for discount
    if (loyaltyPoints >= discountThreshold) {
        loyaltyPoints -= discountThreshold;
        return true;
    }
    return false;
}

// Add loyalty points
void Customer::addLoyaltyPoints(int points) {
    loyaltyPoints += points;
    if (loyaltyPoints < 0) loyaltyPoints = 0;
    std::cout << "Loyalty Points Updated: " << loyaltyPoints << "\n";
}

// Set loyalty points (used when loading from file)
void Customer::setLoyaltyPoints(int points) {
    loyaltyPoints = points;
}

// Add a RentalInfo directly (used when loading from file)
void Customer::addRental(const RentalInfo& rental) {
    rentedVehicles.push_back(rental);
}

// Implement toRow method**
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
