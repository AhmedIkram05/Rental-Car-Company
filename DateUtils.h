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
    // Adds days to a given date string in YYYY-MM-DD format
    static std::string addDays(const std::string& dateStr, int daysToAdd);

    // Gets the current date in YYYY-MM-DD format
    static std::string getCurrentDate();

    // Calculates the difference in days between two dates in YYYY-MM-DD format
    static int calculateDaysLate(const std::string& dueDate, const std::string& returnDate);

    // Validates if a date string is in YYYY-MM-DD format and is a valid date
    static bool isValidDate(const std::string& dateStr);

    // Calculates the difference in days between two dates in YYYY-MM-DD format
    static int daysDifference(const std::string& dueDateStr, const std::string& returnDateStr);

private:
    // Converts a date string in YYYY-MM-DD format to std::tm
    static std::tm stringToTm(const std::string& dateStr);
};

#endif // DATEUTILS_H
