// Customer.cpp
#include "Customer.h"
#include "DateUtils.h"
#include <algorithm>
#include <iostream>

// Constructor
Customer::Customer(int id, const std::string& nm) : customerID(id), name(nm), loyaltyPoints(0) {}

// Destructor
Customer::~Customer() {}

// Implement displayCustomer
void Customer::displayCustomer() const {
    std::cout << "Customer ID: " << customerID << ", Name: " << name << ", Loyalty Points: " << loyaltyPoints << "\n";
    std::cout << "Rentals:\n";
    for (const auto& rental : rentedVehicles) {
        std::cout << "  Vehicle ID: " << rental.vehicle->getVehicleID() << ", Rent Date: " << rental.rentDate << ", Due Date: " << rental.dueDate << "\n";
    }
}

// Getters
int Customer::getCustomerID() const { return customerID; }
std::string Customer::getName() const { return name; }
std::vector<RentalInfo> Customer::getRentedVehicles() const { return rentedVehicles; }
int Customer::getLoyaltyPoints() const { return loyaltyPoints; }

// Rent a vehicle
void Customer::rentVehicle(const std::shared_ptr<Vehicle>& vehicle, const std::string& rentDate, const std::string& dueDate) {
    rentedVehicles.push_back({ vehicle, rentDate, dueDate });
}

// Return a vehicle
int Customer::returnVehicle(const std::shared_ptr<Vehicle>& vehicle, const std::string& returnDate) {
    auto it = std::find_if(rentedVehicles.begin(), rentedVehicles.end(), [&vehicle](const RentalInfo& rental) {
        return rental.vehicle == vehicle;
    });

    if (it != rentedVehicles.end()) {
        int daysLate = DateUtils::calculateDaysLate(it->dueDate, returnDate);
        rentedVehicles.erase(it);
        if (daysLate <= 0) {
            loyaltyPoints += 10; // Add loyalty points for on-time return
        }
        return daysLate;
    }

    throw std::runtime_error("Vehicle not found in customer's rented vehicles.");
}

// Check if customer has rented a specific vehicle
bool Customer::hasRentedVehicle(const std::shared_ptr<Vehicle>& vehicle) const {
    return std::any_of(rentedVehicles.begin(), rentedVehicles.end(), [&vehicle](const RentalInfo& rental) {
        return rental.vehicle == vehicle;
    });
}

// Apply loyalty discount
bool Customer::applyLoyaltyDiscount() {
    if (loyaltyPoints >= 100) {
        loyaltyPoints -= 100;
        return true;
    }
    return false;
}

// Method to add a RentalInfo directly
void Customer::addRental(const RentalInfo& rental) {
    rentedVehicles.emplace_back(rental);
    // Update vehicle availability
    rental.vehicle->setAvailability(false);
}
