// Customer.h

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <memory>
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
    std::vector<RentalInfo> rentedVehicles;
    int loyaltyPoints;

public:
    // Constructor
    Customer(int id, const std::string& nm);

    // Destructor
    virtual ~Customer();

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
};

#endif // CUSTOMER_H
