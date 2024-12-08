// Repository.h
#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <memory>
#include <algorithm>
#include "Customer.h" // Include Customer class

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
        auto it = std::find_if(items.begin(), items.end(), [&id](const std::shared_ptr<T>& item) {
            return item->getVehicleID() == id;
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

    std::shared_ptr<Customer> findById(const std::string& id) const {
        int intId = std::stoi(id); // Convert string ID to integer
        auto it = std::find_if(items.begin(), items.end(),
            [intId](const std::shared_ptr<Customer>& item) {
                return item->getCustomerID() == intId;
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

#endif // REPOSITORY_H
