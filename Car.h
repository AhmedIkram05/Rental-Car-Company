// Car.h
#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car : public Vehicle {
public:
    // Constructors
    Car(const std::string& id, const std::string& mk, const std::string& mdl,
        int passengers, int storage, bool avail);

    // Destructor
    ~Car();

    // Override displayVehicle
    void displayVehicle() const override;
};

#endif // CAR_H
