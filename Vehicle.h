// Vehicle.h
#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

class Vehicle {
protected:
    std::string vehicleID;
    std::string make;
    std::string model;
    int passengers;
    int capacity;
    bool availability;
    double lateFee; // Late fee per day

public:
    // Constructor
    Vehicle(const std::string& id, const std::string& mk, const std::string& mdl,
            int passengers, int storage, bool avail);

    // Default virtual destructor
    virtual ~Vehicle() = default;

    // Display row for table
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

    // Pure virtual function
    virtual double getBaseRentalRate() const = 0;

    // Pure virtual function
    virtual std::string getType() const = 0;

    // Getters
    std::string getVehicleID() const;
    std::string getMake() const;
    std::string getModel() const;
    int getPassengers() const;
    int getCapacity() const;
    bool getAvailability() const;
    double getLateFee() const;

    // Setters
    void setAvailability(bool avail);
    void setLateFee(double fee);
};

#endif // VEHICLE_H
