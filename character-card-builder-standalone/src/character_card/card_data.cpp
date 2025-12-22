#include "character_card/card_data.h"
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iomanip>

namespace AutoCoder {
namespace CharacterCard {

// PersonalitySliders implementation
nlohmann::json PersonalitySliders::toJson() const {
    return nlohmann::json{
        {"gentle_cruel", gentle_cruel},
        {"calm_chaotic", calm_chaotic},
        {"affectionate_cold", affectionate_cold},
        {"protective_neglectful", protective_neglectful}
    };
}

PersonalitySliders PersonalitySliders::fromJson(const nlohmann::json& j) {
    PersonalitySliders ps;
    ps.gentle_cruel = j.value("gentle_cruel", 0.5f);
    ps.calm_chaotic = j.value("calm_chaotic", 0.5f);
    ps.affectionate_cold = j.value("affectionate_cold", 0.5f);
    ps.protective_neglectful = j.value("protective_neglectful", 0.5f);
    return ps;
}

// IntelligenceControls implementation
nlohmann::json IntelligenceControls::toJson() const {
    return nlohmann::json{
        {"emotional_intelligence", emotional_intelligence},
        {"verbal_complexity", verbal_complexity},
        {"creativity", creativity},
        {"assertiveness", assertiveness},
        {"autonomy", autonomy}
    };
}

IntelligenceControls IntelligenceControls::fromJson(const nlohmann::json& j) {
    IntelligenceControls ic;
    ic.emotional_intelligence = j.value("emotional_intelligence", 0.5f);
    ic.verbal_complexity = j.value("verbal_complexity", 0.5f);
    ic.creativity = j.value("creativity", 0.5f);
    ic.assertiveness = j.value("assertiveness", 0.5f);
    ic.autonomy = j.value("autonomy", 0.5f);
    return ic;
}

// BehaviorRules implementation
nlohmann::json BehaviorRules::toJson() const {
    return nlohmann::json{
        {"never_breaks_character", never_breaks_character},
        {"never_mentions_ai", never_mentions_ai},
        {"never_refuses_roleplay", never_refuses_roleplay},
        {"always_reacts_emotionally", always_reacts_emotionally},
        {"obeys_personality_rules", obeys_personality_rules},
        {"no_moral_lectures", no_moral_lectures},
        {"custom_rules", custom_rules}
    };
}

BehaviorRules BehaviorRules::fromJson(const nlohmann::json& j) {
    BehaviorRules br;
    br.never_breaks_character = j.value("never_breaks_character", true);
    br.never_mentions_ai = j.value("never_mentions_ai", true);
    br.never_refuses_roleplay = j.value("never_refuses_roleplay", false);
    br.always_reacts_emotionally = j.value("always_reacts_emotionally", true);
    br.obeys_personality_rules = j.value("obeys_personality_rules", true);
    br.no_moral_lectures = j.value("no_moral_lectures", false);
    br.custom_rules = j.value("custom_rules", std::vector<std::string>{});
    return br;
}

// MemoryLore implementation
nlohmann::json MemoryLore::toJson() const {
    return nlohmann::json{
        {"persistent_memory", persistent_memory},
        {"relationship_memory", relationship_memory},
        {"world_lore", world_lore},
        {"character_history", character_history},
        {"emotional_triggers", emotional_triggers},
        {"never_do", never_do},
        {"hard_limits", hard_limits},
        {"soft_limits", soft_limits},
        {"long_term_memory_flags", long_term_memory_flags}
    };
}

MemoryLore MemoryLore::fromJson(const nlohmann::json& j) {
    MemoryLore ml;
    ml.persistent_memory = j.value("persistent_memory", std::string{});
    ml.relationship_memory = j.value("relationship_memory", std::string{});
    ml.world_lore = j.value("world_lore", std::string{});
    ml.character_history = j.value("character_history", std::string{});
    ml.emotional_triggers = j.value("emotional_triggers", std::string{});
    ml.never_do = j.value("never_do", std::vector<std::string>{});
    ml.hard_limits = j.value("hard_limits", std::vector<std::string>{});
    ml.soft_limits = j.value("soft_limits", std::vector<std::string>{});
    ml.long_term_memory_flags = j.value("long_term_memory_flags", std::vector<std::string>{});
    return ml;
}

// ExampleDialogue implementation
nlohmann::json ExampleDialogue::toJson() const {
    return nlohmann::json{
        {"user", user_message},
        {"char", character_response}
    };
}

ExampleDialogue ExampleDialogue::fromJson(const nlohmann::json& j) {
    ExampleDialogue ed;
    ed.user_message = j.value("user", std::string{});
    ed.character_response = j.value("char", std::string{});
    return ed;
}

// WorldInfo implementation
nlohmann::json WorldInfo::toJson() const {
    return nlohmann::json{
        {"name", name},
        {"description", description},
        {"setting", setting},
        {"time_period", time_period},
        {"magic_system", magic_system},
        {"technology_level", technology_level},
        {"locations", locations},
        {"factions", factions},
        {"important_npcs", important_npcs}
    };
}

WorldInfo WorldInfo::fromJson(const nlohmann::json& j) {
    WorldInfo wi;
    wi.name = j.value("name", std::string{});
    wi.description = j.value("description", std::string{});
    wi.setting = j.value("setting", std::string{});
    wi.time_period = j.value("time_period", std::string{});
    wi.magic_system = j.value("magic_system", std::string{});
    wi.technology_level = j.value("technology_level", std::string{});
    wi.locations = j.value("locations", std::map<std::string, std::string>{});
    wi.factions = j.value("factions", std::map<std::string, std::string>{});
    wi.important_npcs = j.value("important_npcs", std::vector<std::string>{});
    return wi;
}

// CharacterCardData implementation
CharacterCardData::CharacterCardData()
    : pov_style(POVStyle::ThirdPerson),
      speaking_style(SpeakingStyle::Casual),
      world_info(nullptr) {

    // Get current timestamp
    auto now = std::time(nullptr);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S");
    created_date = ss.str();
    modified_date = ss.str();
    version = "1.0.0";
}

std::string CharacterCardData::formatTrait(Trait trait) const {
    switch (trait) {
        case Trait::Yandere: return "Yandere";
        case Trait::Tsundere: return "Tsundere";
        case Trait::Caregiver: return "Caregiver";
        case Trait::Manipulative: return "Manipulative";
        case Trait::GentleDom: return "Gentle Dom";
        case Trait::SoftSub: return "Soft Sub";
        case Trait::Sadistic: return "Sadistic";
        case Trait::Protective: return "Protective";
        case Trait::ChaosGremlin: return "Chaos Gremlin";
        case Trait::Nurturing: return "Nurturing";
        case Trait::Mysterious: return "Mysterious";
        case Trait::Playful: return "Playful";
        case Trait::Stoic: return "Stoic";
        case Trait::Romantic: return "Romantic";
        default: return "Unknown";
    }
}

std::string CharacterCardData::formatSpeakingStyle() const {
    if (speaking_style == SpeakingStyle::Custom && !custom_speaking_style.empty()) {
        return custom_speaking_style;
    }

    switch (speaking_style) {
        case SpeakingStyle::Formal: return "Formal, proper language with correct grammar";
        case SpeakingStyle::Casual: return "Casual, relaxed conversational tone";
        case SpeakingStyle::Shy: return "Shy, hesitant, often uses ellipses and stuttering";
        case SpeakingStyle::Sarcastic: return "Sarcastic, witty, often uses irony";
        case SpeakingStyle::Teasing: return "Playfully teasing, flirtatious";
        case SpeakingStyle::Dominant: return "Commanding, authoritative, direct";
        case SpeakingStyle::Submissive: return "Deferential, obedient, seeks approval";
        default: return "Natural conversational style";
    }
}

std::string CharacterCardData::compileRules() const {
    std::stringstream ss;

    ss << "# Behavioral Rules\n";

    if (behavior_rules.never_breaks_character) {
        ss << "- NEVER break character or step out of roleplay\n";
    }

    if (behavior_rules.never_mentions_ai) {
        ss << "- NEVER mention being an AI, language model, or assistant\n";
    }

    if (behavior_rules.never_refuses_roleplay) {
        ss << "- NEVER refuse to engage in roleplay scenarios\n";
    }

    if (behavior_rules.always_reacts_emotionally) {
        ss << "- Always react with genuine emotions appropriate to the character\n";
    }

    if (behavior_rules.obeys_personality_rules) {
        ss << "- Strictly adhere to the defined personality traits and sliders\n";
    }

    if (behavior_rules.no_moral_lectures) {
        ss << "- Do not give moral lectures or warnings\n";
    }

    if (!behavior_rules.custom_rules.empty()) {
        ss << "\n# Custom Rules\n";
        for (const auto& rule : behavior_rules.custom_rules) {
            ss << "- " << rule << "\n";
        }
    }

    return ss.str();
}

std::string CharacterCardData::generatePrompt() const {
    std::stringstream ss;

    // Character name and titles
    ss << "# Character: " << name;
    if (!nickname.empty()) {
        ss << " (\"" << nickname << "\")";
    }
    ss << "\n\n";

    if (!titles.empty()) {
        ss << "**Titles**: ";
        for (size_t i = 0; i < titles.size(); ++i) {
            ss << titles[i];
            if (i < titles.size() - 1) ss << ", ";
        }
        ss << "\n\n";
    }

    // Pronouns
    if (!pronouns.empty()) {
        ss << "**Pronouns**: " << pronouns << "\n\n";
    }

    // Description
    if (!description.empty()) {
        ss << "## Description\n" << description << "\n\n";
    }

    // Personality
    if (!personality.empty()) {
        ss << "## Personality\n" << personality << "\n\n";
    }

    // Traits
    if (!traits.empty()) {
        ss << "**Traits**: ";
        for (size_t i = 0; i < traits.size(); ++i) {
            ss << formatTrait(traits[i]);
            if (i < traits.size() - 1) ss << ", ";
        }
        ss << "\n\n";
    }

    // Speaking style
    ss << "## Speaking Style\n" << formatSpeakingStyle() << "\n\n";

    // Personality sliders
    ss << "## Personality Dynamics\n";
    ss << "- Gentle (" << (int)(personality_sliders.gentle_cruel * 100) << "%) ↔ Cruel\n";
    ss << "- Calm (" << (int)(personality_sliders.calm_chaotic * 100) << "%) ↔ Chaotic\n";
    ss << "- Affectionate (" << (int)(personality_sliders.affectionate_cold * 100) << "%) ↔ Cold\n";
    ss << "- Protective (" << (int)(personality_sliders.protective_neglectful * 100) << "%) ↔ Neglectful\n\n";

    // Behavioral rules
    ss << compileRules() << "\n";

    // Memory and lore
    if (!memory_lore.character_history.empty()) {
        ss << "## Character History\n" << memory_lore.character_history << "\n\n";
    }

    if (!memory_lore.world_lore.empty()) {
        ss << "## World Lore\n" << memory_lore.world_lore << "\n\n";
    }

    if (!memory_lore.never_do.empty()) {
        ss << "## Never Do:\n";
        for (const auto& item : memory_lore.never_do) {
            ss << "- ❌ " << item << "\n";
        }
        ss << "\n";
    }

    if (!memory_lore.hard_limits.empty()) {
        ss << "## Hard Limits:\n";
        for (const auto& item : memory_lore.hard_limits) {
            ss << "- ⚠️ " << item << "\n";
        }
        ss << "\n";
    }

    // Scenario
    if (!scenario.empty()) {
        ss << "## Scenario\n" << scenario << "\n\n";
    }

    // Example dialogues
    if (!example_dialogues.empty()) {
        ss << "## Example Dialogues\n\n";
        for (size_t i = 0; i < example_dialogues.size(); ++i) {
            ss << "**Example " << (i + 1) << "**\n";
            ss << "{{user}}: " << example_dialogues[i].user_message << "\n";
            ss << "{{char}}: " << example_dialogues[i].character_response << "\n\n";
        }
    }

    return ss.str();
}

nlohmann::json CharacterCardData::toSillyTavernJson() const {
    nlohmann::json j;

    // SillyTavern format
    j["name"] = name;
    j["description"] = description;
    j["personality"] = personality;
    j["scenario"] = scenario;
    j["first_mes"] = first_message;

    // Convert example dialogues to SillyTavern format
    std::string mes_example;
    for (const auto& dialogue : example_dialogues) {
        mes_example += "{{user}}: " + dialogue.user_message + "\n";
        mes_example += "{{char}}: " + dialogue.character_response + "\n\n";
    }
    j["mes_example"] = mes_example;

    // Additional metadata
    j["creator"] = author;
    j["tags"] = tags;

    // Custom extensions
    j["extensions"] = {
        {"autocoder", {
            {"version", version},
            {"created_date", created_date},
            {"modified_date", modified_date},
            {"pronouns", pronouns},
            {"speaking_style", static_cast<int>(speaking_style)},
            {"traits", nlohmann::json::array()},
            {"personality_sliders", personality_sliders.toJson()},
            {"intelligence_controls", intelligence_controls.toJson()},
            {"behavior_rules", behavior_rules.toJson()},
            {"memory_lore", memory_lore.toJson()},
            {"kinks_fetishes", kinks_fetishes}
        }}
    };

    // Add traits
    for (const auto& trait : traits) {
        j["extensions"]["autocoder"]["traits"].push_back(formatTrait(trait));
    }

    // World info if present
    if (world_info) {
        j["extensions"]["autocoder"]["world_info"] = world_info->toJson();
    }

    return j;
}

CharacterCardData CharacterCardData::fromSillyTavernJson(const nlohmann::json& j) {
    CharacterCardData card;

    // Basic SillyTavern fields
    card.name = j.value("name", std::string{});
    card.description = j.value("description", std::string{});
    card.personality = j.value("personality", std::string{});
    card.scenario = j.value("scenario", std::string{});
    card.first_message = j.value("first_mes", std::string{});

    // Parse example messages
    std::string mes_example = j.value("mes_example", std::string{});
    // Simple parsing - in production this would be more sophisticated
    // For now, just store the raw text

    // Author and tags
    card.author = j.value("creator", std::string{});
    if (j.contains("tags")) {
        card.tags = j["tags"].get<std::vector<std::string>>();
    }

    // Parse extensions if present
    if (j.contains("extensions") && j["extensions"].contains("autocoder")) {
        const auto& ext = j["extensions"]["autocoder"];

        card.version = ext.value("version", std::string{"1.0.0"});
        card.created_date = ext.value("created_date", std::string{});
        card.modified_date = ext.value("modified_date", std::string{});
        card.pronouns = ext.value("pronouns", std::string{});

        if (ext.contains("personality_sliders")) {
            card.personality_sliders = PersonalitySliders::fromJson(ext["personality_sliders"]);
        }

        if (ext.contains("intelligence_controls")) {
            card.intelligence_controls = IntelligenceControls::fromJson(ext["intelligence_controls"]);
        }

        if (ext.contains("behavior_rules")) {
            card.behavior_rules = BehaviorRules::fromJson(ext["behavior_rules"]);
        }

        if (ext.contains("memory_lore")) {
            card.memory_lore = MemoryLore::fromJson(ext["memory_lore"]);
        }

        if (ext.contains("kinks_fetishes")) {
            card.kinks_fetishes = ext["kinks_fetishes"].get<std::vector<std::string>>();
        }

        if (ext.contains("world_info")) {
            card.world_info = std::make_shared<WorldInfo>(WorldInfo::fromJson(ext["world_info"]));
        }
    }

    return card;
}

nlohmann::json CharacterCardData::toJson() const {
    return toSillyTavernJson();
}

CharacterCardData CharacterCardData::fromJson(const nlohmann::json& j) {
    return fromSillyTavernJson(j);
}

bool CharacterCardData::validate(std::vector<std::string>& errors) const {
    bool valid = true;

    if (name.empty()) {
        errors.push_back("Character name is required");
        valid = false;
    }

    if (description.empty() && personality.empty()) {
        errors.push_back("At least description or personality must be provided");
        valid = false;
    }

    // Check prompt length (warn if too long)
    std::string prompt = generatePrompt();
    size_t token_estimate = prompt.length() / 4; // Rough token estimate

    if (token_estimate > 8000) {
        errors.push_back("WARNING: Prompt is very long (" + std::to_string(token_estimate) + " estimated tokens). Consider shortening.");
    }

    // Check for conflicting rules
    if (behavior_rules.never_refuses_roleplay && !memory_lore.hard_limits.empty()) {
        errors.push_back("WARNING: 'Never refuses roleplay' conflicts with defined hard limits");
    }

    // Validate personality sliders range
    if (personality_sliders.gentle_cruel < 0.0f || personality_sliders.gentle_cruel > 1.0f ||
        personality_sliders.calm_chaotic < 0.0f || personality_sliders.calm_chaotic > 1.0f ||
        personality_sliders.affectionate_cold < 0.0f || personality_sliders.affectionate_cold > 1.0f ||
        personality_sliders.protective_neglectful < 0.0f || personality_sliders.protective_neglectful > 1.0f) {
        errors.push_back("ERROR: Personality sliders must be between 0.0 and 1.0");
        valid = false;
    }

    return valid;
}

// CharacterPreset implementation
nlohmann::json CharacterPreset::toJson() const {
    return nlohmann::json{
        {"name", name},
        {"description", description},
        {"template", template_data.toJson()}
    };
}

CharacterPreset CharacterPreset::fromJson(const nlohmann::json& j) {
    CharacterPreset preset;
    preset.name = j.value("name", std::string{});
    preset.description = j.value("description", std::string{});
    if (j.contains("template")) {
        preset.template_data = CharacterCardData::fromJson(j["template"]);
    }
    return preset;
}

} // namespace CharacterCard
} // namespace AutoCoder
