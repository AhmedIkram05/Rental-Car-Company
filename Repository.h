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
    void add(const std::shared_ptr<T>& item) {
        items.push_back(item);
    }

    void remove(const std::shared_ptr<T>& item) {
        items.erase(std::remove(items.begin(), items.end(), item), items.end());
    }

    std::shared_ptr<T> findById(const std::string& id) const {
        auto it = std::find_if(items.begin(), items.end(),
            [&id](const std::shared_ptr<T>& item) {
                return item->getID() == id;
            });
        return (it != items.end()) ? *it : nullptr;
    }

    const std::vector<std::shared_ptr<T>>& getAll() const {
        return items;
    }

    void clear() {
        items.clear();
    }

private:
    std::vector<std::shared_ptr<T>> items;
};

// Specialization for Customer
template <>
class Repository<Customer> {
public:
    void add(const std::shared_ptr<Customer>& item) {
        items.push_back(item);
    }

    void remove(const std::shared_ptr<Customer>& item) {
        items.erase(std::remove(items.begin(), items.end(), item), items.end());
    }

    std::shared_ptr<Customer> findById(int id) const {
        auto it = std::find_if(items.begin(), items.end(),
            [&id](const std::shared_ptr<Customer>& item) {
                return item->getCustomerID() == id;
            });
        return (it != items.end()) ? *it : nullptr;
    }

    const std::vector<std::shared_ptr<Customer>>& getAll() const {
        return items;
    }

    void clear() {
        items.clear();
    }

private:
    std::vector<std::shared_ptr<Customer>> items;
};

// Specialization for Vehicle
template <>
class Repository<Vehicle> {
public:
    void add(const std::shared_ptr<Vehicle>& item) {
        items.push_back(item);
    }

    void remove(const std::shared_ptr<Vehicle>& item) {
        items.erase(std::remove(items.begin(), items.end(), item), items.end());
    }

    std::shared_ptr<Vehicle> findById(const std::string& id) const {
        auto it = std::find_if(items.begin(), items.end(),
            [&id](const std::shared_ptr<Vehicle>& item) {
                return item->getVehicleID() == id;
            });
        return (it != items.end()) ? *it : nullptr;
    }

    const std::vector<std::shared_ptr<Vehicle>>& getAll() const {
        return items;
    }

    void clear() {
        items.clear();
    }

private:
    std::vector<std::shared_ptr<Vehicle>> items;
};

#endif // REPOSITORY_H
