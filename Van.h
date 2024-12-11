// Van.h
#ifndef VAN_H
#define VAN_H

#include "Vehicle.h"

// The `Van` class is derived from the `Vehicle` class and represents a van.
class Van : public Vehicle {
public:
    /**
     * @brief Construct a new Van object
     *
     * @param id The unique identifier for the van
     * @param mk The make of the van
     * @param mdl The model of the van
     * @param passengers The number of passengers the van can carry
     * @param storage The storage capacity of the van
     * @param avail The availability status of the van
     */
    Van(const std::string& id, const std::string& mk, const std::string& mdl,
        int passengers, int storage, bool avail);

    /**
     * @brief Destroy the Van object
     */
    ~Van() override = default;

    /**
     * @brief Get the base rental rate for the van
     *
     * @return double The base rental rate for the van
     */
    double getBaseRentalRate() const override;

    /**
     * @brief Convert van information to a row of strings for display
     *
     * @return std::vector<std::string> A vector of strings representing the van information
     */
    std::vector<std::string> toRow() const override {
        auto row = Vehicle::toRow();
        row.insert(row.begin(), "Van"); // Adding Type column
        return row;
    }

    /**
     * @brief Get the type of the vehicle
     *
     * @return std::string The type of the vehicle (Van)
     */
    std::string getType() const override { return "Van"; }
};

#endif // VAN_H