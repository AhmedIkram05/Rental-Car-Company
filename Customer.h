// Customer.h

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Vehicle.h"

// The `RentalInfo` struct represents information about a rental transaction.
struct RentalInfo {
    std::shared_ptr<Vehicle> vehicle; // The rented vehicle
    std::string rentDate;             // The date the vehicle was rented
    std::string dueDate;              // The date the vehicle is due to be returned
};

// The `Customer` class defines a blueprint for a customer object.
class Customer {
private:
    int customerID;                   // Unique identifier for the customer
    std::string name;                 // Name of the customer
    int loyaltyPoints;                // Loyalty points accumulated by the customer
    std::vector<RentalInfo> rentedVehicles; // List of vehicles currently rented by the customer

public:
    /**
     * @brief Construct a new Customer object
     *
     * @param id The unique identifier for the customer
     * @param nm The name of the customer
     */
    Customer(int id, const std::string& nm);

    /**
     * @brief Destroy the Customer object
     */
    ~Customer();

    // Getters

    /**
     * @brief Get the customer ID
     *
     * @return int The customer ID
     */
    int getCustomerID() const;

    /**
     * @brief Get the name of the customer
     *
     * @return std::string The name of the customer
     */
    std::string getName() const;

    /**
     * @brief Get the list of rented vehicles
     *
     * @return std::vector<RentalInfo> The list of rented vehicles
     */
    std::vector<RentalInfo> getRentedVehicles() const;

    /**
     * @brief Get the loyalty points of the customer
     * 
     * @return int The loyalty points of the customer
     */
    int getLoyaltyPoints() const;

    // Rent a vehicle

    /**
     * @brief Rent a vehicle
     *
     * @param vehicle The vehicle to rent
     * @param rentDate The date the vehicle is rented
     * @param dueDate The date the vehicle is due to be returned
     */
    void rentVehicle(const std::shared_ptr<Vehicle>& vehicle, const std::string& rentDate, const std::string& dueDate);

    // Return a vehicle

    /**
     * @brief Return a rented vehicle
     *
     * @param vehicle The vehicle to return
     * @param returnDate The date the vehicle is returned
     * @return int The number of days late the vehicle was returned, or 0 if not late
     */
    int returnVehicle(const std::shared_ptr<Vehicle>& vehicle, const std::string& returnDate);

    // Check if customer has rented a specific vehicle

    /**
     * @brief Check if the customer has rented a specific vehicle
     *
     * @param vehicle The vehicle to check
     * @return bool True if the customer has rented the vehicle, false otherwise
     */
    bool hasRentedVehicle(const std::shared_ptr<Vehicle>& vehicle) const;

    // Apply loyalty discount (deduct points if eligible)

    /**
     * @brief Apply a loyalty discount by deducting points if eligible
     *
     * @return bool True if the discount was applied, false otherwise
     */
    bool applyLoyaltyDiscount();

    // Manage loyalty points

    /**
     * @brief Add loyalty points
     *
     * @param points The number of points to add
     */
    void addLoyaltyPoints(int points);

    /**
     * @brief Set loyalty points (for loading from file)
     *
     * @param points The number of points to set
     */
    void setLoyaltyPoints(int points);

    // Method to add a RentalInfo directly

    /**
     * @brief Add a rental information directly
     *
     * @param rental The rental information to add
     */
    void addRental(const RentalInfo& rental);

    // Display customer information in a table row format

    /**
     * @brief Display customer information in a table row format
     *
     * @param widths The widths of the columns
     */
    void displayRow(const std::vector<int>& widths) const {
        std::cout << "| " << std::setw(widths[0]) << customerID
                  << " | " << std::setw(widths[1]) << name
                  << " | " << std::setw(widths[2]) << loyaltyPoints
                  << " | " << std::setw(widths[3]) << getRentedVehiclesString(widths[3]) << " |" << std::endl;
    }

    // Convert customer information to a row of strings

    /**
     * @brief Convert customer information to a row of strings
     *
     * @return std::vector<std::string> A vector of strings representing the customer information
     */
    std::vector<std::string> toRow() const;

private:
    // Get a string representation of rented vehicles, truncated to fit the specified width

    /**
     * @brief Get a string representation of rented vehicles, truncated to fit the specified width
     *
     * @param width The width to fit the string into
     * @return std::string The string representation of rented vehicles
     */
    std::string getRentedVehiclesString(int width) const {
        std::ostringstream oss;
        for (const auto& rental : rentedVehicles) {
            oss << rental.vehicle->getVehicleID() << " ";
        }
        std::string rentedVehiclesStr = oss.str();
        if (rentedVehiclesStr.length() > static_cast<std::size_t>(width)) {
            rentedVehiclesStr = rentedVehiclesStr.substr(0, static_cast<std::size_t>(width) - 3) + "...";
        }
        return rentedVehiclesStr;
    }
};

#endif // CUSTOMER_H