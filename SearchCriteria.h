// SearchCriteria.h
#ifndef SEARCHCRITERIA_H
#define SEARCHCRITERIA_H

#include <string>

struct SearchCriteria {
    std::string make;
    std::string model;
    int maxDistance;
    int passengerCapacity;
    int storageCapacity;
    bool filterByAvailability;
    bool availability;

    // Default Constructor
    SearchCriteria()
        : make(""), model(""), maxDistance(2), // Set a sensible default value
          passengerCapacity(-1), storageCapacity(-1),
          filterByAvailability(false), availability(false) {}
};

struct CustomerSearchCriteria {
    int customerID;
    std::string name;
    int maxDistance;

    // Default Constructor
    CustomerSearchCriteria()
        : customerID(-1), name(""), maxDistance(2) {} // Set a sensible default value
};

#endif // SEARCHCRITERIA_H
