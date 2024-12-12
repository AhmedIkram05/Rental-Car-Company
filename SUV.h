// SUV.h
#ifndef SUV_H
#define SUV_H

#include "Vehicle.h"

// The `SUV` class is derived from the `Vehicle` class and represents an SUV.
class SUV : public Vehicle {
public:
    /**
     * @brief Construct a new SUV object
     *
     * @param id The unique identifier for the SUV
     * @param mk The make of the SUV
     * @param mdl The model of the SUV
     * @param passengers The number of passengers the SUV can carry
     * @param storage The storage capacity of the SUV
     * @param avail The availability status of the SUV
     */
    SUV(const std::string& id, const std::string& mk, const std::string& mdl,
        int passengers, int storage, bool avail);

    /**
     * @brief Destroy the SUV object
     */
    ~SUV() override = default;

    /**
     * @brief Get the base rental rate for the SUV
     *
     * @return double The base rental rate for the SUV
     */
    double getBaseRentalRate() const override;

    /**
     * @brief Convert SUV information to a row of strings for display
     *
     * @return std::vector<std::string> A vector of strings representing the SUV information
     */
    std::vector<std::string> toRow() const override {
        auto row = Vehicle::toRow();
        row.insert(row.begin(), "SUV"); // Adding Type column
        return row;
    }

    /**
     * @brief Get the type of the vehicle
     *
     * @return std::string The type of the vehicle (SUV)
     */
    std::string getType() const override { return "SUV"; }
};

#endif // SUV_H