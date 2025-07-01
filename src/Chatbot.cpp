#include "Chatbot.hpp"
#include "Utils.hpp"
#include "FAQManager.hpp"
#include <iostream>
#include <ctime>

Chatbot::Chatbot(const std::string &faqFile) : faqManager(faqFile)
{
    if (!faqManager.loadFAQs())
    {
        std::cerr << "Could not load FAQs from file.\n";
        exit(1);
    }
}

void Chatbot::greetUser() const
{
    time_t now = time(0);
    int hour = localtime(&now)->tm_hour;
    if (hour < 12)
        std::cout << "Good Morning!\n";
    else if (hour < 17)
        std::cout << "Good Afternoon!\n";
    else if (hour < 21)
        std::cout << "Good Evening!\n";
    else
        std::cout << "Good Night!\n";
    std::cout << "Welcome to the Loan Chatbot!\n";
}

void Chatbot::start()
{
    greetUser();
    while (true)
    {
        std::cout << "\nAsk a question ('exit', 'add', 'calculate risk', 'csv risk'): ";
        std::string input;
        std::getline(std::cin, input);
        Utils::logQuestion(input);

        std::string normalized = Utils::normalizeInput(Utils::applySynonymNormalization(input));

        if (normalized == "exit")
        {
            std::cout << "Thank you. Goodbye!\n";
            break;
        }
        else if (normalized == "add")
        {
            std::string q, a;
            std::cout << "Enter question: ";
            std::getline(std::cin, q);
            std::cout << "Enter answer: ";
            std::getline(std::cin, a);
            faqManager.addFAQ(q, a);
            std::cout << "Added successfully.\n";
        }
        else if (normalized == "calculate risk")
        {
            int missed;
            double loan, collat, interest;
            std::cout << "Missed payments: ";
            std::cin >> missed;
            std::cout << "Loan amount: ";
            std::cin >> loan;
            std::cout << "Collateral: ";
            std::cin >> collat;
            std::cout << "Interest rate: ";
            std::cin >> interest;
            std::cin.ignore();
            std::cout << "Risk Level: " << riskAnalyzer.calculateRiskLevel(missed, loan, collat, interest) << "\n";
        }
        else if (normalized == "csv risk")
        {
            std::string inFile, outFile;
            std::cout << "Input CSV path: ";
            std::getline(std::cin, inFile);
            std::cout << "Output CSV path: ";
            std::getline(std::cin, outFile);
            riskAnalyzer.classifyRiskFromCSV(inFile, outFile);
        }
        else
        {
            std::string answer = faqManager.searchExact(normalized);
            if (!answer.empty())
            {
                std::cout << answer << "\n";
                continue;
            }

            auto matches = faqManager.extractMatchingFAQs(normalized);
            if (!matches.empty())
            {
                for (const auto &q : matches)
                    std::cout << "- " << q << ": " << faqManager.getFAQs().at(q) << "\n";
            }
            else
            {
                std::cout << "Didn't find an answer. Try a keyword: ";
                std::string keyword;
                std::getline(std::cin, keyword);
                auto suggestions = faqManager.searchKeywords(keyword);
                if (!suggestions.empty())
                {
                    std::cout << "Here are some related questions: " << std::endl;
                    for (size_t i = 0; i < suggestions.size(); ++i)
                        std::cout << i + 1 << ". " << suggestions[i] << "\n";

                    std::cout << "Enter the number of question, or type the full question: " << std::endl;
                    std::string choice;
                    std::getline(std::cin, choice);

                    std::unordered_map<std::string, std::string> loanFAQs = faqManager.getFAQs();
                    bool answered = false;
                    try
                    {
                        size_t index = std::stoi(choice);
                        if (index >= 1 && index <= suggestions.size())
                        {
                            std::cout << loanFAQs[suggestions[index - 1]] << std::endl;
                            continue;
                        }
                    }
                    catch (...)
                    {
                        for (const auto &[q, a] : loanFAQs)
                        {
                            if (Utils::toLower(q) == Utils::toLower(choice))
                            {
                                std::cout << a << std::endl;
                                answered = true;
                                break;
                            }
                        }

                        if (!answered)
                        {
                            std::cout << "Sorry, I still couldn't find the answer." << std::endl;
                        }
                    }
                }
                else
                {
                    std::cout << "No matching questions found for keyword: " << keyword << std::endl;
                }
            }
        }
    }
}