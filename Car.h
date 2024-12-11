// Car.h
#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

// The `Car` class is derived from the `Vehicle` class and represents a car.
class Car : public Vehicle {
public:
    /**
     * @brief Construct a new Car object
     *
     * @param id The unique identifier for the car
     * @param mk The make of the car
     * @param mdl The model of the car
     * @param passengers The number of passengers the car can carry
     * @param storage The storage capacity of the car
     * @param avail The availability status of the car
     */
    Car(const std::string& id, const std::string& mk, const std::string& mdl,
        int passengers, int storage, bool avail);

    /**
     * @brief Destroy the Car object
     */
    ~Car() override = default;

    /**
     * @brief Get the base rental rate for the car
     *
     * @return double The base rental rate for the car
     */
    double getBaseRentalRate() const override;

    /**
     * @brief Convert car information to a row of strings for display
     *
     * @return std::vector<std::string> A vector of strings representing the car information
     */
    std::vector<std::string> toRow() const override {
        auto row = Vehicle::toRow();
        row.insert(row.begin(), "Car"); // Adding Type column
        return row;
    }

    /**
     * @brief Get the type of the vehicle
     *
     * @return std::string The type of the vehicle (Car)
     */
    std::string getType() const override { return "Car"; }
};

#endif // CAR_H