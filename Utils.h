// Utils.h
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <iostream>
#include "Repository.h"
#include "Vehicle.h"
#include "Customer.h"

// Template for displaying items
template <typename T>
void displayItems(const std::vector<std::shared_ptr<T>>& items) {
    for (const auto& item : items) {
        if constexpr (std::is_base_of<Vehicle, T>::value) {
            item->displayVehicle();
        } else if constexpr (std::is_same<T, Customer>::value) {
            item->displayCustomer();
        }
    }
}

// Template for searching item by ID
template <typename T, typename IDType>
std::shared_ptr<T> searchItemById(const Repository<T>& repository, const IDType& id) {
    return repository.findById(id);
}

// Template for adding item
template <typename T>
void addItem(Repository<T>& repository, const std::shared_ptr<T>& item) {
    repository.add(item);
}

// Template for removing item
template <typename T>
void removeItem(Repository<T>& repository, const std::shared_ptr<T>& item) {
    repository.remove(item);
}

// Template for sorting items by a specific attribute
template <typename T, typename Compare>
void sortItems(std::vector<std::shared_ptr<T>>& items, Compare comp) {
    std::sort(items.begin(), items.end(), comp);
}

// Template for searching items by criteria
template <typename T, typename Criteria>
std::vector<std::shared_ptr<T>> searchItems(const Repository<T>& repository, Criteria criteria) {
    std::vector<std::shared_ptr<T>> results;
    for (const auto& item : repository.getAll()) {
        if (criteria(item)) {
            results.push_back(item);
        }
    }
    return results;
}

#endif // UTILS_H
