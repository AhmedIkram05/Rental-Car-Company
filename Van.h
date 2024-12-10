// Van.h
#ifndef VAN_H
#define VAN_H

#include "Vehicle.h"

class Van : public Vehicle {
public:
    // Constructor
    Van(const std::string& id, const std::string& mk, const std::string& mdl,
        int passengers, int storage, bool avail);

    // Default destructor
    ~Van() override = default;

    // Implement getBaseRentalRate
    double getBaseRentalRate() const override;

    // Override toRow
    std::vector<std::string> toRow() const override {
        auto row = Vehicle::toRow();
        row.insert(row.begin(), "Van"); // Adding Type column
        row.push_back(std::to_string(getBaseRentalRate()));
        row.push_back(std::to_string(getLateFee()));
        return row;
    }
};

#endif // VAN_H
