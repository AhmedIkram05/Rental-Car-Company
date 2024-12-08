// Van.h
#ifndef VAN_H
#define VAN_H

#include "Vehicle.h"

class Van : public Vehicle {
public:
    // Constructors
    Van(const std::string& id, const std::string& mk, const std::string& mdl,
        int passengers, int storage, bool avail);
    
    // Destructor
    ~Van();
    
    // Override displayVehicle
    void displayVehicle() const override;
};

#endif // VAN_H
