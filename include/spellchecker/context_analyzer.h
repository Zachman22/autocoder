#ifndef AUTOCODER_CONTEXT_ANALYZER_H
#define AUTOCODER_CONTEXT_ANALYZER_H

#include <string>
#include <vector>
#include <map>

namespace AutoCoder {
namespace SpellChecker {

struct ContextInfo {
    std::string before;
    std::string after;
    std::string sentence;
    std::string paragraph;
    std::vector<std::string> related_words;
};

class ContextAnalyzer {
public:
    ContextAnalyzer();
    ~ContextAnalyzer();

    ContextInfo analyzeContext(const std::string& text, int position);

    std::vector<std::string> getContextualSuggestions(
        const std::string& word,
        const ContextInfo& context
    );

    bool isValidInContext(const std::string& word, const ContextInfo& context);

    double calculateContextualRelevance(
        const std::string& word,
        const ContextInfo& context
    );

    void trainOnCorpus(const std::vector<std::string>& texts);
    void loadContextModel(const std::string& filepath);
    void saveContextModel(const std::string& filepath);

private:
    std::vector<std::string> extractNearbyWords(const std::string& text, int position, int window);
    std::map<std::string, double> calculateWordProbabilities(const ContextInfo& context);

    std::map<std::string, std::map<std::string, double>> context_model_;
};

} // namespace SpellChecker
} // namespace AutoCoder

#endif // AUTOCODER_CONTEXT_ANALYZER_H
