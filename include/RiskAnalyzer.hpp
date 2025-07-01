#ifndef RISKANALYZER_HPP
#define RISKANALYZER_HPP

#include <string>

class RiskAnalyzer
{
public:
    std::string calculateRiskLevel(int missedRepayments, double loanAmount, double collateralValue, double interestRate);
    void classifyRiskFromCSV(const std::string &inputFile, const std::string &outputFile = "output_with_risk.csv");
};

#endif
