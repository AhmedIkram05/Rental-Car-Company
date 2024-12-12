// SearchCriteria.h
#ifndef SEARCHCRITERIA_H
#define SEARCHCRITERIA_H

#include <string>

// The `SearchCriteria` struct defines the criteria for searching vehicles.
struct SearchCriteria {
    std::string type;              // Type of the vehicle
    std::string make;              // Make of the vehicle
    std::string model;             // Model of the vehicle
    size_t maxDistanceMake;        // Maximum Levenshtein distance for make
    size_t maxDistanceModel;       // Maximum Levenshtein distance for model
    int passengerCapacity;         // Minimum passenger capacity
    int storageCapacity;           // Minimum storage capacity
    bool filterByAvailability;     // Whether to filter by availability
    bool availability;             // Availability status

    // Default Constructor
    SearchCriteria()
        : type(""), make(""), model(""),
          maxDistanceMake(2), maxDistanceModel(0),  // Set model maxDistance to 0 for exact match
          passengerCapacity(-1), storageCapacity(-1),
          filterByAvailability(false), availability(false) {}
};

// The `CustomerSearchCriteria` struct defines the criteria for searching customers.
struct CustomerSearchCriteria {
    int customerID;                // Customer ID
    std::string name;              // Name of the customer
    size_t maxDistance;            // Maximum Levenshtein distance for name

    // Default Constructor
    CustomerSearchCriteria()
        : customerID(-1), name(""), maxDistance(2) {}
};

#endif // SEARCHCRITERIA_H