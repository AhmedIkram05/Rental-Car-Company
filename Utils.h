// Utils.h
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include "Repository.h"

// Function declarations
inline void printSeparator(const std::vector<int>& widths);
inline void printHeader(const std::vector<std::string>& headers, const std::vector<int>& widths);

// Levenshtein Distance Algorithm
size_t levenshteinDistance(const std::string& s1, const std::string& s2);

// Helper function to truncate strings
inline std::string truncateString(const std::string& str, size_t maxWidth) {
    if (str.length() <= maxWidth)
        return str;
    if (maxWidth <= 3)
        return str.substr(0, maxWidth);
    return str.substr(0, maxWidth - 3) + "...";
}

// Template function to display items in a table format with dynamic sizing and overflow handling
template <typename T>
void displayItems(const std::vector<std::shared_ptr<T>>& items, const std::vector<std::string>& headers, const std::vector<int>& widths) {
    if (headers.size() != widths.size()) {
        throw std::runtime_error("Headers and widths size mismatch.");
    }

    // Print headers
    printHeader(headers, widths);

    // Print items
    for (const auto& item : items) {
        item->displayRow(widths);
    }
    printSeparator(widths);
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

// Function definitions
inline void printSeparator(const std::vector<int>& widths) {
    std::cout << "+";
    for (const auto& width : widths) {
        std::cout << std::string(static_cast<std::size_t>(width + 2), '-') << "+";
    }
    std::cout << std::endl;
}

inline void printHeader(const std::vector<std::string>& headers, const std::vector<int>& widths) {
    printSeparator(widths);
    std::cout << "|";
    for (size_t i = 0; i < headers.size(); ++i) {
        std::cout << " " << std::left << std::setw(widths[i]) << headers[i] << " |";
    }
    std::cout << std::endl;
    printSeparator(widths);
}

#endif // UTILS_H
