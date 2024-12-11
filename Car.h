// Car.h
#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car : public Vehicle {
public:
    // Constructor
    Car(const std::string& id, const std::string& mk, const std::string& mdl,
        int passengers, int storage, bool avail);

    // Default destructor
    ~Car() override = default;

    // Implement getBaseRentalRate
    double getBaseRentalRate() const override;

    // Override toRow
    std::vector<std::string> toRow() const override {
        auto row = Vehicle::toRow();
        row.insert(row.begin(), "Car"); // Adding Type column
        return row;
    }

    // Override getType
    std::string getType() const override { return "Car"; }
};

#endif // CAR_H
