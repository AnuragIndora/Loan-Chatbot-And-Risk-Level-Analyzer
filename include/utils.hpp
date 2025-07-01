#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

namespace Utils
{
    std::string toLower(const std::string &str);
    std::string normalizeInput(const std::string &str);
    std::string applySynonymNormalization(const std::string &input);
    void logQuestion(const std::string &userInput);
}

#endif
