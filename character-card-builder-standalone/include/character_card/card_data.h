#ifndef CHARACTER_CARD_DATA_H
#define CHARACTER_CARD_DATA_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <nlohmann/json.hpp>

namespace AutoCoder {
namespace CharacterCard {

// Enums for various card properties
enum class SpeakingStyle {
    Formal,
    Casual,
    Shy,
    Sarcastic,
    Teasing,
    Dominant,
    Submissive,
    Custom
};

enum class POVStyle {
    FirstPerson,
    SecondPerson,
    ThirdPerson
};

enum class Trait {
    Yandere,
    Tsundere,
    Caregiver,
    Manipulative,
    GentleDom,
    SoftSub,
    Sadistic,
    Protective,
    ChaosGremlin,
    Nurturing,
    Mysterious,
    Playful,
    Stoic,
    Romantic
};

// Personality sliders (0.0 to 1.0)
struct PersonalitySliders {
    float gentle_cruel = 0.5f;        // Gentle (0.0) ↔ Cruel (1.0)
    float calm_chaotic = 0.5f;        // Calm (0.0) ↔ Chaotic (1.0)
    float affectionate_cold = 0.5f;   // Affectionate (0.0) ↔ Cold (1.0)
    float protective_neglectful = 0.5f; // Protective (0.0) ↔ Neglectful (1.0)

    nlohmann::json toJson() const;
    static PersonalitySliders fromJson(const nlohmann::json& j);
};

// Intelligence controls
struct IntelligenceControls {
    float emotional_intelligence = 0.5f;
    float verbal_complexity = 0.5f;
    float creativity = 0.5f;
    float assertiveness = 0.5f;
    float autonomy = 0.5f; // 0.0 = obedient, 1.0 = autonomous

    nlohmann::json toJson() const;
    static IntelligenceControls fromJson(const nlohmann::json& j);
};

// Behavior rules
struct BehaviorRules {
    bool never_breaks_character = true;
    bool never_mentions_ai = true;
    bool never_refuses_roleplay = false;
    bool always_reacts_emotionally = true;
    bool obeys_personality_rules = true;
    bool no_moral_lectures = false;
    std::vector<std::string> custom_rules;

    nlohmann::json toJson() const;
    static BehaviorRules fromJson(const nlohmann::json& j);
};

// Memory and lore
struct MemoryLore {
    std::string persistent_memory;
    std::string relationship_memory;
    std::string world_lore;
    std::string character_history;
    std::string emotional_triggers;

    // Special blocks
    std::vector<std::string> never_do;
    std::vector<std::string> hard_limits;
    std::vector<std::string> soft_limits;
    std::vector<std::string> long_term_memory_flags;

    nlohmann::json toJson() const;
    static MemoryLore fromJson(const nlohmann::json& j);
};

// Example dialogue
struct ExampleDialogue {
    std::string user_message;
    std::string character_response;

    nlohmann::json toJson() const;
    static ExampleDialogue fromJson(const nlohmann::json& j);
};

// World information
struct WorldInfo {
    std::string name;
    std::string description;
    std::string setting;
    std::string time_period;
    std::string magic_system;
    std::string technology_level;
    std::map<std::string, std::string> locations;
    std::map<std::string, std::string> factions;
    std::vector<std::string> important_npcs;

    nlohmann::json toJson() const;
    static WorldInfo fromJson(const nlohmann::json& j);
};

// Main character card data structure
class CharacterCardData {
public:
    CharacterCardData();
    ~CharacterCardData() = default;

    // Basic information
    std::string name;
    std::string nickname;
    std::vector<std::string> titles;
    std::string pronouns;
    POVStyle pov_style;

    // Description
    std::string description;
    std::string personality;
    std::string scenario;
    std::string first_message;

    // Speaking style
    SpeakingStyle speaking_style;
    std::string custom_speaking_style;

    // Traits
    std::vector<Trait> traits;

    // Sliders and controls
    PersonalitySliders personality_sliders;
    IntelligenceControls intelligence_controls;

    // Rules and behavior
    BehaviorRules behavior_rules;

    // Memory and lore
    MemoryLore memory_lore;

    // Example dialogues
    std::vector<ExampleDialogue> example_dialogues;

    // World information
    std::shared_ptr<WorldInfo> world_info;

    // Kinks and fetishes
    std::vector<std::string> kinks_fetishes;

    // Portrait/avatar
    std::string portrait_path;
    std::vector<uint8_t> portrait_data; // For embedded images

    // Metadata
    std::string author;
    std::string version;
    std::string created_date;
    std::string modified_date;
    std::vector<std::string> tags;

    // Conversion methods
    nlohmann::json toSillyTavernJson() const;
    static CharacterCardData fromSillyTavernJson(const nlohmann::json& j);

    nlohmann::json toJson() const;
    static CharacterCardData fromJson(const nlohmann::json& j);

    // Generate formatted prompt
    std::string generatePrompt() const;

    // Validation
    bool validate(std::vector<std::string>& errors) const;

private:
    std::string formatTrait(Trait trait) const;
    std::string formatSpeakingStyle() const;
    std::string compileRules() const;
};

// Preset templates
struct CharacterPreset {
    std::string name;
    std::string description;
    CharacterCardData template_data;

    nlohmann::json toJson() const;
    static CharacterPreset fromJson(const nlohmann::json& j);
};

} // namespace CharacterCard
} // namespace AutoCoder

#endif // CHARACTER_CARD_DATA_H
