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


/**
 * The addVehicle function in the RentalCompany class adds a new vehicle to the repository if it does
 * not already exist.
 *
 * @param vehicle The `vehicle` parameter is a `std::shared_ptr` to an object of type `Vehicle`.
 */
void RentalCompany::addVehicle(const std::shared_ptr<Vehicle>& vehicle) {
    if (vehicleRepository.findById(vehicle->getVehicleID()) != nullptr) {
        throw std::runtime_error("Vehicle with this ID already exists.");
    }
    vehicleRepository.add(vehicle);
}

/**
 * The function `removeVehicle` removes a vehicle from a rental company's repository based on the
 * provided vehicle ID.
 *
 * @param vehicleID The `vehicleID` parameter is a `std::string` that represents the unique identifier
 * of the vehicle that needs to be removed from the `RentalCompany`'s vehicle repository.
 */
void RentalCompany::removeVehicle(const std::string& vehicleID) {
    auto vehicle = vehicleRepository.findById(vehicleID);
    if (vehicle) {
        vehicleRepository.remove(vehicle);
    } else {
        throw std::runtime_error("Vehicle with ID " + vehicleID + " not found.");
    }
}

/**
 * The function `addCustomer` adds a new customer to the rental company's customer repository, throwing
 * an error if a customer with the same ID already exists.
 *
 * @param customer The `customer` parameter is a `std::shared_ptr` to a `Customer` object. It
 * represents the customer that you want to add to the `RentalCompany`'s customer repository.
 */
void RentalCompany::addCustomer(const std::shared_ptr<Customer>& customer) {
    if (customerRepository.findById(customer->getCustomerID()) != nullptr) {
        throw std::runtime_error("Customer with this ID already exists.");
    }
    customerRepository.add(customer);
}

/**
 * The function `removeCustomer` in the `RentalCompany` class removes a customer by their ID from the
 * customer repository, throwing an error if the customer is not found.
 *
 * @param customerID The `customerID` parameter is an integer that represents the unique identifier of
 * the customer that needs to be removed from the rental company's customer repository.
 */
void RentalCompany::removeCustomer(int customerID) {
    auto customer = customerRepository.findById(customerID);
    if (customer) {
        customerRepository.remove(customer);
    } else {
        throw std::runtime_error("Error: Customer ID " + std::to_string(customerID) + " not found.");
    }
}

/**
 * The function `displayAvailableVehicles` in a C++ program displays information about available
 * vehicles in a rental company.
 *
 * @return The `displayAvailableVehicles` function is returning a list of available vehicles from the
 * `vehicleRepository` based on the availability status of each vehicle. It then displays the available
 * vehicles along with their details such as type, ID, make, model, passengers, storage capacity,
 * availability status, rental rate, and late fee per day.
 */
void RentalCompany::displayAvailableVehicles() const {
    auto availableVehicles = searchItems(vehicleRepository, [](const std::shared_ptr<Vehicle>& vehicle) {
        return vehicle->getAvailability();
    });

    std::vector<std::string> headers = { "Type", "ID", "Make", "Model", "Passengers", "Storage Capacity", "Available", "Rental Rate £/day", "Late Fee £/day" };
    std::vector<int> widths = { 8, 10, 15, 15, 10, 16, 10, 18, 18 };
    displayItems(availableVehicles, headers, widths);
}

/**
 * The function `displayAllVehicles` in the `RentalCompany` class displays information about all
 * vehicles in the repository in a tabular format.
 */
void RentalCompany::displayAllVehicles() const {
    auto allVehicles = vehicleRepository.getAll();

    std::vector<std::string> headers = { "Type", "ID", "Make", "Model", "Passengers", "Storage Capacity", "Available", "Rental Rate £/day", "Late Fee £/day" };
    std::vector<int> widths = { 8, 10, 15, 15, 10, 16, 10, 18, 18 };

    displayItems(allVehicles, headers, widths);
}

/**
 * The `displayCustomers` function in the `RentalCompany` class displays customer information with
 * specific headers and widths, while the `searchVehicle` function searches for a vehicle by ID in the
 * `vehicleRepository`.
 */
void RentalCompany::displayCustomers() const {
    auto allCustomers = customerRepository.getAll();

    std::vector<std::string> headers = { "ID", "Name", "Loyalty Points", "Rented Vehicles" };
    std::vector<int> widths = { 10, 20, 15, 30 };

    displayItems(allCustomers, headers, widths);
}

/**
 * The function `searchVehicle` in the `RentalCompany` class returns a shared pointer to a `Vehicle`
 * object found by its ID in the vehicle repository.
 *
 * @param vehicleID The `vehicleID` parameter is a `std::string` that represents the unique identifier
 * of a vehicle. In the `RentalCompany::searchVehicle` method, this parameter is used to search for a
 * vehicle in the `vehicleRepository` based on its ID. The method returns a `std
 *
 * @return A `std::shared_ptr` to a `Vehicle` object is being returned by the `searchVehicle` function.
 */
std::shared_ptr<Vehicle> RentalCompany::searchVehicle(const std::string& vehicleID) const {
    return vehicleRepository.findById(vehicleID);
}

/**
 * The function searches for a customer in a rental company by their ID and returns a pointer to the
 * customer if found.
 *
 * @param customerID The `customerID` parameter is an integer value that represents the unique
 * identifier of a customer in the `RentalCompany` system. The `searchCustomer` method in the
 * `RentalCompany` class takes this `customerID` as input and searches for the customer with the
 * corresponding ID in the
 *
 * @return A pointer to a Customer object is being returned. If the customer with the specified ID is
 * found in the customer repository, a pointer to that customer object is returned. If the customer is
 * not found, a null pointer is returned.
 */
Customer* RentalCompany::searchCustomer(int customerID) {
    auto customer = customerRepository.findById(customerID);
    return customer ? customer.get() : nullptr;
}

/**
 * The function calculates the total rental cost based on the base rental rate of a vehicle and the
 * number of rental days.
 *
 * @param vehicle A shared pointer to a Vehicle object, which represents the vehicle being rented.
 * @param rentalDays The `rentalDays` parameter represents the number of days for which the vehicle is
 * being rented. This value is used to calculate the total rental cost based on the daily rental rate
 * of the vehicle.
 *
 * @return the total rental cost for a given vehicle based on the number of rental days.
 */
double RentalCompany::calculateRentalCost(const std::shared_ptr<Vehicle>& vehicle, int rentalDays) const {
    double ratePerDay = vehicle->getBaseRentalRate();
    return ratePerDay * rentalDays;
}

/**
 * The `rentVehicle` function in the `RentalCompany` class handles the process of renting a vehicle to
 * a customer, calculating rental cost, applying loyalty discounts, setting rental dates, and awarding
 * loyalty points.
 *
 * @param customerID The `customerID` parameter in the `rentVehicle` function represents the unique
 * identifier of the customer who is renting a vehicle. This ID is used to search for the customer in
 * the system to ensure that the customer exists before proceeding with the rental process. If the
 * customer with the provided ID is not
 * @param vehicleID The `vehicleID` parameter in the `rentVehicle` function represents the unique
 * identifier of the vehicle that a customer wants to rent. This identifier is used to search for the
 * specific vehicle in the rental company's database or collection of vehicles. It helps to uniquely
 * identify the vehicle being rented to ensure the
 */
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

/**
 * The returnVehicle function in a RentalCompany class handles the process of a customer returning a
 * rented vehicle, calculating any late fees or awarding bonus loyalty points based on the return date.
 *
 * @param customerID The `customerID` parameter in the `returnVehicle` function represents the unique
 * identifier of the customer who is returning a vehicle. This ID is used to search for the specific
 * customer in the rental company's records to ensure that the customer exists and has rented a
 * vehicle. If the customer is found,
 * @param vehicleID The `vehicleID` parameter in the `returnVehicle` function represents the unique
 * identifier of the vehicle that is being returned by the customer. This identifier is used to search
 * for the specific vehicle in the rental company's records and perform operations related to the
 * return process, such as updating availability status and calculating
 * @param returnDate The `returnDate` parameter in the `returnVehicle` function represents the date on
 * which the vehicle is being returned by the customer. This date is used to calculate any potential
 * late fees if the vehicle is returned after the expected return date. The function also checks if the
 * return is timely to award bonus
 */
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

/**
 * The function `loadFromFile` reads vehicle and customer data from files, creates corresponding
 * objects, and adds them to the rental company's records.
 *
 * @param vehiclesFile The `vehiclesFile` parameter is a `std::string` that represents the file path to
 * the file containing information about vehicles. This function `loadFromFile` reads data from this
 * file to populate the rental company's vehicle inventory.
 * @param customersFile The `customersFile` parameter in the `loadFromFile` function refers to the file
 * path that contains information about customers, such as their IDs, names, loyalty points, and rented
 * vehicle IDs. This function reads data from the specified file to load customer information into the
 * rental company system.
 */
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
            std::cerr << "Warning: Unknown vehicle type \"" << type << "\" in vehicles file: " << line << "\n";
            addVehicle(std::make_shared<Car>(id, make, model, passengers, capacity, avail));
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

/**
 * The `saveToFile` function saves vehicle and customer data to specified files, while the
 * `searchVehicles` function searches for vehicles based on specified criteria.
 *
 * @param vehiclesFile The `vehiclesFile` parameter is a `std::string` that represents the file path
 * where the vehicle information will be saved. This function opens a file stream to this path and
 * writes the details of vehicles owned by the rental company to this file.
 * @param customersFile The `customersFile` parameter in the `saveToFile` function is a `std::string`
 * that represents the file path where customer information will be saved. This function is responsible
 * for writing the details of customers and their rented vehicles to a file specified by this
 * parameter.
 */
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

/**
 * The function `searchVehicles` filters vehicles based on search criteria and returns a vector of
 * shared pointers to matching vehicles.
 *
 * @param criteria The `searchVehicles` function in the `RentalCompany` class takes a `SearchCriteria`
 * object as a parameter. The `SearchCriteria` object contains the following fields:
 *
 * @return A vector of shared pointers to Vehicle objects that match the search criteria specified in
 * the SearchCriteria object.
 */
std::vector<std::shared_ptr<Vehicle>> RentalCompany::searchVehicles(const SearchCriteria& criteria) const {
    auto vehicles = vehicleRepository.getAll();
    std::vector<std::shared_ptr<Vehicle>> results;

    for (const auto& vehicle : vehicles) {
        bool matches = true;
        if (!criteria.make.empty() && levenshteinDistance(vehicle->getMake(), criteria.make) > criteria.maxDistanceMake) matches = false;
        if (!criteria.model.empty() && levenshteinDistance(vehicle->getModel(), criteria.model) > criteria.maxDistanceModel) matches = false;
        if (criteria.passengerCapacity != -1 && vehicle->getPassengers() != criteria.passengerCapacity) matches = false;
        if (criteria.storageCapacity != -1 && vehicle->getCapacity() != criteria.storageCapacity) matches = false;
        if (criteria.filterByAvailability && vehicle->getAvailability() != criteria.availability) matches = false;

        if (matches) {
            results.push_back(vehicle);
        }
    }

    return results;
}

/**
 * The function `searchCustomers` in the `RentalCompany` class searches for customers based on the
 * provided criteria and returns a vector of shared pointers to matching customers.
 *
 * @param criteria The `criteria` parameter in the `searchCustomers` function is of type
 * `CustomerSearchCriteria`. It seems to contain information used to filter and search for customers in
 * the `RentalCompany`. The criteria may include a customer ID and a name with a maximum allowed
 * distance for a fuzzy search using the
 *
 * @return A vector of shared pointers to Customer objects that match the search criteria specified in
 * the CustomerSearchCriteria parameter.
 */

std::vector<std::shared_ptr<Customer>> RentalCompany::searchCustomers(const CustomerSearchCriteria& criteria) const {
    auto customers = customerRepository.getAll();
    std::vector<std::shared_ptr<Customer>> results;

    for (const auto& customer : customers) {
        bool matches = true;
        if (criteria.customerID != -1 && customer->getCustomerID() != criteria.customerID) matches = false;
        if (!criteria.name.empty() && levenshteinDistance(customer->getName(), criteria.name) > criteria.maxDistance) matches = false;

        if (matches) {
            results.push_back(customer);
        }
    }

    return results;
}

/**
 * The clearData function clears the data stored in the vehicle and customer repositories of a rental
 * company.
 */
void RentalCompany::clearData() {
    vehicleRepository.clear();
    customerRepository.clear();
}
