// RentalCompany.h
#ifndef RENTALCOMPANY_H
#define RENTALCOMPANY_H

#include <string>
#include "Repository.h"
#include "Vehicle.h"
#include "Customer.h"
#include "SearchCriteria.h"

class RentalCompany {
public:
    // Constructor
    RentalCompany();

    // Destructor
    ~RentalCompany();

    // Load data from files
    void loadFromFile(const std::string& vehiclesFile, const std::string& customersFile);

    // Save data to files
    void saveToFile(const std::string& vehiclesFile, const std::string& customersFile) const;

    // Add and remove vehicles
    void addVehicle(const std::shared_ptr<Vehicle>& vehicle);
    void removeVehicle(const std::string& vehicleID);

    // Add and remove customers
    void addCustomer(const Customer& customer);
    void removeCustomer(int customerID);

    // Display all available vehicles
    void displayAvailableVehicles() const;

    // Display all vehicles
    void displayAllVehicles() const;

    // Display all customers
    void displayCustomers() const;

    // Search for vehicles and customers
    std::vector<std::shared_ptr<Vehicle>> searchVehicles(const SearchCriteria& criteria) const;
    std::vector<Customer> searchCustomers(const CustomerSearchCriteria& criteria) const;

    // Rent and return vehicles
    void rentVehicle(int customerID, const std::string& vehicleID);
    void returnVehicle(int customerID, const std::string& vehicleID, const std::string& returnDate);

    // Calculate rental cost
    double calculateRentalCost(const std::shared_ptr<Vehicle>& vehicle, int rentalDays) const;

    // Clear all data
    void clearData();

    // Search for a vehicle by its ID
    std::shared_ptr<Vehicle> searchVehicle(const std::string& vehicleID) const;

    // Search for a customer by ID
    Customer* searchCustomer(int customerID);

    const Repository<Vehicle>& getVehicleRepository() const { return vehicleRepository; }
    const Repository<Customer>& getCustomerRepository() const { return customerRepository; }

private:
    Repository<Vehicle> vehicleRepository;
    Repository<Customer> customerRepository;

    // Levenshtein Distance Algorithm
    int levenshteinDistance(const std::string& s1, const std::string& s2) const;
};

#endif // RENTALCOMPANY_H
