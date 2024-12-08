// RentalCompany.cpp
#include "RentalCompany.h"
#include "Car.h"
#include "Van.h"
#include "Minibus.h"
#include "SUV.h"
#include "Customer.h"
#include "DateUtils.h"
#include "Utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <regex>
#include "SearchCriteria.h"

// Constructor
RentalCompany::RentalCompany() {}

// Destructor
RentalCompany::~RentalCompany() {}

// Levenshtein Distance Algorithm
int RentalCompany::levenshteinDistance(const std::string& s1, const std::string& s2) const {
    const size_t m = s1.size();
    const size_t n = s2.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    // Initialize first column
    for (size_t i = 0; i <= m; ++i) dp[i][0] = static_cast<int>(i);

    // Initialize first row
    for (size_t j = 0; j <= n; ++j) dp[0][j] = static_cast<int>(j);

    // Compute Levenshtein distance
    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            dp[i][j] = std::min({ dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost });
        }
    }

    return dp[m][n];
}

// Add a new vehicle (with duplication check)
void RentalCompany::addVehicle(const std::shared_ptr<Vehicle>& vehicle) {
    if (vehicleRepository.findById(vehicle->getVehicleID()) != nullptr) {
        throw std::runtime_error("Error: Vehicle ID " + vehicle->getVehicleID() + " already exists.");
    }
    addItem(vehicleRepository, vehicle);
}

// Remove a vehicle by its ID
void RentalCompany::removeVehicle(const std::string& vehicleID) {
    auto vehicle = searchItemById(vehicleRepository, vehicleID);
    if (vehicle) {
        removeItem(vehicleRepository, vehicle);
    } else {
        throw std::runtime_error("Error: Vehicle ID " + vehicleID + " not found.");
    }
}

// Display all available vehicles
void RentalCompany::displayAvailableVehicles() const {
    auto vehicles = vehicleRepository.getAll();
    bool anyAvailable = false;
    for (const auto& vehicle : vehicles) {
        if (vehicle->getAvailability()) {
            vehicle->displayVehicle();
            anyAvailable = true;
        }
    }
    if (!anyAvailable) {
        std::cout << "No available vehicles.\n";
    }
}

// Display all vehicles
void RentalCompany::displayAllVehicles() const {
    auto vehicles = vehicleRepository.getAll();
    if (vehicles.empty()) {
        std::cout << "No vehicles found.\n";
    } else {
        displayItems(vehicles);
    }
}

// Search for a vehicle by its ID
std::shared_ptr<Vehicle> RentalCompany::searchVehicle(const std::string& vehicleID) const {
    return searchItemById(vehicleRepository, vehicleID);
}

// Add a new customer (with duplication check)
void RentalCompany::addCustomer(const Customer& customer) {
    int customerID = customer.getCustomerID();
    if (customerRepository.findById(customerID) != nullptr) {
        throw std::runtime_error("Error: Customer ID " + std::to_string(customerID) + " already exists.");
    }
    addItem(customerRepository, std::make_shared<Customer>(customer));
}

// Remove a customer by ID
void RentalCompany::removeCustomer(int customerID) {
    auto customer = searchItemById(customerRepository, customerID);
    if (customer) {
        removeItem(customerRepository, customer);
    } else {
        throw std::runtime_error("Error: Customer ID " + std::to_string(customerID) + " not found.");
    }
}

// Display all customers
void RentalCompany::displayCustomers() const {
    auto customers = customerRepository.getAll();
    if (customers.empty()) {
        std::cout << "No customers found.\n";
    } else {
        displayItems(customers);
    }
}

// Search for a customer by ID
Customer* RentalCompany::searchCustomer(int customerID) {
    auto customer = searchItemById(customerRepository, customerID);
    return customer ? customer.get() : nullptr;
}

// Rent a vehicle
void RentalCompany::rentVehicle(int customerID, const std::string& vehicleID) {
    auto customer = searchCustomer(customerID);
    if (!customer) {
        throw std::runtime_error("Error: Customer ID " + std::to_string(customerID) + " not found.");
    }

    auto vehicle = searchVehicle(vehicleID);
    if (!vehicle) {
        throw std::runtime_error("Error: Vehicle ID " + vehicleID + " not found.");
    }

    if (!vehicle->getAvailability()) {
        throw std::runtime_error("Error: Vehicle ID " + vehicleID + " is not available.");
    }

    std::string rentDate = DateUtils::getCurrentDate();
    std::string dueDate = DateUtils::addDays(rentDate, 7); // Example: 7-day rental period

    customer->rentVehicle(vehicle, rentDate, dueDate);
    vehicle->setAvailability(false);
}

// Return a vehicle
void RentalCompany::returnVehicle(int customerID, const std::string& vehicleID, const std::string& returnDate) {
    auto customer = searchCustomer(customerID);
    if (!customer) {
        throw std::runtime_error("Error: Customer ID " + std::to_string(customerID) + " not found.");
    }

    auto vehicle = searchVehicle(vehicleID);
    if (!vehicle) {
        throw std::runtime_error("Error: Vehicle ID " + vehicleID + " not found.");
    }

    int daysLate = customer->returnVehicle(vehicle, returnDate);
    vehicle->setAvailability(true);

    if (daysLate > 0) {
        double lateFee = daysLate * vehicle->getLateFee();
        std::cout << "Late fee for " << daysLate << " days: $" << lateFee << "\n";
    }
}

// Load data from files
void RentalCompany::loadFromFile(const std::string& vehiclesFile, const std::string& customersFile) {
    std::ifstream vFile(vehiclesFile);
    std::ifstream cFile(customersFile);

    if (!vFile.is_open()) {
        throw std::runtime_error("Error: Could not open vehicles file.");
    }

    std::string line;
    while (std::getline(vFile, line)) {
        std::istringstream iss(line);
        std::string type, id, make, model;
        int passengers, capacity, availInt;
        bool avail;

        if (!(iss >> type >> id >> std::quoted(make) >> std::quoted(model) >> passengers >> capacity >> availInt)) {
            continue;
        }
        avail = static_cast<bool>(availInt);

        if (type == "Car") {
            addVehicle(std::make_shared<Car>(id, make, model, passengers, capacity, avail));
        } else if (type == "Van") {
            addVehicle(std::make_shared<Van>(id, make, model, passengers, capacity, avail));
        } else if (type == "Minibus") {
            addVehicle(std::make_shared<Minibus>(id, make, model, passengers, capacity, avail));
        } else if (type == "SUV") {
            addVehicle(std::make_shared<SUV>(id, make, model, passengers, capacity, avail));
        }
    }

    if (!cFile.is_open()) {
        throw std::runtime_error("Error: Could not open customers file.");
    }

    while (std::getline(cFile, line)) {
        std::istringstream iss(line);
        int customerID;
        std::string name;
        if (!(iss >> customerID >> std::quoted(name))) {
            continue;
        }

        Customer customer(customerID, name);
        std::string vehicleID;
        while (iss >> vehicleID) {
            auto vehicle = searchVehicle(vehicleID);
            if (vehicle) {
                customer.addRental({ vehicle, DateUtils::getCurrentDate(), DateUtils::addDays(DateUtils::getCurrentDate(), 7) });
                vehicle->setAvailability(false);
            }
        }
        addCustomer(customer);
    }
}

// Save data to files
void RentalCompany::saveToFile(const std::string& vehiclesFile, const std::string& customersFile) const {
    std::ofstream vFile(vehiclesFile);
    std::ofstream cFile(customersFile);

    if (!vFile.is_open()) {
        throw std::runtime_error("Error: Could not open vehicles file for writing.");
    }

    auto vehicles = vehicleRepository.getAll();
    for (const auto& vehicle : vehicles) {
        vFile << vehicle->getVehicleID() << " " << std::quoted(vehicle->getMake()) << " "
              << std::quoted(vehicle->getModel()) << " " << vehicle->getPassengers() << " "
              << vehicle->getCapacity() << " " << vehicle->getAvailability() << "\n";
    }

    if (!cFile.is_open()) {
        throw std::runtime_error("Error: Could not open customers file for writing.");
    }

    auto customers = customerRepository.getAll();
    for (const auto& customer : customers) {
        cFile << customer->getCustomerID() << " " << std::quoted(customer->getName());
        for (const auto& rental : customer->getRentedVehicles()) {
            cFile << " " << rental.vehicle->getVehicleID();
        }
        cFile << "\n";
    }
}

// Search Vehicles with Fuzzy Matching
std::vector<std::shared_ptr<Vehicle>> RentalCompany::searchVehicles(const SearchCriteria& criteria) const {
    auto vehicleCriteria = [&](const std::shared_ptr<Vehicle>& vehicle) -> bool {
        bool matches = true;
        if (!criteria.make.empty() && levenshteinDistance(vehicle->getMake(), criteria.make) > criteria.maxDistance) {
            matches = false;
        }
        if (!criteria.model.empty() && levenshteinDistance(vehicle->getModel(), criteria.model) > criteria.maxDistance) {
            matches = false;
        }
        if (criteria.passengerCapacity != -1 && vehicle->getPassengers() != criteria.passengerCapacity) {
            matches = false;
        }
        if (criteria.storageCapacity != -1 && vehicle->getCapacity() != criteria.storageCapacity) {
            matches = false;
        }
        if (criteria.filterByAvailability && vehicle->getAvailability() != criteria.availability) {
            matches = false;
        }
        return matches;
    };

    return searchItems(vehicleRepository, vehicleCriteria);
}

// Search Customers with Fuzzy Matching
std::vector<Customer> RentalCompany::searchCustomers(const CustomerSearchCriteria& criteria) const {
    auto customerCriteria = [&](const std::shared_ptr<Customer>& customer) -> bool {
        bool matches = true;
        if (criteria.customerID != -1 && customer->getCustomerID() != criteria.customerID) {
            matches = false;
        }
        if (!criteria.name.empty() && levenshteinDistance(customer->getName(), criteria.name) > criteria.maxDistance) {
            matches = false;
        }
        return matches;
    };

    auto results = searchItems(customerRepository, customerCriteria);
    std::vector<Customer> customerResults;
    for (const auto& customer : results) {
        customerResults.emplace_back(*customer);
    }
    return customerResults;
}

// Clear all data
void RentalCompany::clearData() {
    vehicleRepository.clear();
    customerRepository.clear();
}
