// RentalCompany.h
#ifndef RENTALCOMPANY_H
#define RENTALCOMPANY_H

#include <string>
#include <vector>
#include <memory>
#include "Repository.h"
#include "Vehicle.h"
#include "Customer.h"
#include "SearchCriteria.h"

// RentalCompany class definition
class RentalCompany {
public:
    /**
     * @brief Construct a new RentalCompany object
     */
    RentalCompany();

    /**
     * @brief Destroy the RentalCompany object
     */
    ~RentalCompany();

    /**
     * @brief Load data from files
     *
     * @param vehiclesFile The file containing vehicle data
     * @param customersFile The file containing customer data
     */
    void loadFromFile(const std::string& vehiclesFile, const std::string& customersFile);

    /**
     * @brief Save data to files
     *
     * @param vehiclesFile The file to save vehicle data
     * @param customersFile The file to save customer data
     */
    void saveToFile(const std::string& vehiclesFile, const std::string& customersFile) const;

    // Vehicle management

    /**
     * @brief Add a vehicle to the repository
     *
     * @param vehicle The vehicle to add
     */
    void addVehicle(const std::shared_ptr<Vehicle>& vehicle);

    /**
     * @brief Remove a vehicle from the repository by its ID
     *
     * @param vehicleID The ID of the vehicle to remove
     */
    void removeVehicle(const std::string& vehicleID);

    /**
     * @brief Display all available vehicles
     */
    void displayAvailableVehicles() const;

    /**
     * @brief Display all vehicles
     */
    void displayAllVehicles() const;

    /**
     * @brief Search for vehicles based on search criteria
     *
     * @param criteria The search criteria
     * @return std::vector<std::shared_ptr<Vehicle>> A vector of vehicles matching the criteria
     */
    std::vector<std::shared_ptr<Vehicle>> searchVehicles(const SearchCriteria& criteria) const;

    /**
     * @brief Search for a vehicle by its ID
     *
     * @param vehicleID The ID of the vehicle to search for
     * @return std::shared_ptr<Vehicle> The vehicle with the specified ID
     */
    std::shared_ptr<Vehicle> searchVehicle(const std::string& vehicleID) const;

    // Customer management

    /**
     * @brief Add a customer to the repository
     *
     * @param customer The customer to add
     */
    void addCustomer(const std::shared_ptr<Customer>& customer);

    /**
     * @brief Remove a customer from the repository by their ID
     *
     * @param customerID The ID of the customer to remove
     */
    void removeCustomer(int customerID);

    /**
     * @brief Display all customers
     */
    void displayCustomers() const;

    /**
     * @brief Display all customers (duplicate method, consider removing one)
     */
    void displayAllCustomers() const;

    /**
     * @brief Search for customers based on search criteria
     *
     * @param criteria The search criteria
     * @return std::vector<std::shared_ptr<Customer>> A vector of customers matching the criteria
     */
    std::vector<std::shared_ptr<Customer>> searchCustomers(const CustomerSearchCriteria& criteria) const;

    /**
     * @brief Search for a customer by their ID
     *
     * @param customerID The ID of the customer to search for
     * @return Customer* The customer with the specified ID
     */
    Customer* searchCustomer(int customerID);

    // Rental management

    /**
     * @brief Rent a vehicle to a customer
     *
     * @param customerID The ID of the customer renting the vehicle
     * @param vehicleID The ID of the vehicle to rent
     */
    void rentVehicle(int customerID, const std::string& vehicleID);

    /**
     * @brief Return a rented vehicle
     *
     * @param customerID The ID of the customer returning the vehicle
     * @param vehicleID The ID of the vehicle being returned
     * @param returnDate The date the vehicle is returned
     */
    void returnVehicle(int customerID, const std::string& vehicleID, const std::string& returnDate);

    /**
     * @brief Calculate the rental cost for a vehicle
     *
     * @param vehicle The vehicle being rented
     * @param rentalDays The number of days the vehicle is rented
     * @return double The rental cost
     */
    double calculateRentalCost(const std::shared_ptr<Vehicle>& vehicle, int rentalDays) const;

    // Data management

    /**
     * @brief Clear all data from the repositories
     */
    void clearData();

    // Getters for repositories

    /**
     * @brief Get the vehicle repository
     *
     * @return const Repository<Vehicle>& The vehicle repository
     */
    const Repository<Vehicle>& getVehicleRepository() const { return vehicleRepository; }

    /**
     * @brief Get the customer repository
     *
     * @return const Repository<Customer>& The customer repository
     */
    const Repository<Customer>& getCustomerRepository() const { return customerRepository; }

private:
    // Repositories for storing vehicles and customers
    Repository<Vehicle> vehicleRepository;
    Repository<Customer> customerRepository;
};

#endif // RENTALCOMPANY_H