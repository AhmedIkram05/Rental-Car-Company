// Vehicle.h
#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

// The `Vehicle` class defines a blueprint for a vehicle object.
class Vehicle {
protected:
    std::string vehicleID;    // Unique identifier for the vehicle
    std::string make;         // Make of the vehicle
    std::string model;        // Model of the vehicle
    int passengers;           // Number of passengers the vehicle can carry
    int capacity;             // Storage capacity of the vehicle
    bool availability;        // Availability status of the vehicle
    double lateFee;           // Late fee per day

public:
    /**
     * @brief Construct a new Vehicle object
     * 
     * @param id The unique identifier for the vehicle
     * @param mk The make of the vehicle
     * @param mdl The model of the vehicle
     * @param passengers The number of passengers the vehicle can carry
     * @param storage The storage capacity of the vehicle
     * @param avail The availability status of the vehicle
     */
    Vehicle(const std::string& id, const std::string& mk, const std::string& mdl,
            int passengers, int storage, bool avail);

    /**
     * @brief Destroy the Vehicle object
     */
    virtual ~Vehicle() = default;

    /**
     * @brief Convert vehicle information to a row of strings for display
     *
     * @return std::vector<std::string> A vector of strings representing the vehicle information
     */
    virtual std::vector<std::string> toRow() const {
        return {
            vehicleID,
            make,
            model,
            std::to_string(passengers),
            std::to_string(capacity),
            availability ? "Yes" : "No",
            std::to_string(getBaseRentalRate()),
            std::to_string(lateFee)
        };
    }

    /**
     * @brief Get the base rental rate for the vehicle
     *
     * @return double The base rental rate for the vehicle
     */
    virtual double getBaseRentalRate() const = 0;

    /**
     * @brief Get the type of the vehicle
     *
     * @return std::string The type of the vehicle
     */
    virtual std::string getType() const = 0;

    // Getters

    /**
     * @brief Get the vehicle ID
     *
     * @return std::string The vehicle ID
     */
    std::string getVehicleID() const;

    /**
     * @brief Get the make of the vehicle
     *
     * @return std::string The make of the vehicle
     */
    std::string getMake() const;

    /**
     * @brief Get the model of the vehicle
     *
     * @return std::string The model of the vehicle
     */
    std::string getModel() const;

    /**
     * @brief Get the number of passengers the vehicle can carry
     *
     * @return int The number of passengers
     */
    int getPassengers() const;

    /**
     * @brief Get the storage capacity of the vehicle
     *
     * @return int The storage capacity
     */
    int getCapacity() const;

    /**
     * @brief Get the availability status of the vehicle
     *
     * @return bool The availability status
     */
    bool getAvailability() const;

    /**
     * @brief Get the late fee per day
     *
     * @return double The late fee per day
     */
    double getLateFee() const;

    // Setters

    /**
     * @brief Set the availability status of the vehicle
     *
     * @param avail The availability status
     */
    void setAvailability(bool avail);

    /**
     * @brief Set the late fee per day
     *
     * @param fee The late fee per day
     */
    void setLateFee(double fee);
};

#endif // VEHICLE_H