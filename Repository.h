// Repository.h
#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <memory>
#include <algorithm>
#include "Customer.h"
#include "Vehicle.h"

// Generic Repository
template <typename T>
class Repository {
public:
    /**
     * @brief Add an item to the repository
     *
     * @param item The item to add
     */
    void add(const std::shared_ptr<T>& item) {
        items.push_back(item);
    }

    /**
     * @brief Remove an item from the repository
     *
     * @param item The item to remove
     */
    void remove(const std::shared_ptr<T>& item) {
        items.erase(std::remove(items.begin(), items.end(), item), items.end());
    }

    /**
     * @brief Find an item by its ID
     *
     * @param id The ID of the item to find
     * @return std::shared_ptr<T> The item with the specified ID, or nullptr if not found
     */
    std::shared_ptr<T> findById(const std::string& id) const {
        auto it = std::find_if(items.begin(), items.end(),
            [&id](const std::shared_ptr<T>& item) {
                return item->getVehicleID() == id;
            });
        return (it != items.end()) ? *it : nullptr;
    }

    /**
     * @brief Get all items in the repository
     *
     * @return const std::vector<std::shared_ptr<T>>& A vector of all items in the repository
     */
    const std::vector<std::shared_ptr<T>>& getAll() const {
        return items;
    }

    /**
     * @brief Clear all items from the repository
     */
    void clear() {
        items.clear();
    }

private:
    std::vector<std::shared_ptr<T>> items; // Vector to store items
};

// Specialization for Customer
template <>
class Repository<Customer> {
public:
    /**
     * @brief Add a customer to the repository
     *
     * @param item The customer to add
     */
    void add(const std::shared_ptr<Customer>& item) {
        items.push_back(item);
    }

    /**
     * @brief Remove a customer from the repository
     *
     * @param item The customer to remove
     */
    void remove(const std::shared_ptr<Customer>& item) {
        items.erase(std::remove(items.begin(), items.end(), item), items.end());
    }

    /**
     * @brief Find a customer by their ID
     *
     * @param id The ID of the customer to find
     * @return std::shared_ptr<Customer> The customer with the specified ID, or nullptr if not found
     */
    std::shared_ptr<Customer> findById(int id) const {
        auto it = std::find_if(items.begin(), items.end(),
            [&id](const std::shared_ptr<Customer>& item) {
                return item->getCustomerID() == id;
            });
        return (it != items.end()) ? *it : nullptr;
    }

    /**
     * @brief Get all customers in the repository
     *
     * @return const std::vector<std::shared_ptr<Customer>>& A vector of all customers in the repository
     */
    const std::vector<std::shared_ptr<Customer>>& getAll() const {
        return items;
    }

    /**
     * @brief Clear all customers from the repository
     */
    void clear() {
        items.clear();
    }

private:
    std::vector<std::shared_ptr<Customer>> items; // Vector to store customers
};

// Specialization for Vehicle
template <>
class Repository<Vehicle> {
public:
    /**
     * @brief Add a vehicle to the repository
     *
     * @param item The vehicle to add
     */
    void add(const std::shared_ptr<Vehicle>& item) {
        items.push_back(item);
    }

    /**
     * @brief Remove a vehicle from the repository
     *
     * @param item The vehicle to remove
     */
    void remove(const std::shared_ptr<Vehicle>& item) {
        items.erase(std::remove(items.begin(), items.end(), item), items.end());
    }

    /**
     * @brief Find a vehicle by its ID
     *
     * @param id The ID of the vehicle to find
     * @return std::shared_ptr<Vehicle> The vehicle with the specified ID, or nullptr if not found
     */
    std::shared_ptr<Vehicle> findById(const std::string& id) const {
        auto it = std::find_if(items.begin(), items.end(),
            [&id](const std::shared_ptr<Vehicle>& item) {
                return item->getVehicleID() == id;
            });
        return (it != items.end()) ? *it : nullptr;
    }

    /**
     * @brief Get all vehicles in the repository
     *
     * @return const std::vector<std::shared_ptr<Vehicle>>& A vector of all vehicles in the repository
     */
    const std::vector<std::shared_ptr<Vehicle>>& getAll() const {
        return items;
    }

    /**
     * @brief Clear all vehicles from the repository
     */
    void clear() {
        items.clear();
    }

private:
    std::vector<std::shared_ptr<Vehicle>> items; // Vector to store vehicles
};

#endif // REPOSITORY_H