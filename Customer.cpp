// Customer.cpp
#include "Customer.h"
#include "DateUtils.h"
#include <algorithm>
#include <iostream>

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
    auto it = std::find_if(rentedVehicles.begin(), rentedVehicles.end(),
                           [&](const RentalInfo& rental) { return rental.vehicle->getVehicleID() == vehicle->getVehicleID(); });

    if (it != rentedVehicles.end()) {
        // Calculate days late
        int daysLate = DateUtils::daysDifference(it->dueDate, returnDate);
        rentedVehicles.erase(it);
        return daysLate > 0 ? daysLate : 0;
    } else {
        throw std::runtime_error("Error: Vehicle ID " + vehicle->getVehicleID() + " not found in rentals.");
    }
}

// Display customer information
void Customer::displayCustomer() const {
    std::cout << "### Customer Details ###\n";
    std::cout << "ID: " << customerID << "\nName: " << name
              << "\nLoyalty Points: " << loyaltyPoints << "\nRented Vehicles:\n";

    if (rentedVehicles.empty()) {
        std::cout << "None\n\n";
    } else {
        for (const auto& rental : rentedVehicles) {
            std::cout << "- Vehicle ID: " << rental.vehicle->getVehicleID()
                      << ", Rent Date: " << rental.rentDate
                      << ", Due Date: " << rental.dueDate << "\n";
        }
        std::cout << "\n";
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
