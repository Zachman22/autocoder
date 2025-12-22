# Character Card Builder 🎭

**A powerful standalone GUI application for creating SillyTavern-compatible character cards**

![Version](https://img.shields.io/badge/version-1.0.0-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)

## Overview

Character Card Builder is a sophisticated, user-friendly desktop application designed for creating, editing, and managing AI roleplay character cards. Built with modern C++ and Qt6, it provides an elegant graphical interface for designing rich, detailed characters compatible with SillyTavern and other AI chat platforms.

## ✨ Key Features

### 🎯 Professional Character Creation
- **SillyTavern Compatible**: Full support for SillyTavern JSON format
- **Wizard Interface**: Step-by-step guided character creation
- **Simple & Advanced Modes**: Toggle between beginner-friendly and expert modes
- **Real-time Validation**: Instant feedback on card quality and compatibility

### 🎭 Advanced Personality System
- **Personality Sliders**: Fine-tune 4 core personality dimensions
  - Gentle ↔ Cruel
  - Calm ↔ Chaotic
  - Affectionate ↔ Cold
  - Protective ↔ Neglectful
- **Character Traits**: 14 preset traits (Yandere, Tsundere, Caregiver, etc.)
- **Speaking Styles**: 8 preset styles (Formal, Casual, Shy, Sarcastic, etc.)
- **Intelligence Controls**: Customize emotional intelligence, creativity, and more

### 🧠 Memory & Lore Management
- Persistent memory and relationship tracking
- Character history and backstory
- World lore and setting details
- Emotional triggers
- Hard/soft limits and boundaries

### 🌍 World Builder
- Create rich, detailed worlds
- Define locations, factions, and NPCs
- Set time periods and technology levels
- Magic system definitions

### 📦 Import & Export
**Import from:**
- SillyTavern (.json)
- Character.AI
- TavernAI
- TextGenWebUI
- Agnaistic
- PNG cards with embedded JSON

**Export to:**
- JSON (SillyTavern format)
- PNG Card (image + embedded JSON)
- TXT (raw prompt)

### 🔍 Advanced Features
- **Card Validator**: Real-time validation with detailed error reports
- **Preset Library**: Built-in character templates
- **Kinks/Fetishes Database**: Import from online databases
- **Portrait Manager**: Load and manage character images
- **Version Control**: Track and compare card versions
- **Token Estimation**: Monitor prompt length

## 📸 Screenshots

*(Screenshots would go here when available)*

## 🚀 Installation

### Pre-built Binaries (Recommended)

Download the latest release for your platform:
- **Windows**: `CharacterCardBuilder-1.0.0-win64.exe`
- **Linux (DEB)**: `CharacterCardBuilder-1.0.0-Linux.deb`
- **Linux (RPM)**: `CharacterCardBuilder-1.0.0-Linux.rpm`
- **macOS**: `CharacterCardBuilder-1.0.0-Darwin.dmg`

### Building from Source

#### Prerequisites
- CMake 3.15 or higher
- Qt6 (Core, Widgets, Network, Gui)
- OpenSSL
- libcurl
- C++17 compatible compiler (GCC, Clang, or MSVC)

#### Build Instructions

**Linux/macOS:**
```bash
# Clone the repository
git clone https://github.com/yourusername/character-card-builder.git
cd character-card-builder

# Install dependencies (Ubuntu/Debian)
sudo apt-get install qt6-base-dev libssl-dev libcurl4-openssl-dev cmake g++

# Install dependencies (macOS with Homebrew)
brew install qt@6 openssl curl cmake

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build
cmake --build . -j$(nproc)

# Install (optional)
sudo cmake --install .

# Run
./character-card-builder
```

**Windows:**
```powershell
# Clone the repository
git clone https://github.com/yourusername/character-card-builder.git
cd character-card-builder

# Install Qt6, OpenSSL, and cURL via vcpkg
vcpkg install qt6 openssl curl

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg-root]/scripts/buildsystems/vcpkg.cmake

# Build
cmake --build . --config Release

# Run
.\Release\character-card-builder.exe
```

## 📖 Quick Start Guide

### Creating Your First Character

1. **Launch the Application**
   ```bash
   ./character-card-builder
   ```

2. **Use the Wizard** (Recommended for beginners)
   - Click **Tools → Guided Wizard**
   - Follow the step-by-step prompts
   - Enter character name, personality, and traits
   - Add example dialogues
   - Click **Finish**

3. **Manual Creation** (For advanced users)
   - Click **File → New Card**
   - Navigate through the tabs:
     - **📝 Basic Info**: Name, description, personality
     - **🎭 Personality**: Adjust sliders and select traits
     - **🧠 Memory & Lore**: Add character history
     - **💬 Dialogues**: Create example conversations
     - **🌍 World Builder**: Build the setting
     - **🖼️ Portrait**: Add character image

4. **Validate Your Card**
   - Click **Tools → Validate Card**
   - Review any warnings or errors
   - Make necessary adjustments

5. **Export**
   - Click **File → Export Card**
   - Choose format (JSON for SillyTavern)
   - Select destination
   - Click **Export**

## 🎮 Usage Examples

### Importing an Existing Card
```
File → Import Card → Select your .json or .png file
```

### Using Presets
```
Presets → Load Preset → Choose template → Customize
```

### Importing Kinks Database
```
Tools → Import Kinks Database → Wait for download → Select items
```

## 🛠️ Advanced Usage

### Keyboard Shortcuts
- `Ctrl+N` - New Card
- `Ctrl+O` - Open Card
- `Ctrl+S` - Save Card
- `Ctrl+Shift+S` - Save As
- `Ctrl+E` - Export Card
- `Ctrl+I` - Import Card
- `Ctrl+W` - Guided Wizard
- `F5` - Validate Card

### Command Line Options
```bash
# Open a specific card
./character-card-builder /path/to/card.json

# Start with wizard
./character-card-builder --wizard

# Export card (non-interactive)
./character-card-builder --export card.json --format png --output card.png
```

## 📐 Architecture

### Technology Stack
- **Language**: C++17
- **GUI Framework**: Qt6
- **JSON Library**: nlohmann/json v3.11.3
- **HTTP Client**: libcurl
- **SSL/TLS**: OpenSSL

### Project Structure
```
character-card-builder/
├── CMakeLists.txt
├── README.md
├── LICENSE
├── CHARACTER_BUILDER.md
├── include/
│   ├── character_card/
│   │   ├── card_data.h
│   │   ├── card_validator.h
│   │   ├── card_importer.h
│   │   ├── web_scraper.h
│   │   ├── character_builder_window.h
│   │   └── [other headers]
│   └── nlohmann/
│       └── json.hpp
├── src/
│   ├── main.cpp
│   └── character_card/
│       ├── card_data.cpp
│       ├── card_validator.cpp
│       └── [other implementations]
└── resources/
    ├── icons/
    ├── presets/
    └── templates/
```

## 🤝 Contributing

Contributions are welcome! Please follow these guidelines:

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/amazing-feature`
3. Make your changes
4. Test thoroughly
5. Commit: `git commit -m 'Add amazing feature'`
6. Push: `git push origin feature/amazing-feature`
7. Open a Pull Request

### Code Style
- Follow C++17 standards
- Use Qt naming conventions
- Comment complex logic
- Write descriptive commit messages

## 📝 File Format

Character cards use SillyTavern-compatible JSON:

```json
{
  "name": "Character Name",
  "description": "Physical description...",
  "personality": "Personality traits...",
  "scenario": "Setting and context...",
  "first_mes": "Greeting message...",
  "mes_example": "{{user}}: Hi\n{{char}}: Hello!",
  "creator": "Your Name",
  "tags": ["roleplay", "fantasy"],
  "extensions": {
    "character_card_builder": {
      "version": "1.0.0",
      "personality_sliders": {...},
      "behavior_rules": {...},
      "world_info": {...}
    }
  }
}
```

## 🐛 Troubleshooting

### Common Issues

**Application won't start:**
- Ensure Qt6 is properly installed
- Check library dependencies: `ldd character-card-builder` (Linux)

**Import fails:**
- Verify file format is supported
- Check JSON syntax
- Try opening in text editor to verify structure

**Export produces invalid cards:**
- Run validator before exporting
- Check for required fields
- Ensure token count is reasonable

**Web scraping fails:**
- Check internet connection
- Verify firewall settings
- Some sites may block automated requests

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- **SillyTavern Team** - For the character card format
- **Qt Project** - For the excellent GUI framework
- **nlohmann** - For the JSON library
- **Community Contributors** - For feedback and suggestions

## 📞 Support

- **Documentation**: See [CHARACTER_BUILDER.md](CHARACTER_BUILDER.md) for detailed guide
- **Issues**: [GitHub Issues](https://github.com/yourusername/character-card-builder/issues)
- **Discussions**: [GitHub Discussions](https://github.com/yourusername/character-card-builder/discussions)
- **Email**: support@charactercardbuilder.app

## 🗺️ Roadmap

### Version 1.1 (Upcoming)
- [ ] AI-assisted character generation
- [ ] Behavior simulation mode
- [ ] Community preset sharing
- [ ] Plugin system

### Version 1.2 (Planned)
- [ ] Multi-language UI support
- [ ] Advanced regex-based rules
- [ ] Relationship progression tracking
- [ ] Mobile companion app

### Version 2.0 (Future)
- [ ] Cloud synchronization
- [ ] Collaborative editing
- [ ] AI portrait generation
- [ ] Voice line integration

## 💖 Support the Project

If you find this tool useful, consider:
- ⭐ Starring the repository
- 🐛 Reporting bugs
- 💡 Suggesting features
- 🤝 Contributing code
- ☕ [Buy me a coffee](https://buymeacoffee.com/charactercardbuilder)

---

**Made with ❤️ for the AI roleplay community**

*Character Card Builder - Creating Better Characters, One Card at a Time*
