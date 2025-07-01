#include "FAQManager.hpp"
#include "Utils.hpp"
#include <fstream>
#include <regex>

FAQManager::FAQManager(const std::string &file) : filename(file) {}

bool FAQManager::loadFAQs()
{
    std::ifstream file(filename);
    if (!file.is_open())
        return false;

    std::string line;
    while (std::getline(file, line))
    {
        size_t sep = line.find('|');
        if (sep != std::string::npos)
        {
            std::string q = line.substr(0, sep);
            std::string a = line.substr(sep + 1);
            faqMap[q] = a;
        }
    }
    return true;
}

void FAQManager::addFAQ(const std::string &question, const std::string &answer)
{
    faqMap[question] = answer;
    std::ofstream file(filename, std::ios::app);
    if (file.is_open())
    {
        file << question << "|" << answer << "\n";
        file.close();
    }
}

std::string FAQManager::searchExact(const std::string &query) const
{
    for (const auto &[q, a] : faqMap)
    {
        if (Utils::toLower(q) == query)
            return a;
    }
    return "";
}

std::vector<std::string> FAQManager::searchKeywords(const std::string &keyword) const
{
    std::vector<std::string> results;
    std::string lowerKeyword = Utils::toLower(keyword);
    for (const auto &[q, _] : faqMap)
    {
        if (Utils::toLower(q).find(lowerKeyword) != std::string::npos)
        {
            results.push_back(q);
        }
    }
    return results;
}

std::vector<std::string> FAQManager::extractMatchingFAQs(const std::string &input) const
{
    std::vector<std::string> found;
    for (const auto &[q, _] : faqMap)
    {
        std::regex word("\\b" + Utils::toLower(q) + "\\b");
        if (std::regex_search(input, word))
        {
            found.push_back(q);
        }
    }
    return found;
}

const std::unordered_map<std::string, std::string> &FAQManager::getFAQs() const
{
    return faqMap;
}
