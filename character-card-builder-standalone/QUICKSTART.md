# Quick Start Guide 🚀

Get up and running with Character Card Builder in 5 minutes!

## Installation

### Linux
```bash
# Extract the archive
tar -xzf character-card-builder-standalone-v1.0.0.tar.gz
cd character-card-builder-standalone

# Build and run
./build.sh
cd build
./character-card-builder
```

### macOS
```bash
# Extract and build
tar -xzf character-card-builder-standalone-v1.0.0.tar.gz
cd character-card-builder-standalone
./build.sh
cd build
./character-card-builder
```

### Windows
```powershell
# Extract the archive
# Open PowerShell in the extracted directory

mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
.\Release\character-card-builder.exe
```

## First Steps

### 1. Create Your First Character (Easy Mode)

1. **Launch** the application
2. Click **Tools → Guided Wizard**
3. **Fill in the wizard:**
   - **Page 1**: Welcome (click Next)
   - **Page 2**: Enter character name and basic info
   - **Page 3**: Adjust personality sliders
   - **Page 4**: Review and finish

### 2. Or Start from a Preset

1. Click **Presets → Load Preset**
2. Choose a template (e.g., "Romantic Partner")
3. Customize the character
4. Click **File → Save**

### 3. Manual Creation (Advanced)

Navigate through the tabs on the left:
- **📝 Basic Info**: Name, description, personality
- **🎭 Personality**: Adjust sliders and select traits
- **🧠 Memory & Lore**: Add backstory and world info
- **💬 Dialogues**: Create example conversations
- **🌍 World Builder**: Build the setting
- **🖼️ Portrait**: Upload character image

### 4. Validate Your Card

- Click **Tools → Validate Card** (or press F5)
- Fix any errors or warnings shown
- Green status = ready to export!

### 5. Export for SillyTavern

1. Click **File → Export Card**
2. Select **JSON** format
3. Choose save location
4. Click **Export**
5. Import the .json file into SillyTavern

## Keyboard Shortcuts

- `Ctrl+N` - New Card
- `Ctrl+O` - Open Card  
- `Ctrl+S` - Save Card
- `Ctrl+E` - Export Card
- `F5` - Validate Card

## Need Help?

- **Full Guide**: See [CHARACTER_BUILDER.md](CHARACTER_BUILDER.md)
- **Build Issues**: See [BUILD.md](BUILD.md)
- **Support**: GitHub Issues or email support@charactercardbuilder.app

## Tips

1. **Start Simple**: Use the wizard for your first character
2. **Validate Often**: Check for errors before exporting
3. **Use Presets**: They're great starting points
4. **Save Frequently**: Use Ctrl+S to save your work
5. **Keep It Under 6000 tokens**: For best AI performance

## Next Steps

- Explore the preset library
- Import existing cards from other platforms
- Join the community for tips and templates
- Create your dream character!

Enjoy creating amazing characters! 🎭✨
