// Minibus.h
#ifndef MINIBUS_H
#define MINIBUS_H

#include "Vehicle.h"

class Minibus : public Vehicle {
public:
    // Constructors
    Minibus(const std::string& id, const std::string& mk, const std::string& mdl,
            int passengers, int storage, bool avail);
    
    // Destructor
    ~Minibus();
    
    // Override displayVehicle
    void displayVehicle() const override;
};

#endif // MINIBUS_H
