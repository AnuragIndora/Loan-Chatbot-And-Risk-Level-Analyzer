#include "Utils.hpp"
#include <algorithm>
#include <cctype>
#include <regex>
#include <fstream>
#include <unordered_map>

namespace Utils
{

    std::string toLower(const std::string &str)
    {
        std::string lower = str;
        std::transform(lower.begin(), lower.end(), lower.begin(),
                       [](unsigned char c)
                       { return std::tolower(c); });
        return lower;
    }

    std::string normalizeInput(const std::string &str)
    {
        std::string trimmed = std::regex_replace(str, std::regex("^ +| +$|( ) +"), "$1");
        return toLower(trimmed);
    }

    std::string applySynonymNormalization(const std::string &input)
    {
        std::unordered_map<std::string, std::string> synonymMap = {
            // General inquiry phrases
            {"tell me about", "what is"},
            {"explain", "what is"},
            {"meaning", "what is"},
            {"define", "what is"},
            {"details about", "what is"},
            {"info on", "what is"},
            {"information on", "what is"},
            {"describe", "what is"},
            {"can you explain", "what is"},
            {"i want to know about", "what is"},
            {"give me details about", "what is"},
            {"what is the", "what is a"},

            // Actionable queries
            {"how do i apply for", "how to apply for"},
            {"how can i get", "how to get"},
            {"steps to get", "how to get"},
            {"ways to get", "how to get"},
            {"process of", "how to get"},
            {"procedure for", "how to get"},

            // EMI-related variations
            {"monthly payment", "emi"},
            {"installment", "emi"},
            {"monthly installment", "emi"},

            // Tenure-related variations
            {"loan duration", "tenure"},
            {"repayment period", "tenure"},
            {"loan period", "tenure"},

            // Interest-related
            {"rate of interest", "interest rate"},
            {"loan interest", "interest rate"},

            // Credit score
            {"cibil score", "credit score"},
            {"credit rating", "credit score"},

            // Default
            {"can't pay", "loan default"},
            {"missed payments", "loan default"},
            {"loan failure", "loan default"},

            // Prepayment
            {"early payment", "prepayment"},
            {"partial payment", "prepayment"},

            // Foreclosure
            {"close loan early", "foreclosure"},
            {"pay off loan early", "foreclosure"}};

        std::string normalized = toLower(input);
        for (const auto &[synonym, replacement] : synonymMap)
        {
            std::regex pattern("\\b" + synonym + "\\b");
            normalized = std::regex_replace(normalized, pattern, replacement);
        }

        return normalized;
    }

    void logQuestion(const std::string &userInput)
    {
        std::ofstream log("chatlog.txt", std::ios::app);
        if (log.is_open())
        {
            log << userInput << "\n";
            log.close();
        }
    }
}