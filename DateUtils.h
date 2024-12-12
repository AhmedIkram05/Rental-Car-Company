// DateUtils.h
#ifndef DATEUTILS_H
#define DATEUTILS_H

#include <string>
#include <ctime>
#include <stdexcept>
#include <sstream>
#include <iomanip>

class DateUtils {
public:
    /**
     * @brief Adds days to a given date string in YYYY-MM-DD format
     *
     * @param dateStr The date string in YYYY-MM-DD format
     * @param daysToAdd The number of days to add
     * @return std::string The new date string after adding the days
     */
    static std::string addDays(const std::string& dateStr, int daysToAdd);

    /**
     * @brief Gets the current date in YYYY-MM-DD format
     *
     * @return std::string The current date in YYYY-MM-DD format
     */
    static std::string getCurrentDate();

    /**
     * @brief Calculates the difference in days between two dates in YYYY-MM-DD format
     *
     * @param dueDate The due date in YYYY-MM-DD format
     * @param returnDate The return date in YYYY-MM-DD format
     * @return int The difference in days between the two dates
     */
    static int calculateDaysLate(const std::string& dueDate, const std::string& returnDate);

    /**
     * @brief Validates if a date string is in YYYY-MM-DD format and is a valid date
     *
     * @param dateStr The date string to validate
     * @return bool True if the date string is valid, false otherwise
     */
    static bool isValidDate(const std::string& dateStr);

    /**
     * @brief Calculates the difference in days between two dates in YYYY-MM-DD format
     *
     * @param dueDateStr The due date string in YYYY-MM-DD format
     * @param returnDateStr The return date string in YYYY-MM-DD format
     * @return int The difference in days between the two dates
     */
    static int daysDifference(const std::string& dueDateStr, const std::string& returnDateStr);

private:
    /**
     * @brief Converts a date string in YYYY-MM-DD format to std::tm
     *
     * @param dateStr The date string in YYYY-MM-DD format
     * @return std::tm The std::tm structure representing the date
     */
    static std::tm stringToTm(const std::string& dateStr);
};

#endif // DATEUTILS_H