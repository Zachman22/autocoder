#ifndef AUTOCODER_DICTIONARY_MANAGER_H
#define AUTOCODER_DICTIONARY_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <set>

namespace AutoCoder {
namespace SpellChecker {

struct Dictionary {
    std::string name;
    std::string language;
    std::set<std::string> words;
    std::map<std::string, std::vector<std::string>> word_forms;
    size_t word_count;
};

class DictionaryManager {
public:
    DictionaryManager();
    ~DictionaryManager();

    bool loadDictionary(const std::string& name, const std::string& filepath);
    bool saveDictionary(const std::string& name, const std::string& filepath);

    bool createDictionary(const std::string& name, const std::string& language);
    bool deleteDictionary(const std::string& name);

    bool addWord(const std::string& dictionary_name, const std::string& word);
    bool removeWord(const std::string& dictionary_name, const std::string& word);

    bool hasWord(const std::string& dictionary_name, const std::string& word);
    std::vector<std::string> findSimilarWords(const std::string& dictionary_name, const std::string& word);

    Dictionary* getDictionary(const std::string& name);
    std::vector<std::string> getLoadedDictionaries() const;

    void mergeDictionaries(const std::string& dict1, const std::string& dict2, const std::string& output_name);

private:
    std::map<std::string, Dictionary> dictionaries_;
};

} // namespace SpellChecker
} // namespace AutoCoder

#endif // AUTOCODER_DICTIONARY_MANAGER_H
