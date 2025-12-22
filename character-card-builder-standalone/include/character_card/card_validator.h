#ifndef CHARACTER_CARD_VALIDATOR_H
#define CHARACTER_CARD_VALIDATOR_H

#include "character_card/card_data.h"
#include <string>
#include <vector>

namespace AutoCoder {
namespace CharacterCard {

enum class ValidationLevel {
    Error,    // Red - breaks functionality
    Warning,  // Yellow - suboptimal but works
    Info      // Green - all good
};

struct ValidationIssue {
    ValidationLevel level;
    std::string message;
    std::string field;
    std::string suggestion;
};

class CardValidator {
public:
    CardValidator();
    ~CardValidator() = default;

    // Validate a character card
    std::vector<ValidationIssue> validate(const CharacterCardData& card);

    // Get overall validation status
    ValidationLevel getOverallStatus(const std::vector<ValidationIssue>& issues);

    // Format validation report
    std::string formatReport(const std::vector<ValidationIssue>& issues);

private:
    // Individual validation checks
    void checkBasicInfo(const CharacterCardData& card, std::vector<ValidationIssue>& issues);
    void checkTokenLength(const CharacterCardData& card, std::vector<ValidationIssue>& issues);
    void checkConflictingRules(const CharacterCardData& card, std::vector<ValidationIssue>& issues);
    void checkRedundancy(const CharacterCardData& card, std::vector<ValidationIssue>& issues);
    void checkFormattingIssues(const CharacterCardData& card, std::vector<ValidationIssue>& issues);
    void checkPersonalityConsistency(const CharacterCardData& card, std::vector<ValidationIssue>& issues);
    void checkExampleDialogues(const CharacterCardData& card, std::vector<ValidationIssue>& issues);

    // Utility functions
    size_t estimateTokens(const std::string& text);
    bool hasRedundantText(const std::string& text1, const std::string& text2, float threshold = 0.7f);
    bool detectCircularLogic(const CharacterCardData& card);
};

} // namespace CharacterCard
} // namespace AutoCoder

#endif // CHARACTER_CARD_VALIDATOR_H
