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

    // Common displayVehicle method
    virtual void displayVehicle() const {
        std::cout << "### Vehicle Details ###\n";
        std::cout << "ID: " << vehicleID << "\n"
                  << "Make: " << make << "\n"
                  << "Model: " << model << "\n"
                  << "Passenger Capacity: " << passengers << "\n"
                  << "Storage Capacity: " << capacity << "\n"
                  << "Available: " << (availability ? "Yes" : "No") << "\n"
                  << "Base Rental Rate: $" << getBaseRentalRate() << "/day\n"
                  << "Late Fee: $" << lateFee << "/day\n\n";
    }

    // Display row for table
    virtual void displayRow(const std::vector<int>& widths) const {
        std::cout << " " << std::setw(widths[0]) << vehicleID
                  << " | " << std::setw(widths[1]) << make
                  << " | " << std::setw(widths[2]) << model
                  << " | " << std::setw(widths[3]) << passengers
                  << " | " << std::setw(widths[4]) << capacity
                  << " | " << std::setw(widths[5]) << (availability ? "Yes" : "No")
                  << " | " << std::setw(widths[6]) << getBaseRentalRate()
                  << " | " << std::setw(widths[7]) << lateFee << " |";
    }

    // Display row for table
    virtual std::vector<std::string> toRow() const {
        return {
            vehicleID,
            make,
            model,
            std::to_string(passengers),
            std::to_string(capacity),
            availability ? "Yes" : "No"
        };
    }

    // Pure virtual function
    virtual double getBaseRentalRate() const = 0;

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
