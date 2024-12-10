// Customer.h

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>
#include "Vehicle.h"

struct RentalInfo {
    std::shared_ptr<Vehicle> vehicle;
    std::string rentDate;
    std::string dueDate;
};

class Customer {
private:
    int customerID;
    std::string name;
    int loyaltyPoints;
    std::vector<RentalInfo> rentedVehicles;

public:
    // Constructor
    Customer(int id, const std::string& nm);

    // Destructor
    ~Customer();

    // Getters
    int getCustomerID() const;
    std::string getName() const;
    std::vector<RentalInfo> getRentedVehicles() const;
    int getLoyaltyPoints() const;

    // Rent a vehicle
    void rentVehicle(const std::shared_ptr<Vehicle>& vehicle, const std::string& rentDate, const std::string& dueDate);

    // Return a vehicle
    int returnVehicle(const std::shared_ptr<Vehicle>& vehicle, const std::string& returnDate);

    // Display customer information
    void displayCustomer() const;

    // Check if customer has rented a specific vehicle
    bool hasRentedVehicle(const std::shared_ptr<Vehicle>& vehicle) const;

    // Apply loyalty discount
    bool applyLoyaltyDiscount(); // Deduct points if eligible

    // Manage loyalty points
    void addLoyaltyPoints(int points);
    void setLoyaltyPoints(int points); // For loading from file

    // Method to add a RentalInfo directly
    void addRental(const RentalInfo& rental);

    // Display row for table
    void displayRow(const std::vector<int>& widths) const {
        std::cout << " " << std::setw(widths[0]) << customerID
                  << " | " << std::setw(widths[1]) << name
                  << " | " << std::setw(widths[2]) << loyaltyPoints
                  << " | ";
        if (rentedVehicles.empty()) {
            std::cout << std::setw(widths[3]) << "No rented vehicles";
        } else {
            for (const auto& rental : rentedVehicles) {
                std::cout << rental.vehicle->getVehicleID() << " ";
            }
        }
        std::cout << " |";
    }
};

#endif // CUSTOMER_H
