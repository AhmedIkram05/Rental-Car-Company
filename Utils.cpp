// Utils.cpp

#include "Utils.h"
#include <vector>
#include <string>
#include <regex>
#include <iostream>

// Levenshtein Distance Algorithm
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

bool isValidName(const std::string& name) {
    std::regex nameRegex("^[A-Za-z ]+$");
    return std::regex_match(name, nameRegex);
}

bool isValidVehicleID(const std::string& id) {
    std::regex vehicleIDRegex("^V\\d+$");
    return std::regex_match(id, vehicleIDRegex);
}

bool isValidCustomerID(int id) {
    return id >= 100 && id <= 999;
}

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

std::string trimWhitespace(const std::string& str) {
    const char* whitespace = " \t\n\r\f\v";
    std::size_t start = str.find_first_not_of(whitespace);
    std::size_t end = str.find_last_not_of(whitespace);
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}
bool isValidModelName(const std::string &model) {
  return !model.empty() && model.length() <= 50;
}
