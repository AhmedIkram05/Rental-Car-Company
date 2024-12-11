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

// Validation functions

/**
 * @brief Validate a name string
 *
 * @param name The name string to validate
 * @return bool True if the name is valid, false otherwise
 */
bool isValidName(const std::string& name);

/**
 * @brief Validate a vehicle ID string
 *
 * @param id The vehicle ID string to validate
 * @return bool True if the vehicle ID is valid, false otherwise
 */
bool isValidVehicleID(const std::string& id);

/**
 * @brief Validate a customer ID
 *
 * @param id The customer ID to validate
 * @return bool True if the customer ID is valid, false otherwise
 */
bool isValidCustomerID(int id);

/**
 * @brief Validate a model name string
 *
 * @param model The model name string to validate
 * @return bool True if the model name is valid, false otherwise
 */
bool isValidModelName(const std::string& model);

// Function declarations

/**
 * @brief Print a separator line for tables
 *
 * @param widths The widths of the columns
 */
inline void printSeparator(const std::vector<int>& widths);

/**
 * @brief Print table headers
 *
 * @param headers The headers of the table
 * @param widths The widths of the columns
 */
inline void printHeader(const std::vector<std::string>& headers, const std::vector<int>& widths);

// Levenshtein Distance Algorithm

/**
 * @brief Calculate the Levenshtein distance between two strings
 *
 * @param s1 The first string
 * @param s2 The second string
 * @return size_t The Levenshtein distance between the two strings
 */
size_t levenshteinDistance(const std::string& s1, const std::string& s2);

// Helper function to truncate strings

/**
 * @brief Truncate a string to fit within a specified width
 *
 * @param str The string to truncate
 * @param maxWidth The maximum width of the truncated string
 * @return std::string The truncated string
 */
inline std::string truncateString(const std::string& str, size_t maxWidth) {
    if (str.length() <= maxWidth)
        return str;
    if (maxWidth <= 3)
        return str.substr(0, maxWidth);
    return str.substr(0, maxWidth - 3) + "...";
}

// Template function to display items in a table format with dynamic sizing and overflow handling

/**
 * @brief Display items in a table format with dynamic sizing and overflow handling
 *
 * @tparam T The type of the items
 * @param items The items to display
 * @param headers The headers of the table
 * @param widths The widths of the columns
 */
template <typename T>
void displayItems(const std::vector<std::shared_ptr<T>>& items, const std::vector<std::string>& headers, const std::vector<int>& widths) {
    if (headers.size() != widths.size()) {
        throw std::runtime_error("Headers and widths size mismatch.");
    }

    // Print headers
    printHeader(headers, widths);

    // Print items
    for (const auto& item : items) {
        const auto row = item->toRow();
        std::cout << "|";
        for (size_t i = 0; i < row.size(); ++i) {
            if (i == 7 || i == 8) { // Assuming rental rate and late fee are at index 7 and 8
                std::cout << " " << std::left << std::setw(widths[i]) << std::fixed << std::setprecision(2) << std::stod(row[i]) << " |";
            } else {
                std::cout << " " << std::left << std::setw(widths[i]) << truncateString(row[i], static_cast<size_t>(widths[i])) << " |";
            }
        }
        std::cout << std::endl;
    }
    printSeparator(widths);
}

// Template for searching item by ID

/**
 * @brief Search for an item by its ID
 *
 * @tparam T The type of the item
 * @tparam IDType The type of the ID
 * @param repository The repository to search in
 * @param id The ID of the item to search for
 * @return std::shared_ptr<T> The item with the specified ID
 */
template <typename T, typename IDType>
std::shared_ptr<T> searchItemById(const Repository<T>& repository, const IDType& id) {
    return repository.findById(id);
}

// Template for adding item

/**
 * @brief Add an item to the repository
 *
 * @tparam T The type of the item
 * @param repository The repository to add the item to
 * @param item The item to add
 */
template <typename T>
void addItem(Repository<T>& repository, const std::shared_ptr<T>& item) {
    repository.add(item);
}

// Template for removing item

/**
 * @brief Remove an item from the repository
 *
 * @tparam T The type of the item
 * @param repository The repository to remove the item from
 * @param item The item to remove
 */
template <typename T>
void removeItem(Repository<T>& repository, const std::shared_ptr<T>& item) {
    repository.remove(item);
}

// Template for sorting items by a specific attribute

/**
 * @brief Sort items by a specific attribute
 *
 * @tparam T The type of the items
 * @tparam Compare The comparison function
 * @param items The items to sort
 * @param comp The comparison function to use for sorting
 */
template <typename T, typename Compare>
void sortItems(std::vector<std::shared_ptr<T>>& items, Compare comp) {
    std::sort(items.begin(), items.end(), comp);
}

// Template for searching items by criteria

/**
 * @brief Search for items by criteria
 *
 * @tparam T The type of the items
 * @tparam Criteria The criteria function
 * @param repository The repository to search in
 * @param criteria The criteria function to use for searching
 * @return std::vector<std::shared_ptr<T>> A vector of items matching the criteria
 */
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

/**
 * @brief Print a separator line for tables
 *
 * @param widths The widths of the columns
 */
inline void printSeparator(const std::vector<int>& widths) {
    std::cout << "+";
    for (const auto& width : widths) {
        std::cout << std::string(static_cast<std::size_t>(width + 2), '-') << "+";
    }
    std::cout << std::endl;
}

/**
 * @brief Print table headers
 *
 * @param headers The headers of the table
 * @param widths The widths of the columns
 */
inline void printHeader(const std::vector<std::string>& headers, const std::vector<int>& widths) {
    printSeparator(widths);
    std::cout << "|";
    for (size_t i = 0; i < headers.size(); ++i) {
        std::cout << " " << std::left << std::setw(widths[i]) << headers[i] << " |";
    }
    std::cout << std::endl;
    printSeparator(widths);
}

/**
 * @brief Get a validated menu choice from the user
 *
 * @param minOption The minimum valid option
 * @param maxOption The maximum valid option
 * @return int The validated menu choice
 */
int getValidatedMenuChoice(int minOption, int maxOption);

#endif // UTILS_H
