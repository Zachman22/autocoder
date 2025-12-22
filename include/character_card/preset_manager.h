#ifndef PRESET_MANAGER_H
#define PRESET_MANAGER_H

#include "character_card/card_data.h"
#include <string>
#include <vector>
#include <memory>

namespace AutoCoder {
namespace CharacterCard {

class PresetManager {
public:
    PresetManager();
    ~PresetManager() = default;

    // Load built-in presets
    std::vector<CharacterPreset> getBuiltInPresets();

    // User presets
    std::vector<CharacterPreset> getUserPresets();
    bool saveUserPreset(const CharacterPreset& preset);
    bool deleteUserPreset(const std::string& name);

    // Get specific preset
    CharacterPreset getPreset(const std::string& name);

private:
    void initializeBuiltInPresets();
    std::vector<CharacterPreset> builtInPresets;
    std::string userPresetsPath;
};

} // namespace CharacterCard
} // namespace AutoCoder

#endif // PRESET_MANAGER_H
