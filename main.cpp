// main.cpp
#include "RentalCompany.h"
#include "Utils.h"
#include "Car.h"
#include "Van.h"
#include "Minibus.h"
#include "SUV.h"
#include "DateUtils.h"
#include <iostream>
#include <limits>
#include <string>

// Function declarations
void displayMainMenu();
void runSpecificTests(RentalCompany& company);
void handleRentVehicle(RentalCompany& company);
void handleReturnVehicle(RentalCompany& company);
void handleDisplayAvailableVehicles(RentalCompany& company);
void handleDisplayCustomers(RentalCompany& company);
void handleSearchVehicles(RentalCompany& company);
void handleSearchCustomers(RentalCompany& company);
void displaySearchResults(const std::vector<std::shared_ptr<Vehicle>>& results);
void displayCustomerSearchResults(const std::vector<std::shared_ptr<Customer>>& results);
void handleAddCustomer(RentalCompany& company);
void handleAddVehicle(RentalCompany& company);
void handleDisplayAllVehicles(RentalCompany& company);

int main() {
    RentalCompany company;
    company.loadFromFile("mainVehicles.txt", "mainCustomers.txt");

    int choice;

    do {
        displayMainMenu();
        std::cin >> choice;

        // Validate input
        while (std::cin.fail() || choice < 1 || choice > 11) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 11: ";
            std::cin >> choice;
        }

        switch (choice) {
            case 1:
                handleAddCustomer(company);
                company.saveToFile("mainVehicles.txt", "mainCustomers.txt");
                break;
            case 2:
                handleAddVehicle(company);
                company.saveToFile("mainVehicles.txt", "mainCustomers.txt");
                break;
            case 3:
                handleRentVehicle(company);
                company.saveToFile("mainVehicles.txt", "mainCustomers.txt");
                break;
            case 4:
                handleReturnVehicle(company);
                company.saveToFile("mainVehicles.txt", "mainCustomers.txt");
                break;
            case 5:
                handleDisplayAvailableVehicles(company);
                break;
            case 6:
                handleDisplayAllVehicles(company);
                break;
            case 7:
                handleDisplayCustomers(company);
                break;
            case 8:
                handleSearchVehicles(company);
                break;
            case 9:
                handleSearchCustomers(company);
                break;
            case 10:
                runSpecificTests(company);
                company.loadFromFile("mainVehicles.txt", "mainCustomers.txt");
                break;
            case 11:
                // Save data before exiting
                company.saveToFile("mainVehicles.txt", "mainCustomers.txt");
                std::cout << "Exiting program. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 11);

    return 0;
}

// Function definitions

void displayMainMenu() {
    std::cout << "\n=== Rental Company Menu ===\n";
    std::cout << "1. Add Customer\n";
    std::cout << "2. Add Vehicle\n";
    std::cout << "3. Rent Vehicle\n";
    std::cout << "4. Return Vehicle\n";
    std::cout << "5. Display Available Vehicles\n";
    std::cout << "6. Display All Vehicles\n";
    std::cout << "7. Display Customers\n";
    std::cout << "8. Search Vehicles\n";
    std::cout << "9. Search Customers\n";
    std::cout << "10. Run Specific Tests\n";
    std::cout << "11. Exit\n";
    std::cout << "Enter your choice: ";
}

// Run Specific Tests
void runSpecificTests(RentalCompany& company) {
    std::cout << "\n=== Running Specific Test Scenarios ===\n\n";

    // Clear existing data
    company.clearData();

    // Test 1: Loading sample data files...
    std::cout << "Test 1: Loading sample data files...\n";
    try {
        company.loadFromFile("vehicles.txt", "customers.txt");
        std::cout << "Test 1 PASSED: Sample data files loaded successfully.\n\n";
    } catch (const std::exception& e) {
        std::cout << "Test 1 FAILED: " << e.what() << "\n\n";
    }

    // Test 2: Adding new Car - V108 Vauxhall Corsa...
    std::cout << "Test 2: Adding new Car - V108 Vauxhall Corsa...\n";
    std::shared_ptr<Vehicle> car = std::make_shared<Car>("V108", "Vauxhall", "Corsa", 4, 32, true);
    company.addVehicle(car);
    std::cout << "Test 2 PASSED: Car V108 Vauxhall Corsa added successfully.\n\n";

    // Test 3: Adding new Customer - Christina (ID:106)...
    std::cout << "Test 3: Adding new Customer - Christina (ID:106)...\n";
    Customer customer(106, "Christina");
    company.addCustomer(customer);
    std::cout << "Test 3 PASSED: Customer Christina added successfully.\n\n";

    // Test 4a: David (ID:104) returning vehicle V106...
    std::cout << "Test 4a: David (ID:104) returning vehicle V106...\n";
    try {
        company.returnVehicle(104, "V106", DateUtils::getCurrentDate());
        std::cout << "Test 4a PASSED: David returned vehicle V106 successfully.\n\n";
    }
    catch (const std::exception& e) {
        std::cout << "Test 4a FAILED: " << e.what() << "\n\n";
    }

    // Test 4b: Alice (ID:101) renting vehicle V106...
    std::cout << "Test 4b: Alice (ID:101) renting vehicle V106...\n";
    try {
        company.rentVehicle(101, "V106");
        std::cout << "Test 4b PASSED: Alice rented vehicle V106 successfully.\n\n";
    } catch (const std::exception& e) {
        std::cout << "Test 4b FAILED: " << e.what() << "\n\n";
    }

    // Test 5: Alice (ID:101) returning vehicle V106...
    std::cout << "Test 5: Alice (ID:101) returning vehicle V106...\n";
    try {
        company.returnVehicle(101, "V106", DateUtils::getCurrentDate());
        std::cout << "Test 5 PASSED: Alice returned vehicle V106 successfully.\n\n";
    } catch (const std::exception& e) {
        std::cout << "Test 5 FAILED: " << e.what() << "\n\n";
    }

    // Test 6: Searching for Car Make: Audi, Model: Q8...
    std::cout << "Test 6: Searching for Car Make: Audi, Model: Q8...\n";
    SearchCriteria criteria;
    criteria.make = "Audi";
    criteria.model = "Q8";
    std::vector<std::shared_ptr<Vehicle>> searchResults = company.searchVehicles(criteria);
    if (!searchResults.empty()) {
        std::cout << "Test 6 PASSED: Audi Q8 found.\n\n";
        for (const auto& vehicle : searchResults) {
            vehicle->displayVehicle();
        }
    } else {
        std::cout << "Test 6 FAILED: Audi Q8 not found.\n\n";
    }

    // Test 7a: Adding new Car - V109 Toyota Corolla...
    std::cout << "Test 7a: Adding new Car - V109 Toyota Corolla...\n";
    std::shared_ptr<Vehicle> car2 = std::make_shared<Car>("V109", "Toyota", "Corolla", 5, 35, true);
    company.addVehicle(car2);
    std::cout << "Test 7a PASSED: Car V109 Toyota Corolla added successfully.\n\n";

    // Test 7b: Bob (ID:102) renting vehicle V109...
    std::cout << "Test 7b: Bob (ID:102) renting vehicle V109...\n";
    try {
        company.rentVehicle(102, "V109");
        std::cout << "Test 7b PASSED: Bob rented vehicle V109 successfully.\n\n";
    } catch (const std::exception& e) {
        std::cout << "Test 7b FAILED: " << e.what() << "\n\n";
    }

    // Test 8: Exporting data to new files...
    std::cout << "Test 8: Exporting data to new files...\n";
    try {
        company.saveToFile("vehiclesTestOutput.txt", "customersTestOutput.txt");
        std::cout << "Test 8 PASSED: Data exported successfully to vehiclesTestOutput.txt and customersTestOutput.txt!\n\n";
    } catch (const std::exception& e) {
        std::cout << "Test 8 FAILED: " << e.what() << "\n\n";
    }

    std::cout << "=== Specific Test Scenarios Completed ===\n\n";
}

void handleRentVehicle(RentalCompany& company) {
    int customerID;
    std::string vehicleID;

    std::cout << "Enter Customer ID: ";
    std::cin >> customerID;

    std::cout << "Enter Vehicle ID to rent: ";
    std::cin >> vehicleID;

    try {
        company.rentVehicle(customerID, vehicleID);
        std::cout << "Vehicle rented successfully.\n\n";
        std::cout << "You must return the vehicle within 7 days.\n";
    }
    catch (const std::exception& e) {
        std::cout << "Rental Failed: " << e.what() << "\n\n";
    }
}

void handleReturnVehicle(RentalCompany& company) {
    int customerID;
    std::string vehicleID;
    std::string returnDate;

    std::cout << "Enter Customer ID: ";
    std::cin >> customerID;

    std::cout << "Enter Vehicle ID to return: ";
    std::cin >> vehicleID;

    std::cout << "Enter Return Date (YYYY-MM-DD): ";
    std::cin >> returnDate;

    try {
        company.returnVehicle(customerID, vehicleID, returnDate);
        std::cout << "Vehicle returned successfully.\n\n";
    }
    catch (const std::exception& e) {
        std::cout << "Return Failed: " << e.what() << "\n\n";
    }
}

void handleDisplayAvailableVehicles(RentalCompany& company) {
    company.displayAvailableVehicles();
}

void handleDisplayAllVehicles(RentalCompany& company) {
    std::cout << "=== All Vehicles ===\n";
    company.displayAllVehicles();
}

void handleDisplayCustomers(RentalCompany& company) {
    company.displayCustomers();
}

void handleSearchVehicles(RentalCompany& company) {
    SearchCriteria criteria;
    char choice;
    bool done = false;

    while (!done) {
        std::cout << "\n=== Vehicle Search Menu ===\n";
        std::cout << "1. Set Make\n";
        std::cout << "2. Set Model\n";
        std::cout << "3. Set Passenger Capacity\n";
        std::cout << "4. Set Storage Capacity\n";
        std::cout << "5. Set Availability\n";
        std::cout << "6. View Results\n";
        std::cout << "7. Exit Search\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                std::cout << "Enter Make: ";
                std::cin >> criteria.make;
                break;
            case '2':
                std::cout << "Enter Model: ";
                std::cin >> criteria.model;
                break;
            case '3':
                std::cout << "Enter Passenger Capacity: ";
                std::cin >> criteria.passengerCapacity;
                break;
            case '4':
                std::cout << "Enter Storage Capacity: ";
                std::cin >> criteria.storageCapacity;
                break;
            case '5':
                std::cout << "Filter by Availability (1 for Yes, 0 for No): ";
                std::cin >> criteria.filterByAvailability;
                if (criteria.filterByAvailability) {
                    std::cout << "Enter Availability (1 for Yes, 0 for No): ";
                    std::cin >> criteria.availability;
                }
                break;
            case '6': {
                auto results = searchItems(company.getVehicleRepository(), [&criteria](const std::shared_ptr<Vehicle>& vehicle) {
                    bool matches = true;
                    if (!criteria.make.empty() && vehicle->getMake() != criteria.make) matches = false;
                    if (!criteria.model.empty() && vehicle->getModel() != criteria.model) matches = false;
                    if (criteria.passengerCapacity != -1 && vehicle->getPassengers() != criteria.passengerCapacity) matches = false;
                    if (criteria.storageCapacity != -1 && vehicle->getCapacity() != criteria.storageCapacity) matches = false;
                    if (criteria.filterByAvailability && vehicle->getAvailability() != criteria.availability) matches = false;
                    return matches;
                });
                displaySearchResults(results);
                break;
            }
            case '7':
                done = true;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

void handleSearchCustomers(RentalCompany& company) {
    CustomerSearchCriteria criteria;
    char choice;
    bool done = false;

    while (!done) {
        std::cout << "\n=== Customer Search Menu ===\n";
        std::cout << "1. Set Customer ID\n";
        std::cout << "2. Set Name\n";
        std::cout << "3. View Results\n";
        std::cout << "4. Exit Search\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                std::cout << "Enter Customer ID: ";
                std::cin >> criteria.customerID;
                break;
            case '2':
                std::cout << "Enter Name: ";
                std::cin >> criteria.name;
                break;
            case '3': {
                auto results = searchItems(company.getCustomerRepository(), [&criteria](const std::shared_ptr<Customer>& customer) {
                    bool matches = true;
                    if (criteria.customerID != -1 && customer->getCustomerID() != criteria.customerID) matches = false;
                    if (!criteria.name.empty() && customer->getName() != criteria.name) matches = false;
                    return matches;
                });
                displayCustomerSearchResults(results);
                break;
            }
            case '4':
                done = true;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

void displaySearchResults(const std::vector<std::shared_ptr<Vehicle>>& results) {
    if (results.empty()) {
        std::cout << "No vehicles found matching the criteria.\n";
    } else {
        for (const auto& vehicle : results) {
            vehicle->displayVehicle();
        }
    }
}

void displayCustomerSearchResults(const std::vector<std::shared_ptr<Customer>>& results) {
    if (results.empty()) {
        std::cout << "No customers found matching the criteria.\n";
    } else {
        for (const auto& customer : results) {
            customer->displayCustomer();
        }
    }
}

void handleAddCustomer(RentalCompany& company) {
    int customerID;
    std::string name;

    std::cout << "Enter Customer ID: ";
    std::cin >> customerID;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    std::cout << "Enter Customer Name: ";
    std::getline(std::cin, name);

    try {
        company.addCustomer(Customer(customerID, name));
        std::cout << "Customer added successfully.\n\n";
    }
    catch (const std::exception& e) {
        std::cout << "Failed to add customer: " << e.what() << "\n\n";
    }
}

void handleAddVehicle(RentalCompany& company) {
    int vehicleType;
    std::cout << "Select Vehicle Type:\n";
    std::cout << "1. Car\n";
    std::cout << "2. Van\n";
    std::cout << "3. Minibus\n";
    std::cout << "4. SUV\n";
    std::cout << "Enter your choice: ";
    std::cin >> vehicleType;

    std::string id, make, model;
    int passengers, storage;
    bool avail;

    std::cout << "Enter Vehicle ID: ";
    std::cin >> id;
    std::cout << "Enter Make: ";
    std::cin >> make;
    std::cout << "Enter Model: ";
    std::cin >> model;
    std::cout << "Enter Passenger Capacity: ";
    std::cin >> passengers;
    std::cout << "Enter Storage Capacity: ";
    std::cin >> storage;
    std::cout << "Is the vehicle available? (1 for Yes, 0 for No): ";
    std::cin >> avail;

    switch (vehicleType) {
        case 1: {
            auto car = std::make_shared<Car>(id, make, model, passengers, storage, avail);
            company.addVehicle(car);
            break;
        }
        case 2: {
            auto van = std::make_shared<Van>(id, make, model, passengers, storage, avail);
            company.addVehicle(van);
            break;
        }
        case 3: {
            auto minibus = std::make_shared<Minibus>(id, make, model, passengers, storage, avail);
            company.addVehicle(minibus);
            break;
        }
        case 4: {
            auto suv = std::make_shared<SUV>(id, make, model, passengers, storage, avail);
            company.addVehicle(suv);
            break;
        }
        default:
            std::cout << "Invalid vehicle type.\n";
            break;
    }
}
