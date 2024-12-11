// SUV.h
#ifndef SUV_H
#define SUV_H

#include "Vehicle.h"

class SUV : public Vehicle {
public:
    // Constructors
    SUV(const std::string& id, const std::string& mk, const std::string& mdl,
        int passengers, int storage, bool avail);

    // Destructor
    ~SUV() override = default;

    // Implement getBaseRentalRate
    double getBaseRentalRate() const override;

    // Override toRow
    std::vector<std::string> toRow() const override {
        auto row = Vehicle::toRow();
        row.insert(row.begin(), "SUV"); // Adding Type column
        return row;
    }
};

#endif // SUV_H