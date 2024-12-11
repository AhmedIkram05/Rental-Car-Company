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
    ~Minibus() override = default;

    // Implement getBaseRentalRate
    double getBaseRentalRate() const override;

    // Override toRow
    std::vector<std::string> toRow() const override {
        auto row = Vehicle::toRow();
        row.insert(row.begin(), "Minibus"); // Adding Type column
        return row;
    }
};

#endif // MINIBUS_H
