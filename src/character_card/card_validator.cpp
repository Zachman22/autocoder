#include "character_card/card_validator.h"
#include <sstream>
#include <algorithm>
#include <regex>

namespace AutoCoder {
namespace CharacterCard {

CardValidator::CardValidator() {
}

std::vector<ValidationIssue> CardValidator::validate(const CharacterCardData& card) {
    std::vector<ValidationIssue> issues;

    checkBasicInfo(card, issues);
    checkTokenLength(card, issues);
    checkConflictingRules(card, issues);
    checkRedundancy(card, issues);
    checkFormattingIssues(card, issues);
    checkPersonalityConsistency(card, issues);
    checkExampleDialogues(card, issues);

    return issues;
}

ValidationLevel CardValidator::getOverallStatus(const std::vector<ValidationIssue>& issues) {
    bool hasError = false;
    bool hasWarning = false;

    for (const auto& issue : issues) {
        if (issue.level == ValidationLevel::Error) {
            hasError = true;
        } else if (issue.level == ValidationLevel::Warning) {
            hasWarning = true;
        }
    }

    if (hasError) return ValidationLevel::Error;
    if (hasWarning) return ValidationLevel::Warning;
    return ValidationLevel::Info;
}

std::string CardValidator::formatReport(const std::vector<ValidationIssue>& issues) {
    std::stringstream ss;

    if (issues.empty()) {
        ss << "✓ Card validation passed with no issues!\n";
        return ss.str();
    }

    int errorCount = 0;
    int warningCount = 0;

    for (const auto& issue : issues) {
        if (issue.level == ValidationLevel::Error) {
            ss << "❌ ERROR: ";
            errorCount++;
        } else if (issue.level == ValidationLevel::Warning) {
            ss << "⚠️  WARNING: ";
            warningCount++;
        } else {
            ss << "ℹ️  INFO: ";
        }

        ss << issue.message;
        if (!issue.field.empty()) {
            ss << " [Field: " << issue.field << "]";
        }
        ss << "\n";

        if (!issue.suggestion.empty()) {
            ss << "   💡 Suggestion: " << issue.suggestion << "\n";
        }
    }

    ss << "\n";
    ss << "Summary: " << errorCount << " errors, " << warningCount << " warnings\n";

    return ss.str();
}

void CardValidator::checkBasicInfo(const CharacterCardData& card, std::vector<ValidationIssue>& issues) {
    if (card.name.empty()) {
        issues.push_back({
            ValidationLevel::Error,
            "Character name is required",
            "name",
            "Provide a name for your character"
        });
    }

    if (card.description.empty() && card.personality.empty()) {
        issues.push_back({
            ValidationLevel::Error,
            "Either description or personality must be provided",
            "description/personality",
            "Add a description or personality to define your character"
        });
    }

    if (card.first_message.empty()) {
        issues.push_back({
            ValidationLevel::Warning,
            "No first message defined",
            "first_message",
            "Add a greeting message for your character"
        });
    }

    if (card.example_dialogues.empty()) {
        issues.push_back({
            ValidationLevel::Warning,
            "No example dialogues provided",
            "example_dialogues",
            "Add example dialogues to help define character behavior"
        });
    }
}

void CardValidator::checkTokenLength(const CharacterCardData& card, std::vector<ValidationIssue>& issues) {
    std::string prompt = card.generatePrompt();
    size_t tokens = estimateTokens(prompt);

    if (tokens > 8000) {
        issues.push_back({
            ValidationLevel::Error,
            "Prompt is too long (" + std::to_string(tokens) + " tokens). May exceed model context limits.",
            "overall",
            "Shorten descriptions, reduce example dialogues, or simplify memory lore"
        });
    } else if (tokens > 6000) {
        issues.push_back({
            ValidationLevel::Warning,
            "Prompt is very long (" + std::to_string(tokens) + " tokens). Consider shortening.",
            "overall",
            "Review and condense verbose sections"
        });
    } else if (tokens < 100) {
        issues.push_back({
            ValidationLevel::Warning,
            "Prompt is very short (" + std::to_string(tokens) + " tokens). May lack detail.",
            "overall",
            "Add more personality details and example dialogues"
        });
    }
}

void CardValidator::checkConflictingRules(const CharacterCardData& card, std::vector<ValidationIssue>& issues) {
    // Check for conflicting behavior rules
    if (card.behavior_rules.never_refuses_roleplay && !card.memory_lore.hard_limits.empty()) {
        issues.push_back({
            ValidationLevel::Warning,
            "Conflict: 'Never refuses roleplay' enabled but hard limits defined",
            "behavior_rules",
            "Either disable 'never refuses' or remove hard limits for consistency"
        });
    }

    // Check if personality sliders conflict with traits
    if (card.personality_sliders.gentle_cruel > 0.7f) {
        // High cruelty
        for (const auto& trait : card.traits) {
            if (trait == Trait::Caregiver || trait == Trait::Nurturing) {
                issues.push_back({
                    ValidationLevel::Warning,
                    "Conflict: High cruelty slider conflicts with nurturing/caregiver traits",
                    "personality_sliders",
                    "Adjust cruelty slider or remove conflicting traits"
                });
                break;
            }
        }
    }

    if (card.personality_sliders.gentle_cruel < 0.3f) {
        // High gentleness
        for (const auto& trait : card.traits) {
            if (trait == Trait::Sadistic) {
                issues.push_back({
                    ValidationLevel::Warning,
                    "Conflict: High gentleness conflicts with sadistic trait",
                    "personality_sliders",
                    "Adjust gentleness slider or remove sadistic trait"
                });
                break;
            }
        }
    }
}

void CardValidator::checkRedundancy(const CharacterCardData& card, std::vector<ValidationIssue>& issues) {
    // Check for redundant text between description and personality
    if (!card.description.empty() && !card.personality.empty()) {
        if (hasRedundantText(card.description, card.personality, 0.5f)) {
            issues.push_back({
                ValidationLevel::Warning,
                "Description and personality contain similar text",
                "description/personality",
                "Avoid repeating the same information in multiple fields"
            });
        }
    }

    // Check for duplicate example dialogues
    for (size_t i = 0; i < card.example_dialogues.size(); ++i) {
        for (size_t j = i + 1; j < card.example_dialogues.size(); ++j) {
            if (card.example_dialogues[i].character_response == card.example_dialogues[j].character_response) {
                issues.push_back({
                    ValidationLevel::Warning,
                    "Duplicate example dialogue responses detected",
                    "example_dialogues",
                    "Ensure each example dialogue is unique"
                });
                break;
            }
        }
    }
}

void CardValidator::checkFormattingIssues(const CharacterCardData& card, std::vector<ValidationIssue>& issues) {
    // Check for improper {{char}} and {{user}} usage
    std::regex charPattern(R"(\{\{char\}\})");
    std::regex userPattern(R"(\{\{user\}\})");

    // These should NOT appear in description or personality (they're for dialogue examples)
    if (std::regex_search(card.description, charPattern)) {
        issues.push_back({
            ValidationLevel::Warning,
            "{{char}} placeholder found in description - should use actual character name",
            "description",
            "Replace {{char}} with the character's actual name in descriptions"
        });
    }

    if (std::regex_search(card.personality, charPattern)) {
        issues.push_back({
            ValidationLevel::Warning,
            "{{char}} placeholder found in personality - should use actual character name",
            "personality",
            "Replace {{char}} with the character's actual name"
        });
    }

    // Check for common formatting mistakes
    if (card.description.find("**") != std::string::npos &&
        std::count(card.description.begin(), card.description.end(), '*') % 2 != 0) {
        issues.push_back({
            ValidationLevel::Warning,
            "Unmatched markdown formatting in description",
            "description",
            "Ensure all ** and * are properly closed"
        });
    }
}

void CardValidator::checkPersonalityConsistency(const CharacterCardData& card, std::vector<ValidationIssue>& issues) {
    // Check if personality traits are mentioned but not reflected in sliders
    std::string fullText = card.description + " " + card.personality;
    std::transform(fullText.begin(), fullText.end(), fullText.begin(), ::tolower);

    struct KeywordCheck {
        std::string keyword;
        std::string slider;
        float expectedValue;
        std::string direction;
    };

    std::vector<KeywordCheck> checks = {
        {"cruel", "gentle_cruel", 0.7f, "high"},
        {"sadistic", "gentle_cruel", 0.8f, "high"},
        {"kind", "gentle_cruel", 0.2f, "low"},
        {"gentle", "gentle_cruel", 0.2f, "low"},
        {"chaotic", "calm_chaotic", 0.7f, "high"},
        {"impulsive", "calm_chaotic", 0.7f, "high"},
        {"calm", "calm_chaotic", 0.2f, "low"},
        {"serene", "calm_chaotic", 0.2f, "low"},
        {"cold", "affectionate_cold", 0.7f, "high"},
        {"distant", "affectionate_cold", 0.7f, "high"},
        {"loving", "affectionate_cold", 0.2f, "low"},
        {"affectionate", "affectionate_cold", 0.2f, "low"}
    };

    for (const auto& check : checks) {
        if (fullText.find(check.keyword) != std::string::npos) {
            float actualValue = 0.0f;
            if (check.slider == "gentle_cruel") actualValue = card.personality_sliders.gentle_cruel;
            else if (check.slider == "calm_chaotic") actualValue = card.personality_sliders.calm_chaotic;
            else if (check.slider == "affectionate_cold") actualValue = card.personality_sliders.affectionate_cold;

            bool inconsistent = false;
            if (check.direction == "high" && actualValue < 0.5f) inconsistent = true;
            if (check.direction == "low" && actualValue > 0.5f) inconsistent = true;

            if (inconsistent) {
                issues.push_back({
                    ValidationLevel::Info,
                    "Text mentions '" + check.keyword + "' but slider may not reflect this",
                    check.slider,
                    "Consider adjusting the " + check.slider + " slider"
                });
            }
        }
    }
}

void CardValidator::checkExampleDialogues(const CharacterCardData& card, std::vector<ValidationIssue>& issues) {
    if (card.example_dialogues.size() > 10) {
        issues.push_back({
            ValidationLevel::Warning,
            "Too many example dialogues (" + std::to_string(card.example_dialogues.size()) + ")",
            "example_dialogues",
            "Consider reducing to 5-8 high-quality examples"
        });
    }

    for (size_t i = 0; i < card.example_dialogues.size(); ++i) {
        const auto& dialogue = card.example_dialogues[i];

        if (dialogue.user_message.empty()) {
            issues.push_back({
                ValidationLevel::Error,
                "Example dialogue " + std::to_string(i + 1) + " has empty user message",
                "example_dialogues[" + std::to_string(i) + "]",
                "Add a user message or remove this example"
            });
        }

        if (dialogue.character_response.empty()) {
            issues.push_back({
                ValidationLevel::Error,
                "Example dialogue " + std::to_string(i + 1) + " has empty character response",
                "example_dialogues[" + std::to_string(i) + "]",
                "Add a character response or remove this example"
            });
        }

        if (dialogue.character_response.length() > 500) {
            issues.push_back({
                ValidationLevel::Info,
                "Example dialogue " + std::to_string(i + 1) + " response is very long",
                "example_dialogues[" + std::to_string(i) + "]",
                "Consider shortening for better training"
            });
        }
    }
}

size_t CardValidator::estimateTokens(const std::string& text) {
    // Rough token estimation: ~4 characters per token on average
    // This is a simplification; real tokenization is more complex
    return text.length() / 4;
}

bool CardValidator::hasRedundantText(const std::string& text1, const std::string& text2, float threshold) {
    // Simple overlap check - count common words
    std::stringstream ss1(text1), ss2(text2);
    std::vector<std::string> words1, words2;
    std::string word;

    while (ss1 >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        words1.push_back(word);
    }

    while (ss2 >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        words2.push_back(word);
    }

    size_t commonCount = 0;
    for (const auto& w1 : words1) {
        if (std::find(words2.begin(), words2.end(), w1) != words2.end()) {
            commonCount++;
        }
    }

    float overlap = static_cast<float>(commonCount) / static_cast<float>(std::min(words1.size(), words2.size()));
    return overlap > threshold;
}

bool CardValidator::detectCircularLogic(const CharacterCardData& card) {
    // Check for self-referential or circular definitions
    // This is a simplified check
    return false;
}

} // namespace CharacterCard
} // namespace AutoCoder
