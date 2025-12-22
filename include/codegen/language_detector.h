#ifndef AUTOCODER_LANGUAGE_DETECTOR_H
#define AUTOCODER_LANGUAGE_DETECTOR_H

#include <string>
#include <vector>
#include <map>

namespace AutoCoder {
namespace CodeGen {

struct LanguageInfo {
    std::string name;
    std::string extension;
    std::string comment_style;
    std::vector<std::string> keywords;
    std::vector<std::string> frameworks;
};

struct DetectionResult {
    std::string language;
    double confidence;
    std::vector<std::string> suggested_languages;
};

class LanguageDetector {
public:
    LanguageDetector();
    ~LanguageDetector();

    DetectionResult detectFromCode(const std::string& code);
    DetectionResult detectFromDescription(const std::string& description);
    DetectionResult detectFromFile(const std::string& filepath);

    std::string getLanguageFromExtension(const std::string& extension);
    std::vector<std::string> getSupportedLanguages() const;

    LanguageInfo getLanguageInfo(const std::string& language);

    void addLanguageSupport(const LanguageInfo& info);

private:
    double calculateSimilarity(const std::string& code, const LanguageInfo& info);
    std::vector<std::string> extractKeywords(const std::string& code);

    std::map<std::string, LanguageInfo> supported_languages_;
};

} // namespace CodeGen
} // namespace AutoCoder

#endif // AUTOCODER_LANGUAGE_DETECTOR_H
