#ifndef FAQMANAGER_HPP
#define FAQMANAGER_HPP

#include <unordered_map>
#include <string>
#include <vector>

class FAQManager
{
private:
    std::unordered_map<std::string, std::string> faqMap;
    std::string filename;

public:
    FAQManager(const std::string &file);
    bool loadFAQs();
    void addFAQ(const std::string &question, const std::string &answer);
    std::string searchExact(const std::string &query) const;
    std::vector<std::string> searchKeywords(const std::string &keyword) const;
    std::vector<std::string> extractMatchingFAQs(const std::string &input) const;
    const std::unordered_map<std::string, std::string> &getFAQs() const;
};

#endif
