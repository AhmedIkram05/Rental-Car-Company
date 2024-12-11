// Minibus.h
#ifndef MINIBUS_H
#define MINIBUS_H

#include "Vehicle.h"

// The `Minibus` class is derived from the `Vehicle` class and represents a minibus.
class Minibus : public Vehicle {
public:
    /**
     * @brief Construct a new Minibus object
     *
     * @param id The unique identifier for the minibus
     * @param mk The make of the minibus
     * @param mdl The model of the minibus
     * @param passengers The number of passengers the minibus can carry
     * @param storage The storage capacity of the minibus
     * @param avail The availability status of the minibus
     */
    Minibus(const std::string& id, const std::string& mk, const std::string& mdl,
            int passengers, int storage, bool avail);

    /**
     * @brief Destroy the Minibus object
     */
    ~Minibus() override = default;

    /**
     * @brief Get the base rental rate for the minibus
     *
     * @return double The base rental rate for the minibus
     */
    double getBaseRentalRate() const override;

    /**
     * @brief Convert minibus information to a row of strings for display
     *
     * @return std::vector<std::string> A vector of strings representing the minibus information
     */
    std::vector<std::string> toRow() const override {
        auto row = Vehicle::toRow();
        row.insert(row.begin(), "Minibus"); // Adding Type column
        return row;
    }

    /**
     * @brief Get the type of the vehicle
     *
     * @return std::string The type of the vehicle (Minibus)
     */
    std::string getType() const override { return "Minibus"; }
};

#endif // MINIBUS_H