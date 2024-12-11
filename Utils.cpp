// Utils.cpp

#include "Utils.h"
#include <vector>
#include <string>
#include <regex>
#include <iostream>

/**
 * The function calculates the Levenshtein distance between two input strings using dynamic
 * programming.
 *
 * @param s1 The function `levenshteinDistance` you provided calculates the Levenshtein distance
 * between two strings `s1` and `s2`. The Levenshtein distance is a measure of the minimum number of
 * single-character edits (insertions, deletions, or substitutions) required to change
 * @param s2 It seems like you forgot to provide the second string `s2` for which you want to calculate
 * the Levenshtein distance from the first string `s1`. Please provide the second string `s2` so that I
 * can assist you further.
 *
 * @return The function `levenshteinDistance` returns the Levenshtein distance between two input
 * strings `s1` and `s2`. The Levenshtein distance is the minimum number of single-character edits
 * (insertions, deletions, or substitutions) required to change one string into the other.
 */
size_t levenshteinDistance(const std::string& s1, const std::string& s2) {
    const size_t m = s1.size();
    const size_t n = s2.size();
    std::vector<std::vector<size_t>> dp(m + 1, std::vector<size_t>(n + 1));

    for (size_t i = 0; i <= m; ++i) dp[i][0] = i;
    for (size_t j = 0; j <= n; ++j) dp[0][j] = j;

    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            size_t cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            dp[i][j] = std::min({ dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost });
        }
    }

    return dp[m][n];
}

/**
 * The isValidName function checks if a given string only contains alphabetic characters and spaces.
 *
 * @param name The `isValidName` function takes a `std::string` parameter named `name`, which
 * represents a name input. The function uses a regular expression to check if the name contains only
 * alphabetic characters (both uppercase and lowercase) and spaces. The function returns a boolean
 * value indicating whether the name is
 *
 * @return The function `isValidName` returns a boolean value indicating whether the input `name` is a
 * valid name or not. It uses a regular expression to check if the name contains only alphabetic
 * characters and spaces. If the name matches the regular expression pattern, the function returns
 * `true`, indicating that the name is valid. Otherwise, it returns `false`.
 */
bool isValidName(const std::string& name) {
    std::regex nameRegex("^[A-Za-z ]+$");
    return std::regex_match(name, nameRegex);
}

/**
 * The function isValidVehicleID checks if a given string is a valid vehicle ID starting with 'V'
 * followed by one or more digits.
 *
 * @param id The `id` parameter is a `std::string` representing a vehicle ID that needs to be
 * validated.
 *
 * @return The function `isValidVehicleID` returns a boolean value indicating whether the input `id`
 * matches the pattern specified by the regular expression `^V\d+$`.
 */
bool isValidVehicleID(const std::string& id) {
    std::regex vehicleIDRegex("^V\\d+$");
    return std::regex_match(id, vehicleIDRegex);
}

/**
 * The function checks if a given customer ID is valid within the range of 100 to 999.
 *
 * @param id The `id` parameter is an integer representing a customer ID. The `isValidCustomerID`
 * function checks if the customer ID is within the range of 100 to 999 (inclusive) and returns a
 * boolean value indicating whether the ID is valid or not.
 *
 * @return The function `isValidCustomerID` returns a boolean value, indicating whether the input `id`
 * is a valid customer ID. It returns `true` if the `id` is between 100 and 999 (inclusive), and
 * `false` otherwise.
 */
bool isValidCustomerID(int id) {
    return id >= 100 && id <= 999;
}

/**
 * The function `getValidatedMenuChoice` ensures the user inputs a valid menu choice within a specified
 * range.
 *
 * @param minOption The `minOption` parameter represents the minimum valid menu option that the user
 * can choose. This value is used to validate the user's input and ensure that it falls within the
 * specified range of menu options.
 * @param maxOption The `maxOption` parameter in the `getValidatedMenuChoice` function represents the
 * maximum valid option that a user can choose from the menu. This parameter is used to ensure that the
 * user's input is within the specified range of menu options.
 *
 * @return The function `getValidatedMenuChoice` returns an integer value representing the user's
 * validated menu choice within the specified range of `minOption` and `maxOption`.
 */
int getValidatedMenuChoice(int minOption, int maxOption) {
    int choice;
    std::cout << "Enter your choice: ";
    while (!(std::cin >> choice) || choice < minOption || choice > maxOption) {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << "Invalid choice. Please enter a number between "
                  << minOption << " and " << maxOption << ": ";
    }
    return choice;
}

/**
 * The above functions are used for trimming whitespace from a string and validating a model name in
 * C++.
 *
 * @param str The `trimWhitespace` function takes a `std::string` parameter named `str`, which
 * represents the input string that needs to be trimmed of leading and trailing whitespace characters.
 *
 * @return The `trimWhitespace` function returns a new string that is a trimmed version of the input
 * string `str`, with leading and trailing whitespace characters removed. The `isValidModelName`
 * function returns a boolean value indicating whether the input string `model` is not empty and has a
 * length less than or equal to 50.
 */
std::string trimWhitespace(const std::string& str) {
    const char* whitespace = " \t\n\r\f\v";
    std::size_t start = str.find_first_not_of(whitespace);
    std::size_t end = str.find_last_not_of(whitespace);
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}
bool isValidModelName(const std::string &model) {
  return !model.empty() && model.length() <= 50;
}
