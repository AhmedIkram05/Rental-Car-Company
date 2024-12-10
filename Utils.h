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
void displayItems(const std::vector<std::shared_ptr<T>>& items, const std::vector<std::string>& headers) {
    const size_t MAX_WIDTH = 20;

    // Calculate column widths based on headers
    std::vector<size_t> widths;
    for (const auto& header : headers) {
        widths.push_back(std::min(header.length(), MAX_WIDTH));
    }

    // Update widths based on content
    for (const auto& item : items) {
        std::vector<std::string> row = item->toRow();
        for (size_t i = 0; i < row.size() && i < widths.size(); ++i) {
            if (row[i].length() > widths[i]) {
                widths[i] = std::min(row[i].length(), MAX_WIDTH);
            }
        }
    }

    // Print header
    std::cout << "|";
    for (size_t i = 0; i < headers.size(); ++i) {
        std::cout << " " << std::setw(static_cast<int>(widths[i])) << std::left << headers[i] << " |";
    }
    std::cout << "\n|";
    for (size_t i = 0; i < headers.size(); ++i) {
        std::cout << std::string(widths[i] + 2, '-') << "|";
    }
    std::cout << "\n";

    // Print rows
    for (const auto& item : items) {
        std::vector<std::string> row = item->toRow();
        std::cout << "|";
        for (size_t i = 0; i < row.size() && i < widths.size(); ++i) {
            std::cout << " "
                      << std::setw(static_cast<int>(widths[i]))
                      << std::left
                      << truncateString(row[i], widths[i])
                      << " |";
        }
        std::cout << "\n";
    }

    // Print footer
    std::cout << std::string((headers.size() * (MAX_WIDTH + 3)), '=') << "\n";
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
