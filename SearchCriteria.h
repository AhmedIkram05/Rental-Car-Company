// SearchCriteria.h
#ifndef SEARCHCRITERIA_H
#define SEARCHCRITERIA_H

#include <string>

struct SearchCriteria {
    std::string type;
    std::string make;
    std::string model;
    size_t maxDistanceMake;
    size_t maxDistanceModel;  // Add separate maxDistance for model
    int passengerCapacity;
    int storageCapacity;
    bool filterByAvailability;
    bool availability;

    // Default Constructor
    SearchCriteria()
        : type(""), make(""), model(""),
          maxDistanceMake(2), maxDistanceModel(0),  // Set model maxDistance to 0 for exact match
          passengerCapacity(-1), storageCapacity(-1),
          filterByAvailability(false), availability(false) {}
};

struct CustomerSearchCriteria {
    int customerID;
    std::string name;
    size_t maxDistance;  // Changed from int to size_t

    // Default Constructor
    CustomerSearchCriteria()
        : customerID(-1), name(""), maxDistance(2) {}
};

#endif // SEARCHCRITERIA_H
