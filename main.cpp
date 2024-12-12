/**
 * The main function in the C++ program manages a rental company system with menus for admin and
 * customer actions, including adding customers and vehicles, renting and returning vehicles, searching
 * for vehicles and customers, and running specific test scenarios.
 *
 * @return The main function in the provided code is returning an integer value of 0 at the end of the
 * program execution. This return statement `return 0;` signifies that the program has executed
 * successfully and is exiting with a status code of 0, indicating no errors occurred during the
 * program execution.
 */
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
#include <iomanip>
#include "Repository.h"

// Function declarations

// Display Menus
void displayMainMenu();
void displayAdminMenu();
void displayCustomerMenu();

// Input Handling
void runSpecificTests(RentalCompany& company);
void handleRentVehicle(RentalCompany& company);
void handleReturnVehicle(RentalCompany& company);
void handleDisplayAvailableVehicles(RentalCompany& company);
void handleDisplayCustomers(RentalCompany& company);
void handleSearchVehicles(RentalCompany& company);
void handleSearchCustomers(RentalCompany& company);
void displayVehicleSearchResults(const std::vector<std::shared_ptr<Vehicle>>& results);
void displayCustomerSearchResults(const std::vector<std::shared_ptr<Customer>>& results);
void handleAddCustomer(RentalCompany& company);
void handleAddVehicle(RentalCompany& company);
void handleDisplayAllVehicles(RentalCompany& company);
bool adminLogin();


/**
 * The main function of a rental company program that interacts with users through menus for admin,
 * customer, testing, and exiting functionalities.
 *
 * @return The `main` function is returning an integer value of 0, which is a common convention in C++
 * to indicate successful program execution.
 */
int main() {
    RentalCompany company;
    try {
        company.loadFromFile("mainVehicles.txt", "mainCustomers.txt");
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to load data: " << e.what() << "\n";
    }

    int mainChoice;
    bool exitProgram = false;

    while (!exitProgram) {
        displayMainMenu();
        mainChoice = getValidatedMenuChoice(1, 4);

        switch (mainChoice) {
            case 1: { // Admin Menu
                if (adminLogin()) { // Check login
                    int adminChoice;
                    bool backToMain = false;
                    while (!backToMain) {
                        displayAdminMenu();
                        std::cin >> adminChoice;

                        // Validate input
                        while (std::cin.fail() || adminChoice < 1 || adminChoice > 7) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Invalid input. Please enter a number between 1 and 7: ";
                            std::cin >> adminChoice;
                        }

                        switch (adminChoice) {
                            case 1:
                                handleAddCustomer(company);
                                company.saveToFile("mainVehicles.txt", "mainCustomers.txt");
                                break;
                            case 2:
                                handleAddVehicle(company);
                                company.saveToFile("mainVehicles.txt", "mainCustomers.txt");
                                break;
                            case 3:
                                handleDisplayAllVehicles(company);
                                break;
                            case 4:
                                handleDisplayCustomers(company);
                                break;
                            case 5:
                                handleSearchVehicles(company);
                                break;
                            case 6:
                                handleSearchCustomers(company);
                                break;
                            case 7:
                                backToMain = true;
                                break;
                            default:
                                std::cout << "Invalid choice. Please try again.\n";
                        }
                    }
                } else {
                    std::cout << "Access denied. Returning to Main Menu.\n";
                }
                break;
            }
            case 2: { // Customer Menu
                int customerChoice;
                bool backToMain = false;
                while (!backToMain) {
                    displayCustomerMenu();
                    std::cin >> customerChoice;

                    // Validate input
                    while (std::cin.fail() || customerChoice < 1 || customerChoice > 4) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter a number between 1 and 4: ";
                        std::cin >> customerChoice;
                    }

                    switch (customerChoice) {
                        case 1:
                            handleRentVehicle(company);
                            company.saveToFile("mainVehicles.txt", "mainCustomers.txt");
                            break;
                        case 2:
                            handleReturnVehicle(company);
                            company.saveToFile("mainVehicles.txt", "mainCustomers.txt");
                            break;
                        case 3:
                            handleDisplayAvailableVehicles(company);
                            break;
                        case 4:
                            backToMain = true;
                            break;
                        default:
                            std::cout << "Invalid choice. Please try again.\n";
                    }
                }
                break;
            }
            case 3: { // Run Tests
                runSpecificTests(company);
                break;
            }
            case 4: { // Exit
                std::cout << "Exiting the program. Goodbye!\n";
                exitProgram = true;
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

/**
 * The function `adminLogin` in C++ prompts the user for a username and password, allowing a maximum of
 * 3 login attempts with predefined credentials before denying access.
 *
 * @return The function `adminLogin()` returns a boolean value - `true` if the login is successful
 * (username and password match the predefined values), and `false` if the maximum number of login
 * attempts is exceeded without a successful login.
 */
bool adminLogin() {
    const std::string USERNAME = "0";
    const std::string PASSWORD = "0";
    std::string inputUsername;
    std::string inputPassword;
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;

    while (attempts < MAX_ATTEMPTS) {
        std::cout << "=== Admin Login ===\n";
        std::cout << "Username: ";
        std::cin >> inputUsername;
        std::cout << "Password: ";
        std::cin >> inputPassword;

        if (inputUsername == USERNAME && inputPassword == PASSWORD) {
            std::cout << "Login successful.\n";
            return true;
        } else {
            attempts++;
            std::cout << "Invalid credentials. Attempts remaining: " << (MAX_ATTEMPTS - attempts) << "\n\n";
        }
    }

    std::cout << "Maximum login attempts exceeded.\n";
    return false;
}

/**
 * The function `displayMainMenu` prints out the main menu options for a rental company program in C++.
 */
void displayMainMenu() {
    std::cout << "\n==============================\n";
    std::cout << "=== Rental Company Main Menu ===\n";
    std::cout << "==============================\n";
    std::cout << "1. Admin\n";
    std::cout << "2. Customers\n";
    std::cout << "3. Run Specific Tests\n";
    std::cout << "4. Exit\n";
    std::cout << "==============================\n";
    std::cout << "Enter your choice: ";
}


/**
 * The function `displayAdminMenu` prints out a menu for administrative tasks in a vehicle management
 * system.
 */
void displayAdminMenu() {
    std::cout << "\n========= Admin Menu =========\n";
    std::cout << "1. Add Customer\n";
    std::cout << "2. Add Vehicle\n";
    std::cout << "3. Display All Vehicles\n";
    std::cout << "4. Display All Customers\n";
    std::cout << "5. Search Vehicles\n";
    std::cout << "6. Search Customers\n";
    std::cout << "7. Back to Main Menu\n";
    std::cout << "=============================\n";
    std::cout << "Enter your choice: ";
}

/**
 * The function `displayCustomerMenu` prints out a menu for customer actions in a vehicle management
 * system.
 */
void displayCustomerMenu() {
    std::cout << "\n=== Customer Menu ===\n";
    std::cout << "1. Rent Vehicle\n";
    std::cout << "2. Return Vehicle\n";
    std::cout << "3. Display Available Vehicles\n";
    std::cout << "4. Back to Main Menu\n";
    std::cout << "Enter your choice: ";
}

/**
 * The function `handleRentVehicle` in C++ manages the process of renting a vehicle by a customer,
 * including input validation and error handling.
 *
 * @param company A reference to the `RentalCompany` object representing the rental company system.
 */
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
    try {
        auto car = std::make_shared<Car>("V108", "Vauxhall", "Corsa", 5, 300, true);
        company.addVehicle(car);
        std::cout << "Test 2 PASSED: Car V108 Vauxhall Corsa added successfully.\n\n";
    } catch (const std::exception& e) {
        std::cout << "Test 2 FAILED: " << e.what() << "\n\n";
    }

    // Test 3: Adding new Customer - Christina (ID:106)...
    std::cout << "Test 3: Adding new Customer - Christina (ID:106)...\n";
    try {
        auto customer = std::make_shared<Customer>(106, "Christina");
        company.addCustomer(customer);
        std::cout << "Test 3 PASSED: Customer Christina added successfully.\n\n";
    } catch (const std::exception& e) {
        std::cout << "Test 3 FAILED: " << e.what() << "\n\n";
    }

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
    auto results = company.searchVehicles(criteria);
    if (!results.empty()) {
        std::cout << "Test 6 PASSED: Audi Q8 found.\n\n";
        displayVehicleSearchResults(results);
    } else {
        std::cout << "Test 6 FAILED: Audi Q8 not found.\n\n";
    }

    // Test 7a: Adding new Car - V109 Toyota Corolla...
    std::cout << "Test 7a: Adding new Car - V109 Toyota Corolla...\n";
    try {
        auto car = std::make_shared<Car>("V109", "Toyota", "Corolla", 5, 400, true);
        company.addVehicle(car);
        std::cout << "Test 7a PASSED: Car V109 Toyota Corolla added successfully.\n\n";
    } catch (const std::exception& e) {
        std::cout << "Test 7a FAILED: " << e.what() << "\n\n";
    }

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

    // Reload main data after tests
    company.clearData();

    try {
        company.loadFromFile("mainVehicles.txt", "mainCustomers.txt");
        std::cout << "Main Data Reloaded Successfully.\n\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to reload main data: " << e.what() << "\n";
    }
    std::cout << "=== Specific Test Scenarios Completed ===\n\n";
}

void handleRentVehicle(RentalCompany& company) {
    int customerID;
    std::string vehicleID;

    std::cout << "Enter Customer ID: ";
    while (!(std::cin >> customerID) || !isValidCustomerID(customerID)) {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << "Invalid Customer ID. Please enter a 3-digit number (100-999): ";
    }

    std::cout << "Enter Vehicle ID to rent: ";
    std::cin >> vehicleID;
    while (!isValidVehicleID(vehicleID)) {
        std::cout << "Invalid Vehicle ID. Please enter an ID starting with 'V' followed by digits: ";
        std::cin >> vehicleID;
    }

    // Check if vehicle is available
    auto vehicle = company.getVehicleRepository().findById(vehicleID);
    if (!vehicle || !vehicle->getAvailability()) {
        std::cout << "Vehicle is not available for rent.\n";
        return;
    }

    try {
        company.rentVehicle(customerID, vehicleID);
        std::cout << "Vehicle rented successfully.\n";
        std::cout << "You must return the vehicle within 7 days.\n\n";
    } catch (const std::exception& e) {
        std::cout << "Rental Failed: " << e.what() << "\n\n";
    }
}


/**
 * The function `handleReturnVehicle` in C++ prompts the user to enter a customer ID, vehicle ID, and
 * return date, then attempts to return the vehicle in a rental company, displaying success or failure
 * messages accordingly.
 *
 * @param company The `company` parameter in the `handleReturnVehicle` function is of type
 * `RentalCompany&`, which means it is a reference to an object of the `RentalCompany` class. This
 * parameter is used to interact with the rental company object to return a vehicle based on the
 * provided customer
 */
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

/**
 * The function `handleDisplayAvailableVehicles` calls the `displayAvailableVehicles` method of a
 * `RentalCompany` object.
 *
 * @param company The parameter `company` is an object of type `RentalCompany`, which is being passed
 * by reference to the function `handleDisplayAvailableVehicles`.
 */
void handleDisplayAvailableVehicles(RentalCompany& company) {
    company.displayAvailableVehicles();
}

/**
 * The function `handleDisplayCustomers` calls the `displayCustomers` method of a `RentalCompany`
 * object.
 *
 * @param company The parameter `company` is an object of type `RentalCompany`, which is being passed
 * by reference to the function `handleDisplayCustomers`.
 */
void handleDisplayAllVehicles(RentalCompany& company) {
    std::cout << "=== All Vehicles ===\n";
    company.displayAllVehicles();
}

/**
 * The function `handleDisplayCustomers` calls the `displayCustomers` method of a `RentalCompany`
 * object.
 *
 * @param company The parameter `company` is an object of type `RentalCompany`, which is being passed
 * by reference to the function `handleDisplayCustomers`.
 */
void handleDisplayCustomers(RentalCompany& company) {
    company.displayCustomers();
}

/**
 * The function `handleAddCustomer` in C++ prompts the user to enter a customer ID and name, then
 * attempts to add a new customer to a rental company, displaying success or failure messages
 * accordingly.
 *
 * @param company The `company` parameter in the `handleAddCustomer` function is of type
 * `RentalCompany&`, which means it is a reference to an object of the `RentalCompany` class. This
 * parameter is used to interact with the rental company object to add a new customer based on the
 * provided customer ID and name.
 */
void handleSearchVehicles(RentalCompany& company) {
    SearchCriteria criteria;
    char choice;
    bool done = false;

    while (!done) {
        std::cout << "\n=== Vehicle Search Menu ===\n";
        std::cout << "1. Set Vehicle Type\n";
        std::cout << "2. Set Make\n";
        std::cout << "3. Set Model\n";
        std::cout << "4. Set Passenger Capacity\n";
        std::cout << "5. Set Storage Capacity\n";
        std::cout << "6. Set Availability\n";
        std::cout << "7. Exit Search\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                std::cout << "Enter Vehicle Type (Car, Van, Minibus, SUV): ";
                std::cin >> criteria.type;
                break;
            case '2':
                std::cout << "Enter Make: ";
                std::cin >> criteria.make;
                break;
            case '3':
                std::cout << "Enter Model: ";
                std::cin >> criteria.model;
                break;
            case '4':
                std::cout << "Enter Passenger Capacity: ";
                std::cin >> criteria.passengerCapacity;
                break;
            case '5':
                std::cout << "Enter Storage Capacity: ";
                std::cin >> criteria.storageCapacity;
                break;
            case '6':
                std::cout << "Filter by Availability (1 for Yes, 0 for No): ";
                std::cin >> criteria.filterByAvailability;
                if (criteria.filterByAvailability) {
                    std::cout << "Enter Availability (1 for Yes, 0 for No): ";
                    std::cin >> criteria.availability;
                }
                break;
            case '7':
                done = true;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }

        if (!done) {
            auto results = searchItems(company.getVehicleRepository(), [&criteria](const std::shared_ptr<Vehicle>& vehicle) {
                bool matches = true;
                if (!criteria.type.empty() && vehicle->getType() != criteria.type) matches = false;
                if (!criteria.make.empty() && levenshteinDistance(vehicle->getMake(), criteria.make) > criteria.maxDistanceMake) matches = false;
                if (!criteria.model.empty() && levenshteinDistance(vehicle->getModel(), criteria.model) > criteria.maxDistanceModel) matches = false;
                if (criteria.passengerCapacity != -1 && vehicle->getPassengers() != criteria.passengerCapacity) matches = false;
                if (criteria.storageCapacity != -1 && vehicle->getCapacity() != criteria.storageCapacity) matches = false;
                if (criteria.filterByAvailability && vehicle->getAvailability() != criteria.availability) matches = false;
                return matches;
            });
            displayVehicleSearchResults(results);
        }
    }
}

/**
 * The function `handleSearchCustomers` in C++ allows the user to search for customers based on
 * specific criteria such as customer ID and name, displaying the search results if any customers
 * match the criteria.
 *
 * @param company The `company` parameter in the `handleSearchCustomers` function is of type
 * `RentalCompany&`, which means it is a reference to an object of the `RentalCompany` class. This
 * parameter is used to interact with the rental company object to search for customers based on the
 * provided search criteria.
 */
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

/**
 * The function `displayVehicleSearchResults` in C++ displays the search results for vehicles based on
 * specific criteria, showing the vehicle type, ID, make, model, passengers, storage capacity,
 * availability, rental rate, and late fee for each vehicle.
 *
 * @param results The `results` parameter is a vector of shared pointers to `Vehicle` objects
 * containing the search results based on the search criteria provided by the user.
 */
void displayVehicleSearchResults(const std::vector<std::shared_ptr<Vehicle>>& results) {
    if (results.empty()) {
        std::cout << "No vehicles found matching the criteria.\n";
        return;
    }

    std::vector<std::string> headers = { "Type", "ID", "Make", "Model", "Passengers", "Storage Capacity", "Available", "Rental Rate £/day", "Late Fee £/day" };
    std::vector<int> widths = { 8, 10, 15, 15, 10, 16, 10, 18, 17 };

    displayItems(results, headers, widths);
}

/**
 * The function `displayCustomerSearchResults` in C++ displays the search results for customers based
 * on specific criteria, showing the customer ID, name, loyalty points, and rented vehicles for each
 * customer.
 *
 * @param results The `results` parameter is a vector of shared pointers to `Customer` objects
 * containing the search results based on the search criteria provided by the user.
 */
void displayCustomerSearchResults(const std::vector<std::shared_ptr<Customer>>& results) {
    if (results.empty()) {
        std::cout << "No customers found matching the criteria.\n";
        return;
    }

    std::vector<std::string> headers = { "ID", "Name", "Loyalty Points", "Rented Vehicles" };
    std::vector<int> widths = { 10, 20, 15, 30 };

    displayItems(results, headers, widths);
}

/**
 * The function `handleAddCustomer` in C++ prompts the user to enter a customer ID and name, then
 * attempts to add a new customer to a rental company, displaying success or failure messages
 * accordingly.
 *
 * @param company The `company` parameter in the `handleAddCustomer` function is of type
 * `RentalCompany&`, which means it is a reference to an object of the `RentalCompany` class. This
 * parameter is used to interact with the rental company object to add a new customer based on the
 * provided customer ID and name.
 */
void handleAddCustomer(RentalCompany& company) {
    int customerID;
    std::string name;

    // Input Customer ID
    std::cout << "Enter Customer ID (3-digit number): ";
    while (!(std::cin >> customerID) || !isValidCustomerID(customerID)) {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << "Invalid Customer ID. Please enter a 3-digit number (100-999): ";
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

    // Input Customer Name
    std::cout << "Enter Customer Name (letters and spaces only): ";
    std::getline(std::cin, name);
    while (!isValidName(name)) {
        std::cout << "Invalid name. Please enter letters and spaces only: ";
        std::getline(std::cin, name);
    }

    try {
        company.addCustomer(std::make_shared<Customer>(customerID, name));
        std::cout << "Customer added successfully.\n\n";
    }
    catch (const std::exception& e) {
        std::cout << "Failed to add customer: " << e.what() << "\n\n";
    }
}

/**
 * The function `handleAddVehicle` in C++ prompts the user to enter details for a new vehicle, including
 * the vehicle type, ID, make, model, passenger capacity, storage capacity, and availability, then
 * attempts to add the new vehicle to a rental company, displaying success or failure messages
 * accordingly.
 *
 * @param company The `company` parameter in the `handleAddVehicle` function is of type
 * `RentalCompany&`, which means it is a reference to an object of the `RentalCompany` class. This
 * parameter is used to interact with the rental company object to add a new vehicle based on the
 * provided vehicle details.
 */
void handleAddVehicle(RentalCompany& company) {
    int vehicleType;
    std::cout << "Select Vehicle Type:\n";
    std::cout << "1. Car\n";
    std::cout << "2. Van\n";
    std::cout << "3. Minibus\n";
    std::cout << "4. SUV\n";
    std::cout << "Enter your choice: ";
    while (!(std::cin >> vehicleType) || vehicleType < 1 || vehicleType > 4) {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << "Invalid choice. Please enter a number between 1 and 4: ";
    }

    std::string id, make, model;
    int passengers, storage;
    bool avail;

    // Input Vehicle ID
    std::cout << "Enter Vehicle ID (e.g., V101): ";
    std::cin >> id;
    while (!isValidVehicleID(id)) {
        std::cout << "Invalid Vehicle ID. Please enter an ID starting with 'V' followed by digits: ";
        std::cin >> id;
    }

    // Input Make
    std::cout << "Enter Make (letters and spaces only): ";
    std::cin.ignore();
    std::getline(std::cin, make);
    while (!isValidName(make)) {
        std::cout << "Invalid make. Please enter letters and spaces only: ";
        std::getline(std::cin, make);
    }

    // Input Model
    std::cout << "Enter Model (max 50 characters): ";
    std::getline(std::cin, model);
    while (!isValidModelName(model)) {
        std::cout << "Invalid model. Please enter a valid model name (up to 50 characters): ";
        std::getline(std::cin, model);
    }

    // Input Passenger Capacity
    std::cout << "Enter Passenger Capacity (positive integer): ";
    while (!(std::cin >> passengers) || passengers <= 0) {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << "Invalid capacity. Please enter a positive integer: ";
    }

    // Input Storage Capacity
    std::cout << "Enter Storage Capacity (positive integer): ";
    while (!(std::cin >> storage) || storage < 0) {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << "Invalid capacity. Please enter a non-negative integer: ";
    }

    // Input Availability
    std::cout << "Is the vehicle available? (1 for Yes, 0 for No): ";
    while (!(std::cin >> avail) || (avail != 0 && avail != 1)) {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << "Invalid input. Please enter 1 for Yes or 0 for No: ";
    }

    try {
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
                return;
        }
        std::cout << "Vehicle added successfully.\n\n";
    }
    catch (const std::exception& e) {
        std::cout << "Failed to add vehicle: " << e.what() << "\n\n";
    }
}
