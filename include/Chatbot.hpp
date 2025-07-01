#ifndef CHATBOT_HPP
#define CHATBOT_HPP

#include "FAQManager.hpp"
#include "RiskAnalyzer.hpp"

class Chatbot
{
private:
    FAQManager faqManager;
    RiskAnalyzer riskAnalyzer;

    void greetUser() const;
    void handleUserInput(const std::string &input);

public:
    Chatbot(const std::string &faqFile);
    void start();
};

#endif
