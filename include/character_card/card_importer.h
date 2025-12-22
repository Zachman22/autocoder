#ifndef CHARACTER_CARD_IMPORTER_H
#define CHARACTER_CARD_IMPORTER_H

#include "character_card/card_data.h"
#include <string>
#include <vector>
#include <memory>

namespace AutoCoder {
namespace CharacterCard {

enum class ImportFormat {
    SillyTavern,
    CharacterAI,
    TavernAI,
    TextGenWebUI,
    Agnaistic,
    Custom
};

struct ImportResult {
    bool success;
    std::string error_message;
    std::shared_ptr<CharacterCardData> card;
};

class CardImporter {
public:
    CardImporter();
    ~CardImporter() = default;

    // Import from various formats
    ImportResult importFromFile(const std::string& filepath, ImportFormat format = ImportFormat::SillyTavern);
    ImportResult importFromJson(const std::string& jsonString, ImportFormat format = ImportFormat::SillyTavern);
    ImportResult importFromPngCard(const std::string& pngFilepath);

    // Auto-detect format
    ImportFormat detectFormat(const std::string& jsonString);

    // Platform-specific importers
    ImportResult importSillyTavern(const nlohmann::json& j);
    ImportResult importCharacterAI(const nlohmann::json& j);
    ImportResult importTavernAI(const nlohmann::json& j);
    ImportResult importTextGenWebUI(const nlohmann::json& j);
    ImportResult importAgnaistic(const nlohmann::json& j);

    // Extract embedded JSON from PNG
    std::string extractJsonFromPng(const std::string& pngFilepath);

private:
    std::string readFile(const std::string& filepath);
    bool isValidJson(const std::string& jsonString);
};

} // namespace CharacterCard
} // namespace AutoCoder

#endif // CHARACTER_CARD_IMPORTER_H
