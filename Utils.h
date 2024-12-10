// Utils.h
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "Repository.h"

// Levenshtein Distance Algorithm
size_t levenshteinDistance(const std::string& s1, const std::string& s2);

// Template function to display items in a table format
template <typename T>
void displayItems(const std::vector<std::shared_ptr<T>>& items, const std::vector<std::string>& headers, const std::vector<int>& widths) {
    if (headers.size() != widths.size()) {
        throw std::runtime_error("Headers and widths size mismatch.");
    }

    // Print headers
    std::cout << std::string(80, '=') << "\n";
    std::cout << "|";
    for (size_t i = 0; i < headers.size(); ++i) {
        std::cout << " " << std::setw(widths[i]) << headers[i] << " |";
    }
    std::cout << "\n" << std::string(80, '=') << "\n";

    // Print items
    for (const auto& item : items) {
        std::cout << "|";
        item->displayRow(widths);
        std::cout << "\n";
    }
    std::cout << std::string(80, '=') << "\n";
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
