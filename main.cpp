#include "iostream"
#include "ctime"
#include "unordered_map"
#include "string"
#include "algorithm"
#include "vector"
#include "fstream"
#include "regex"
#include "set"

#define endl "\n"

// Convert to lowercase
std::string to_lower(const std::string &str)
{
    std::string lower_str = str;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), [](unsigned char c) { return std::tolower(c); });
    return lower_str;
}

// Normalize input: trim & collapse whitespace
std::string normalize_input(const std::string &str)
{
    std::string trimmed = std::regex_replace(str, std::regex("^ +| +$|( ) +"), "$1");
    return to_lower(trimmed);
}

// Replace synonyms with standard keywords
std::string apply_synonym_normalization(const std::string &input)
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
        {"pay off loan early", "foreclosure"}
    };


    std::string normalized = to_lower(input);
    for (const auto &[synonym, standard] : synonymMap)
    {
        std::regex pattern("\\b" + synonym + "\\b");
        normalized = std::regex_replace(normalized, pattern, standard);
    }

    return normalized;
}

// Search for keyword suggestions
std::vector<std::string> searchFAQs(const std::string &keyword, const std::unordered_map<std::string, std::string> &faqMap)
{
    std::vector<std::string> suggestions;
    std::string lower_query = to_lower(keyword);

    for (const auto &[question, _] : faqMap)
    {
        std::string lower_key = to_lower(question);
        if (lower_key.find(lower_query) != std::string::npos)
        {
            suggestions.push_back(question);
        }
    }

    return suggestions;
}

// Load FAQs from file
bool loadFAQsFromFile(const std::string &filename, std::unordered_map<std::string, std::string> &faqmap)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return false;

    std::string line;
    while (std::getline(file, line))
    {
        size_t seperator = line.find('|');
        if (seperator != std::string::npos)
        {
            std::string question = line.substr(0, seperator);
            std::string answer = line.substr(seperator + 1);
            faqmap[question] = answer;
        }
    }
    file.close();
    return true;
}

// Add new FAQ to file
void addFAQs(const std::string &filename, const std::string &question, const std::string &answer)
{
    std::ofstream file(filename, std::ios::app);
    if (file.is_open())
    {
        file << question << "|" << answer << "\n";
        file.close();
    }
}

// Log question to file
void log_question(const std::string &user_input)
{
    std::ofstream log("chatlog.txt", std::ios::app);
    if (log.is_open())
    {
        log << user_input << "\n";
        log.close();
    }
}

// Extract multiple FAQ keywords from input
std::vector<std::string> extract_all_keywords(const std::string &input, const std::unordered_map<std::string, std::string> &faqMap)
{
    std::vector<std::string> found;
    std::set<std::string> seen;

    for (const auto &[question, _] : faqMap)
    {
        std::string keyword = to_lower(question);
        std::regex word("\\b" + keyword + "\\b", std::regex_constants::icase);
        if (std::regex_search(input, word) && seen.find(keyword) == seen.end())
        {
            found.push_back(question);
            seen.insert(keyword);
        }
    }
    return found;
}

std::string calculateLoanRisk(int missed_repayments, double loan_amount, double collateral_value, double interest) {
    if (collateral_value <= 0) return "INVALID (Collateral can't be zero and negative!)";

    double risk_score = (missed_repayments * 2.0) + (loan_amount / collateral_value) + (interest / 2.0);
    
    if (risk_score <= 15.0)
        return "LOW";
    else if (risk_score > 15.0 && risk_score <= 25.0)
        return "MEDIUM";
    else
        return "HIGH";
}


void classifyRiskFromCSV(const std::string& inputFile, const std::string& outputFile = "output_with_risk.csv") {
    std::ifstream in(inputFile);
    std::ofstream out(outputFile);
    
    if (!in.is_open() || !out.is_open()) {
        std::cerr << "Failed to open input/output file.\n";
        return;
    }

    std::string header;
    std::getline(in, header);
    out << header << "risk_score,risk_level\n";

    std::string line;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> values;

        while (std::getline(ss, token, ',')) {
            values.push_back(token);
        }

        if (values.size() < 4) continue;
        std::string loan_acc_no = values[0];
        int missed = std::stoi(values[1]);
        double loan_amount = std::stod(values[2]);
        double collateral = std::stod(values[3]);
        double interest = std::stod(values[4]);

        double risk_score = (missed * 2.0) + (loan_amount / collateral) + (interest / 2.0);

        std::string risk = calculateLoanRisk(missed, loan_amount, collateral, interest);
        out << line << "," << risk_score << "," << risk << "\n";
    }

    in.close();
    out.close();
    std::cout << "Risk levels written to: " << outputFile << "\n";
}


int main()
{
    std::unordered_map<std::string, std::string> loanFAQs;

    if (!loadFAQsFromFile("LoanFAQs.txt", loanFAQs))
    {
        std::cerr << "Error: File could not open 'LoanFAQs.txt'" << endl;
        return 1;
    }

    time_t now = time(0);
    tm *local_time = localtime(&now);
    int hour = local_time->tm_hour;

    if (hour >= 5 && hour < 12)
        std::cout << "Good Morning!" << endl;
    else if (hour >= 12 && hour < 17)
        std::cout << "Good Afternoon!" << endl;
    else if (hour >= 17 && hour < 21)
        std::cout << "Good Evening!" << endl;
    else
        std::cout << "Good Night!" << endl;

    std::cout << "Welcome to the Loan Chatbot!" << endl;

    while (true)
    {
        std::cout << "\nAsk me something about loans (type 'add' to add new FAQ, 'exit' to quit, 'calculate risk' to calculate the risk manually, 'csv risk' to apply on complete csv file): " << endl;

        std::string user_input;
        std::getline(std::cin, user_input);
        log_question(user_input);

        std::string input_lower = normalize_input(apply_synonym_normalization(user_input));

        if (input_lower == "exit")
        {
            std::cout << "Thank you for using Loan Chatbot. Goodbye!" << endl;
            break;
        }
        else if (input_lower == "add")
        {
            std::string question, answer;
            std::cout << "Enter the new question: ";
            std::getline(std::cin, question);

            std::cout << "Enter the answer: ";
            std::getline(std::cin, answer);

            loanFAQs[question] = answer;
            addFAQs("LoanFAQs.txt", question, answer);

            std::cout << "FAQ added successfully!" << endl;
            continue;
        }
        else if (input_lower == "calculate risk") {
            int missed;
            double loan_amount, collateral, interest;

            std::cout << "Enter missed repayments: ";
            std::cin >> missed;
            std::cout << "Enter loan amount: ";
            std::cin >> loan_amount;
            std::cout << "Enter collateral value: ";
            std::cin >> collateral;
            std::cout << "Enter interest rate: ";
            std::cin >> interest;
            std::cin.ignore(); // clear input buffer

            std::string risk = calculateLoanRisk(missed, loan_amount, collateral, interest);
            std::cout << "Calculated Risk Level: " << risk << "\n";
            continue;
        }
        else if (input_lower == "csv risk") {
            std::string input_file, output_file;
            std::cout << "Enter input CSV file path: ";
            std::getline(std::cin, input_file);
            std::cout << "Enter output CSV file path: ";
            std::getline(std::cin, output_file);
            
            classifyRiskFromCSV(input_file, output_file);
            continue;
        }


        bool answered = false;

        // Exact match
        for (const auto &[q, a] : loanFAQs)
        {
            if (to_lower(q) == input_lower)
            {
                std::cout << a << endl;
                answered = true;
                break;
            }
        }

        // Multi-FAQ keyword detection
        if (!answered)
        {
            std::vector<std::string> multiple_matches = extract_all_keywords(input_lower, loanFAQs);
            if (!multiple_matches.empty())
            {
                std::cout << "I found multiple relevant answers based on your question:\n";
                for (const auto &match : multiple_matches)
                {
                    std::cout << "- " << match << ": " << loanFAQs[match] << "\n";
                }
                continue;
            }

            // Fallback: search by suggestion
            std::cout << "I couldn't find an exact answer. What keyword are you asking about?" << endl;
            std::string keyword;
            std::getline(std::cin, keyword);

            std::vector<std::string> suggestions = searchFAQs(keyword, loanFAQs);

            if (!suggestions.empty())
            {
                std::cout << "Here are some related questions: " << endl;
                for (size_t i = 0; i < suggestions.size(); i++)
                {
                    std::cout << i + 1 << ". " << suggestions[i] << endl;
                }

                std::cout << "Enter the number of question, or type the full question: " << endl;
                std::string choice;
                std::getline(std::cin, choice);

                try
                {
                    size_t index = std::stoi(choice);
                    if (index >= 1 && index <= suggestions.size())
                    {
                        std::cout << loanFAQs[suggestions[index - 1]] << endl;
                        continue;
                    }
                }
                catch (...)
                {
                    for (const auto &[q, a] : loanFAQs)
                    {
                        if (to_lower(q) == to_lower(choice))
                        {
                            std::cout << a << endl;
                            answered = true;
                            break;
                        }
                    }

                    if (!answered)
                    {
                        std::cout << "Sorry, I still couldn't find the answer." << endl;
                    }
                }
            }
            else
            {
                std::cout << "No matching questions found for keyword: " << keyword << endl;
            }
        }
    }
    return 0;
}
