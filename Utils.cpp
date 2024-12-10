// Utils.cpp

#include "Utils.h"
#include <vector>

// Levenshtein Distance Algorithm
size_t levenshteinDistance(const std::string& s1, const std::string& s2) {
    const size_t len1 = s1.size(), len2 = s2.size();
    std::vector<std::vector<size_t>> d(len1 + 1, std::vector<size_t>(len2 + 1));

    for (size_t i = 0; i <= len1; ++i)
        d[i][0] = i;
    for (size_t j = 0; j <= len2; ++j)
        d[0][j] = j;
    for (size_t i = 1; i <= len1; ++i)
        for (size_t j = 1; j <= len2; ++j)
            d[i][j] = std::min({ d[i - 1][j] + 1,
                                 d[i][j - 1] + 1,
                                 d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });
    return d[len1][len2];
}
