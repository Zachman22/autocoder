#ifndef AUTOCODER_ENHANCED_SPELLCHECKER_H
#define AUTOCODER_ENHANCED_SPELLCHECKER_H

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace AutoCoder {
namespace SpellChecker {

struct SpellingError {
    std::string word;
    int start_position;
    int end_position;
    std::vector<std::string> suggestions;
    std::string context;
    double confidence;
};

struct SpellCheckResult {
    std::vector<SpellingError> errors;
    int total_words;
    int error_count;
    double accuracy;
};

class EnhancedSpellChecker {
public:
    EnhancedSpellChecker();
    ~EnhancedSpellChecker();

    void initialize();
    void shutdown();

    SpellCheckResult check(const std::string& text);
    SpellCheckResult checkCode(const std::string& code, const std::string& language);

    std::vector<std::string> getSuggestions(const std::string& word);
    std::string autoCorrect(const std::string& text);

    void addWord(const std::string& word);
    void removeWord(const std::string& word);
    void addToDictionary(const std::string& word, const std::string& dictionary_name);

    void enableContextualChecking(bool enable);
    void enableCamelCaseSupport(bool enable);
    void enableAcronymSupport(bool enable);

    void setLanguage(const std::string& language);
    std::vector<std::string> getSupportedLanguages() const;

    void loadCustomDictionary(const std::string& filepath);
    void saveCustomDictionary(const std::string& filepath);

private:
    bool isValidWord(const std::string& word);
    std::vector<std::string> generateSuggestions(const std::string& word);
    double calculateSimilarity(const std::string& word1, const std::string& word2);
    bool isCodeIdentifier(const std::string& word);
    std::vector<std::string> splitCamelCase(const std::string& word);

    void* dictionary_handle_;
    std::vector<std::string> custom_words_;
    bool contextual_checking_;
    bool camel_case_support_;
    bool acronym_support_;
    std::string current_language_;
};

} // namespace SpellChecker
} // namespace AutoCoder

#endif // AUTOCODER_ENHANCED_SPELLCHECKER_H
