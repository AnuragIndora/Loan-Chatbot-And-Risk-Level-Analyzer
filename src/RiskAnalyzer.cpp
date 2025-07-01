#include "RiskAnalyzer.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

std::string RiskAnalyzer::calculateRiskLevel(int missed, double loanAmount, double collateral, double interest)
{
    if (collateral <= 0)
        return "INVALID (Collateral can't be zero and negative!)";
    double score = (missed * 2.0) + (loanAmount / collateral) + (interest / 2.0);

    if (score <= 15.0)
        return "LOW";
    else if (score <= 25.0)
        return "MEDIUM";
    else
        return "HIGH";
}

void RiskAnalyzer::classifyRiskFromCSV(const std::string &inputFile, const std::string &outputFile)
{
    std::ifstream in(inputFile);
    std::ofstream out(outputFile);

    if (!in.is_open() || !out.is_open())
    {
        std::cerr << "Failed to open input/output file.\n";
        return;
    }

    std::string header;
    std::getline(in, header);
    out << header << ",risk_score,risk_level\n";

    std::string line;
    while (std::getline(in, line))
    {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> values;

        while (std::getline(ss, token, ','))
            values.push_back(token);
        if (values.size() < 5)
            continue;

        int missed = std::stoi(values[1]);
        double loan = std::stod(values[2]);
        double collat = std::stod(values[3]);
        double interest = std::stod(values[4]);
        double score = (missed * 2.0) + (loan / collat) + (interest / 2.0);
        std::string level = calculateRiskLevel(missed, loan, collat, interest);

        out << line << "," << score << "," << level << "\n";
    }

    std::cout << "Risk levels written to: " << outputFile << "\n";
}
