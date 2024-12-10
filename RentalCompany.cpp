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

// Add a new vehicle (with duplication check)
void RentalCompany::addVehicle(const std::shared_ptr<Vehicle>& vehicle) {
    if (vehicleRepository.findById(vehicle->getVehicleID()) != nullptr) {
        throw std::runtime_error("Error: Vehicle ID " + vehicle->getVehicleID() + " already exists.");
    }
    vehicleRepository.add(vehicle);
}

// Remove a vehicle by its ID
void RentalCompany::removeVehicle(const std::string& vehicleID) {
    auto vehicle = vehicleRepository.findById(vehicleID);
    if (vehicle) {
        vehicleRepository.remove(vehicle);
    } else {
        throw std::runtime_error("Error: Vehicle ID " + vehicleID + " not found.");
    }
}

// Add a new customer (with duplication check)
void RentalCompany::addCustomer(const std::shared_ptr<Customer>& customer) {
    if (customerRepository.findById(customer->getCustomerID()) != nullptr) {
        throw std::runtime_error("Error: Customer ID " + std::to_string(customer->getCustomerID()) + " already exists.");
    }
    customerRepository.add(customer);
}

// Remove a customer by ID
void RentalCompany::removeCustomer(int customerID) {
    auto customer = customerRepository.findById(customerID);
    if (customer) {
        customerRepository.remove(customer);
    } else {
        throw std::runtime_error("Error: Customer ID " + std::to_string(customerID) + " not found.");
    }
}

// Display available vehicles
void RentalCompany::displayAvailableVehicles() const {
    auto vehicles = vehicleRepository.getAll();
    std::vector<std::shared_ptr<Vehicle>> availableVehicles;
    for (const auto& vehicle : vehicles) {
        if (vehicle->getAvailability()) {
            availableVehicles.push_back(vehicle);
        }
    }

    std::vector<std::string> headers = {"ID", "Make", "Model", "Passengers", "Storage", "Available", "Rate", "Late Fee"};
    std::vector<int> widths = {6, 10, 10, 12, 8, 10, 6, 10};

    displayItems(availableVehicles, headers, widths);
}

// Display all vehicles
void RentalCompany::displayAllVehicles() const {
    auto vehicles = vehicleRepository.getAll();
    std::vector<std::string> headers = {"ID", "Make", "Model", "Passengers", "Storage", "Available", "Rate", "Late Fee"};
    std::vector<int> widths = {6, 10, 10, 12, 8, 10, 6, 10};

    displayItems(vehicles, headers, widths);
}

// Display all customers
void RentalCompany::displayCustomers() const {
    auto customers = customerRepository.getAll();
    std::vector<std::string> headers = {"ID", "Name", "Loyalty Points", "Rented Vehicles"};
    std::vector<int> widths = {4, 9, 14, 20};

    displayItems(customers, headers, widths);
}

// Search for a vehicle by its ID
std::shared_ptr<Vehicle> RentalCompany::searchVehicle(const std::string& vehicleID) const {
    return vehicleRepository.findById(vehicleID);
}

// Search for a customer by ID
Customer* RentalCompany::searchCustomer(int customerID) {
    auto customer = customerRepository.findById(customerID);
    return customer ? customer.get() : nullptr;
}

// Calculate Rental Cost
double RentalCompany::calculateRentalCost(const std::shared_ptr<Vehicle>& vehicle, int rentalDays) const {
    double ratePerDay = vehicle->getBaseRentalRate();
    return ratePerDay * rentalDays;
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

    // For simplicity, assume rental period is fixed at 7 days
    int rentalDays = 7;
    double rentalCost = calculateRentalCost(vehicle, rentalDays);

    std::cout << "Rental Cost for " << rentalDays << " days: $" << rentalCost << "\n";

    // Check for loyalty discount
    bool discountApplied = false;
    double discountAmount = 0.0;
    if (customer->getLoyaltyPoints() >= 100) { // Threshold for discount
        discountApplied = customer->applyLoyaltyDiscount(); // Deduct points and apply discount
        if (discountApplied) {
            discountAmount = rentalCost * 0.30; // 30% discount
            rentalCost -= discountAmount;
            std::cout << "Loyalty Discount Applied! Deducted 100 points. Discount Amount: $" << discountAmount << "\n";
            std::cout << "New Rental Cost: $" << rentalCost << "\n";
        }
    }

    // Proceed with rental
    std::string rentDate = DateUtils::getCurrentDate();
    std::string dueDate = DateUtils::addDays(rentDate, rentalDays);

    customer->rentVehicle(vehicle, rentDate, dueDate);
    vehicle->setAvailability(false);

    // Award loyalty points, e.g., 10 points per rental
    int earnedPoints = 10;
    customer->addLoyaltyPoints(earnedPoints);
    std::cout << "Loyalty Points Earned: " << earnedPoints << "\n\n";
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

    // Check if the customer has rented this vehicle
    if (!customer->hasRentedVehicle(vehicle)) {
        throw std::runtime_error("Error: Customer ID " + std::to_string(customerID) + " has not rented Vehicle ID " + vehicleID + ".");
    }

    int daysLate = customer->returnVehicle(vehicle, returnDate);
    vehicle->setAvailability(true);

    if (daysLate > 0) {
        double lateFee = daysLate * vehicle->getLateFee();
        std::cout << "Late fee for " << daysLate << " days: $" << lateFee << "\n";
    } else {
        // Award bonus loyalty points for timely return
        int bonusPoints = 5;
        customer->addLoyaltyPoints(bonusPoints);
        std::cout << "Timely return! Bonus Loyalty Points Earned: " << bonusPoints << "\n";
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
        std::string typeOrId, id, make, model;
        int passengers, capacity, availInt;
        bool avail;

        // Attempt to read the first token
        if (!(iss >> typeOrId)) {
            continue; // Skip malformed lines
        }

        // List of known vehicle types
        const std::vector<std::string> knownTypes = {"Car", "Van", "Minibus", "SUV"};

        std::string type;
        if (std::find(knownTypes.begin(), knownTypes.end(), typeOrId) != knownTypes.end()) {
            // The first token is a known type
            type = typeOrId;

            if (!(iss >> id >> std::quoted(make) >> std::quoted(model) >> passengers >> capacity >> availInt)) {
                std::cerr << "Warning: Malformed line in vehicles file: " << line << "\n";
                continue;
            }
        }
        else {
            // The first token is not a known type; assume default type "Car"
            type = "Car";
            id = typeOrId;

            if (!(iss >> std::quoted(make) >> std::quoted(model) >> passengers >> capacity >> availInt)) {
                std::cerr << "Warning: Malformed line in vehicles file: " << line << "\n";
                continue;
            }
        }

        avail = static_cast<bool>(availInt);

        // Create the appropriate vehicle object
        if (type == "Car") {
            addVehicle(std::make_shared<Car>(id, make, model, passengers, capacity, avail));
        }
        else if (type == "Van") {
            addVehicle(std::make_shared<Van>(id, make, model, passengers, capacity, avail));
        }
        else if (type == "Minibus") {
            addVehicle(std::make_shared<Minibus>(id, make, model, passengers, capacity, avail));
        }
        else if (type == "SUV") {
            addVehicle(std::make_shared<SUV>(id, make, model, passengers, capacity, avail));
        }
        else {
            std::cerr << "Warning: Unknown vehicle type \"" << type << "\" in vehicles file.\n";
            continue;
        }
    }

    if (!cFile.is_open()) {
        throw std::runtime_error("Error: Could not open customers file.");
    }

    while (std::getline(cFile, line)) {
        std::istringstream iss(line);
        int customerID;
        std::string name;

        // Attempt to read customerID and name
        if (!(iss >> customerID >> std::quoted(name))) {
            std::cerr << "Warning: Malformed line in customers file: " << line << "\n";
            continue;
        }

        int loyaltyPoints = 0;

        // Store the current position before attempting to read loyaltyPoints
        std::streampos pos = iss.tellg();

        // Attempt to read loyaltyPoints
        if (!(iss >> loyaltyPoints)) {
            // If reading loyaltyPoints fails, reset the stream to the stored position
            iss.clear(); // Clear the error flags
            iss.seekg(pos); // Seek back to the stored position
        }

        auto customer = std::make_shared<Customer>(customerID, name);
        customer->setLoyaltyPoints(loyaltyPoints);

        std::string vehicleID;
        while (iss >> vehicleID) {
            auto vehicle = searchVehicle(vehicleID);
            if (vehicle) {
                // For simplicity, assume current date as rent date and rent period as 7 days
                std::string rentDate = DateUtils::getCurrentDate();
                std::string dueDate = DateUtils::addDays(rentDate, 7);
                RentalInfo rental = { vehicle, rentDate, dueDate };
                customer->addRental(rental);
                vehicle->setAvailability(false);
            }
            else {
                std::cerr << "Warning: Vehicle ID \"" << vehicleID << "\" not found for customer ID " << customerID << ".\n";
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
        // Determine vehicle type
        std::string type;
        if (dynamic_cast<Car*>(vehicle.get())) {
            type = "Car";
        }
        else if (dynamic_cast<Van*>(vehicle.get())) {
            type = "Van";
        }
        else if (dynamic_cast<Minibus*>(vehicle.get())) {
            type = "Minibus";
        }
        else if (dynamic_cast<SUV*>(vehicle.get())) {
            type = "SUV";
        }
        else {
            type = "Unknown";
        }

        vFile << type << " " << vehicle->getVehicleID() << " " << std::quoted(vehicle->getMake()) << " "
              << std::quoted(vehicle->getModel()) << " " << vehicle->getPassengers() << " "
              << vehicle->getCapacity() << " " << vehicle->getAvailability() << "\n";
    }

    if (!cFile.is_open()) {
        throw std::runtime_error("Error: Could not open customers file for writing.");
    }

    auto customers = customerRepository.getAll();
    for (const auto& customer : customers) {
        cFile << customer->getCustomerID() << " " << std::quoted(customer->getName()) << " " << customer->getLoyaltyPoints();
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
std::vector<std::shared_ptr<Customer>> RentalCompany::searchCustomers(const CustomerSearchCriteria& criteria) const {
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

    return searchItems(customerRepository, customerCriteria);
}

// Clear all data
void RentalCompany::clearData() {
    vehicleRepository.clear();
    customerRepository.clear();
}
