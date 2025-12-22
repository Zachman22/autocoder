#include "character_card/card_importer.h"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace AutoCoder {
namespace CharacterCard {

CardImporter::CardImporter() {
}

ImportResult CardImporter::importFromFile(const std::string& filepath, ImportFormat format) {
    std::string content = readFile(filepath);

    if (content.empty()) {
        return {false, "Failed to read file or file is empty", nullptr};
    }

    // Check if it's a PNG file
    if (filepath.size() >= 4 && filepath.substr(filepath.size() - 4) == ".png") {
        return importFromPngCard(filepath);
    }

    return importFromJson(content, format);
}

ImportResult CardImporter::importFromJson(const std::string& jsonString, ImportFormat format) {
    if (!isValidJson(jsonString)) {
        return {false, "Invalid JSON format", nullptr};
    }

    try {
        nlohmann::json j = nlohmann::json::parse(jsonString);

        // Auto-detect format if not specified
        if (format == ImportFormat::SillyTavern) {
            format = detectFormat(jsonString);
        }

        switch (format) {
            case ImportFormat::SillyTavern:
                return importSillyTavern(j);
            case ImportFormat::CharacterAI:
                return importCharacterAI(j);
            case ImportFormat::TavernAI:
                return importTavernAI(j);
            case ImportFormat::TextGenWebUI:
                return importTextGenWebUI(j);
            case ImportFormat::Agnaistic:
                return importAgnaistic(j);
            default:
                return importSillyTavern(j); // Default to SillyTavern
        }
    } catch (const std::exception& e) {
        return {false, std::string("JSON parsing error: ") + e.what(), nullptr};
    }
}

ImportResult CardImporter::importFromPngCard(const std::string& pngFilepath) {
    std::string json = extractJsonFromPng(pngFilepath);

    if (json.empty()) {
        return {false, "No embedded JSON data found in PNG", nullptr};
    }

    return importFromJson(json);
}

ImportFormat CardImporter::detectFormat(const std::string& jsonString) {
    try {
        nlohmann::json j = nlohmann::json::parse(jsonString);

        // Check for SillyTavern format
        if (j.contains("name") && j.contains("description") && j.contains("personality")) {
            return ImportFormat::SillyTavern;
        }

        // Check for Character.AI format
        if (j.contains("participant__name") || j.contains("title")) {
            return ImportFormat::CharacterAI;
        }

        // Check for TextGenWebUI format
        if (j.contains("char_name") && j.contains("char_persona")) {
            return ImportFormat::TextGenWebUI;
        }

        // Check for Agnaistic format
        if (j.contains("kind") && j["kind"] == "character") {
            return ImportFormat::Agnaistic;
        }

    } catch (...) {
        // If parsing fails, default to SillyTavern
    }

    return ImportFormat::SillyTavern;
}

ImportResult CardImporter::importSillyTavern(const nlohmann::json& j) {
    try {
        auto card = std::make_shared<CharacterCardData>(CharacterCardData::fromSillyTavernJson(j));

        return {true, "", card};
    } catch (const std::exception& e) {
        return {false, std::string("Import error: ") + e.what(), nullptr};
    }
}

ImportResult CardImporter::importCharacterAI(const nlohmann::json& j) {
    try {
        auto card = std::make_shared<CharacterCardData>();

        // Character.AI format mapping
        card->name = j.value("participant__name", j.value("title", std::string{}));
        card->description = j.value("description", std::string{});
        card->personality = j.value("personality", std::string{});
        card->scenario = j.value("scenario", std::string{});
        card->first_message = j.value("greeting", std::string{});

        // Parse example dialogues if available
        if (j.contains("example_dialogs") && j["example_dialogs"].is_string()) {
            std::string examples = j["example_dialogs"].get<std::string>();
            // Parse the example dialogs string
            // Format is typically "User: ... Bot: ..."
            // This is simplified - real implementation would need better parsing
        }

        return {true, "", card};
    } catch (const std::exception& e) {
        return {false, std::string("Import error: ") + e.what(), nullptr};
    }
}

ImportResult CardImporter::importTavernAI(const nlohmann::json& j) {
    // TavernAI uses similar format to SillyTavern
    return importSillyTavern(j);
}

ImportResult CardImporter::importTextGenWebUI(const nlohmann::json& j) {
    try {
        auto card = std::make_shared<CharacterCardData>();

        // TextGenWebUI format mapping
        card->name = j.value("char_name", std::string{});
        card->description = j.value("char_persona", std::string{});
        card->scenario = j.value("world_scenario", std::string{});
        card->first_message = j.value("char_greeting", std::string{});

        if (j.contains("example_dialogue")) {
            // Parse example dialogue
            std::string example = j["example_dialogue"].get<std::string>();
            // Add to card
        }

        return {true, "", card};
    } catch (const std::exception& e) {
        return {false, std::string("Import error: ") + e.what(), nullptr};
    }
}

ImportResult CardImporter::importAgnaistic(const nlohmann::json& j) {
    try {
        auto card = std::make_shared<CharacterCardData>();

        // Agnaistic format mapping
        card->name = j.value("name", std::string{});
        card->description = j.value("description", std::string{});
        card->personality = j.value("persona", std::string{});
        card->scenario = j.value("scenario", std::string{});
        card->first_message = j.value("greeting", std::string{});

        if (j.contains("sampleChat") && j["sampleChat"].is_string()) {
            std::string samples = j["sampleChat"].get<std::string>();
            // Parse sample chat
        }

        return {true, "", card};
    } catch (const std::exception& e) {
        return {false, std::string("Import error: ") + e.what(), nullptr};
    }
}

std::string CardImporter::extractJsonFromPng(const std::string& pngFilepath) {
    std::ifstream file(pngFilepath, std::ios::binary);
    if (!file) {
        return "";
    }

    // Read the entire file
    std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());

    // Look for tEXt chunk containing JSON data
    // PNG character cards typically store JSON in a tEXt chunk with key "chara"
    const std::string textChunk = "tEXt";
    const std::string charaKey = "chara";

    for (size_t i = 0; i < buffer.size() - 4; ++i) {
        // Check for tEXt chunk signature
        if (buffer[i] == 't' && buffer[i+1] == 'E' && buffer[i+2] == 'X' && buffer[i+3] == 't') {
            // Found tEXt chunk, look for "chara" key
            size_t keyStart = i + 4;

            if (keyStart + charaKey.length() < buffer.size()) {
                std::string key(buffer.begin() + keyStart,
                                buffer.begin() + keyStart + charaKey.length());

                if (key == charaKey) {
                    // Found chara key, extract JSON data
                    size_t jsonStart = keyStart + charaKey.length() + 1; // +1 for null terminator

                    // Find the end of the chunk (look for next chunk or end)
                    size_t jsonEnd = jsonStart;
                    while (jsonEnd < buffer.size() && buffer[jsonEnd] != 0) {
                        jsonEnd++;
                    }

                    // The data might be base64 encoded
                    std::string jsonData(buffer.begin() + jsonStart, buffer.begin() + jsonEnd);

                    // Try to decode if it's base64
                    // For simplicity, assume it's already JSON
                    // In production, implement base64 decoding

                    return jsonData;
                }
            }
        }
    }

    return "";
}

std::string CardImporter::readFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file) {
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool CardImporter::isValidJson(const std::string& jsonString) {
    try {
        nlohmann::json::parse(jsonString);
        return true;
    } catch (...) {
        return false;
    }
}

} // namespace CharacterCard
} // namespace AutoCoder
