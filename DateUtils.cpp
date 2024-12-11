// DateUtils.cpp
#include "DateUtils.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cmath>

/**
 * @brief Adds days to a given date string in YYYY-MM-DD format
 *
 * @param date The date string in YYYY-MM-DD format
 * @param days The number of days to add
 * @return std::string The new date string after adding the days
 */
std::string DateUtils::addDays(const std::string& date, int days) {
    std::tm tm = {};
    std::istringstream iss(date);
    iss >> std::get_time(&tm, "%Y-%m-%d");
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    tp += std::chrono::hours(24 * days);
    std::time_t new_time = std::chrono::system_clock::to_time_t(tp);
    std::tm new_tm = *std::localtime(&new_time);
    std::ostringstream oss;
    oss << std::put_time(&new_tm, "%Y-%m-%d");
    return oss.str();
}

/**
 * @brief Validates if a date string is in YYYY-MM-DD format and is a valid date
 *
 * @param dateStr The date string to validate
 * @return bool True if the date string is valid, false otherwise
 */
bool DateUtils::isValidDate(const std::string& dateStr) {
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    if (ss.fail()) return false;
    return true;
}

/**
 * @brief Gets the current date in YYYY-MM-DD format
 *
 * @return std::string The current date in YYYY-MM-DD format
 */
std::string DateUtils::getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_c);
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d");
    return oss.str();
}

/**
 * @brief Calculates the difference in days between two dates in YYYY-MM-DD format
 *
 * @param dueDateStr The due date string in YYYY-MM-DD format
 * @param returnDateStr The return date string in YYYY-MM-DD format
 * @return int The difference in days between the two dates
 */
int DateUtils::daysDifference(const std::string& dueDateStr, const std::string& returnDateStr) {
    std::tm dueTm = stringToTm(dueDateStr);
    std::tm returnTm = stringToTm(returnDateStr);

    std::time_t dueTime = std::mktime(&dueTm);
    std::time_t returnTime = std::mktime(&returnTm);

    if (dueTime == -1 || returnTime == -1) {
        throw std::runtime_error("Invalid dates provided.");
    }

    double difference = std::difftime(returnTime, dueTime) / (60 * 60 * 24);
    return static_cast<int>(std::floor(difference));
}

/**
 * @brief Converts a date string in YYYY-MM-DD format to std::tm
 *
 * @param dateStr The date string in YYYY-MM-DD format
 * @return std::tm The std::tm structure representing the date
 */
std::tm DateUtils::stringToTm(const std::string& dateStr) {
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    if (ss.fail()) {
        throw std::runtime_error("Failed to parse date: " + dateStr);
    }
    return tm;
}

/**
 * @brief Calculates the difference in days between two dates in YYYY-MM-DD format
 *
 * @param dueDate The due date string in YYYY-MM-DD format
 * @param returnDate The return date string in YYYY-MM-DD format
 * @return int The difference in days between the two dates
 */
int DateUtils::calculateDaysLate(const std::string& dueDate, const std::string& returnDate) {
    std::tm due_tm = {};
    std::tm return_tm = {};
    std::istringstream iss_due(dueDate);
    std::istringstream iss_return(returnDate);
    iss_due >> std::get_time(&due_tm, "%Y-%m-%d");
    iss_return >> std::get_time(&return_tm, "%Y-%m-%d");
    auto due_tp = std::chrono::system_clock::from_time_t(std::mktime(&due_tm));
    auto return_tp = std::chrono::system_clock::from_time_t(std::mktime(&return_tm));
    auto duration = std::chrono::duration_cast<std::chrono::hours>(return_tp - due_tp).count();
    return static_cast<int>(duration / 24);
}