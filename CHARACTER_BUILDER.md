# Character Card Builder 🎭

## Overview

The **Character Card Builder** is a powerful tool integrated into AutoCoder for creating, editing, and managing SillyTavern-compatible character cards. It provides an elegant GUI for designing AI roleplay characters with rich personality systems, behavior rules, memory management, and world-building features.

## Features

### 🔑 Core Features

#### 1. **Guided Character Builder (Wizard)**
- Step-by-step wizard interface for creating characters from scratch
- Intuitive prompts for character name, personality, and behavior
- Live preview of generated cards
- Preset templates for quick start

#### 2. **SillyTavern-Compatible Format**
- Fully compatible with SillyTavern JSON format
- Auto-generates `{{char}}` and `{{user}}` placeholders
- Example dialogue formatting
- Scenario blocks and author notes
- Extended metadata support

#### 3. **Simple and Advanced Modes**
- 🟢 **Simple Mode**: Sliders, toggles, and preset options only
- 🔴 **Advanced Mode**: Raw prompt editing with validation
- Switch between modes seamlessly

### 🎭 Personality System

#### **Personality Sliders**
Fine-tune character behavior with intuitive sliders:
- **Gentle ↔ Cruel**: Control compassion levels
- **Calm ↔ Chaotic**: Manage temperament
- **Affectionate ↔ Cold**: Adjust emotional warmth
- **Protective ↔ Neglectful**: Set caring behavior

#### **Character Traits**
Mix and match predefined traits:
- Yandere, Tsundere, Caregiver
- Manipulative, Gentle Dom, Soft Sub
- Sadistic, Protective, Chaos Gremlin
- Nurturing, Mysterious, Playful, Stoic, Romantic

#### **Speaking Styles**
Choose from preset speaking patterns:
- Formal, Casual, Shy
- Sarcastic, Teasing
- Dominant, Submissive
- Custom (define your own)

### 🧠 Intelligence & Behavior

#### **Intelligence Controls**
- Emotional Intelligence
- Verbal Complexity
- Creativity Level
- Assertiveness
- Autonomy vs Obedience

#### **Behavior Rules Engine**
Checkbox-based rule configuration:
- ✅ Never breaks character
- ✅ Never mentions AI
- ✅ Never refuses roleplay
- ✅ Always reacts emotionally
- ✅ Obeys personality rules
- ❌ No moral lectures (optional)

Custom rules can be added as needed.

### 💾 Memory & Lore System

Dedicated sections for:
- **Persistent Memory**: Long-term character memories
- **Relationship Memory**: Connection with the user
- **World Lore**: Background information about the setting
- **Character History**: Backstory and past events
- **Emotional Triggers**: Situations that evoke strong reactions

#### **Special Blocks**
- ❌ **Never Do**: Hard boundaries
- ⚠️ **Hard Limits**: Absolute restrictions
- ⚠️ **Soft Limits**: Flexible boundaries
- 💾 **Long-term Memory Flags**: Important events to remember

### 💬 Dynamic Dialogue System

- **Example Dialogues**: Create sample conversations
- **Auto-generation**: AI-powered dialogue suggestions
- **Live Preview**: See how changes affect output
- **Tone-aware**: Respects speaking style and personality
- **No duplicates**: Validation prevents redundant examples

### 🌍 World Builder

Build rich, detailed worlds for your characters:
- **World Information**: Name, description, setting
- **Time Period**: Historical context
- **Magic System**: Supernatural elements
- **Technology Level**: Sci-fi or fantasy tech
- **Locations**: Important places
- **Factions**: Organizations and groups
- **NPCs**: Supporting characters

### 🖼️ Portrait Manager

- **Load Images**: Import character portraits
- **PNG Card Support**: Embed JSON data in PNG images
- **AI Generation**: (Coming soon) Generate portraits with AI
- **Preview**: View portraits before exporting

### 🔍 Card Validator

Real-time validation with color-coded status:
- ✅ **Green**: Card is valid
- ⚠️ **Yellow**: Warnings (card works but has issues)
- ❌ **Red**: Errors (card may not work properly)

**Validation Checks:**
- Token length warnings
- Broken formatting detection
- Conflicting rules identification
- Redundant instructions
- Personality consistency
- Example dialogue quality

### 📦 Import & Export

#### **Import From:**
- SillyTavern (.json)
- Character.AI (various formats)
- TavernAI
- TextGenWebUI
- Agnaistic
- PNG cards (with embedded JSON)

#### **Export To:**
- JSON (SillyTavern format)
- PNG Card (image with embedded JSON)
- TXT (raw prompt text)
- Clipboard copy

### 🗂️ Preset Library

**Built-in Presets:**
- Romantic Partner
- Villain
- Therapist
- Caregiver
- Dominant
- Submissive
- Companion
- Horror Entity
- Fantasy NPC

**User Presets:**
- Save your own templates
- Share with community (optional)
- Clone and remix existing presets

### 🌐 Advanced Features

#### **Kinks & Fetishes Database**
- Import from online databases
- Auto-scrape from badgirlsbible.com
- Categorized lists
- Easy tagging and selection

#### **Version Control**
- Track card versions
- Rollback to previous versions
- Compare changes
- Duplicate and remix cards

## Usage

### Opening the Character Builder

1. Launch AutoCoder
2. Go to **Tools → Character Builder** (Ctrl+Shift+C)
3. The Character Builder window will open

### Creating a New Character

#### **Method 1: Using the Wizard**
1. Click **Tools → Guided Wizard**
2. Follow the step-by-step prompts:
   - Enter basic information
   - Configure personality sliders
   - Set behavior rules
   - Add example dialogues
3. Click **Finish** to create the card

#### **Method 2: Manual Creation**
1. Click **File → New Card**
2. Navigate through the tabs:
   - **📝 Basic Info**: Name, description, personality
   - **🎭 Personality**: Sliders, traits, behavior rules
   - **🧠 Memory & Lore**: Character history and world lore
   - **💬 Dialogues**: Example conversations
   - **🌍 World Builder**: Create the setting
   - **🖼️ Portrait**: Add character image
3. Save your card when finished

### Importing Existing Cards

1. Click **File → Import Card**
2. Select a card file:
   - JSON files from SillyTavern or other platforms
   - PNG cards with embedded JSON
3. The card will be loaded and ready to edit

### Exporting Your Card

1. Click **File → Export Card**
2. Choose export format:
   - **JSON**: For use with SillyTavern and compatible platforms
   - **PNG**: Image card with embedded JSON data
   - **TXT**: Plain text prompt for testing
3. Select destination and click **Export**

### Validating Your Card

1. Click **Tools → Validate Card** (or the validation button in the toolbar)
2. Review the validation report:
   - Check for errors (red)
   - Address warnings (yellow)
   - Confirm validation passes (green)
3. Make necessary adjustments

### Using Presets

1. Click **Presets → Load Preset**
2. Choose from built-in or user presets
3. Customize as needed
4. Save as a new preset with **Presets → Save as Preset**

## Architecture

### Core Components

#### **Data Model** (`card_data.h/cpp`)
- `CharacterCardData`: Main card data structure
- `PersonalitySliders`: Personality trait values
- `IntelligenceControls`: Intelligence settings
- `BehaviorRules`: Behavior configuration
- `MemoryLore`: Memory and lore data
- `WorldInfo`: World building information

#### **Validation** (`card_validator.h/cpp`)
- `CardValidator`: Validates cards for errors and warnings
- Token estimation
- Conflict detection
- Redundancy checking

#### **Import/Export** (`card_importer.h/cpp`)
- `CardImporter`: Import from various formats
- Format auto-detection
- PNG card parsing
- Multi-platform support

#### **Web Integration** (`web_scraper.h/cpp`)
- `WebScraper`: Fetch data from web
- Kinks/fetishes database import
- HTML parsing and cleaning

#### **GUI Components**
- `CharacterBuilderWindow`: Main window
- `BasicInfoPanel`: Basic character information
- `PersonalityPanel`: Personality and behavior
- `MemoryLorePanel`: Memory and lore management
- `DialoguePanel`: Example dialogues
- `WorldBuilderPanel`: World building
- `PortraitPanel`: Image management
- `ExportDialog`: Export configuration
- `WizardDialog`: Guided wizard interface

## File Format

Character cards are stored in JSON format compatible with SillyTavern:

```json
{
  "name": "Character Name",
  "description": "Physical description...",
  "personality": "Personality traits...",
  "scenario": "Current situation...",
  "first_mes": "Greeting message...",
  "mes_example": "{{user}}: Hello\n{{char}}: Hi there!",
  "creator": "Author Name",
  "tags": ["tag1", "tag2"],
  "extensions": {
    "autocoder": {
      "version": "1.0.0",
      "personality_sliders": {...},
      "intelligence_controls": {...},
      "behavior_rules": {...},
      "memory_lore": {...},
      "world_info": {...}
    }
  }
}
```

## Tips & Best Practices

### Creating Better Characters

1. **Be Specific**: Detailed descriptions create more consistent characters
2. **Balance Sliders**: Extreme values can lead to unpredictable behavior
3. **Use Examples**: Quality example dialogues significantly improve character voice
4. **Test Thoroughly**: Use the validator and test with your AI platform
5. **Iterate**: Don't be afraid to refine and adjust based on testing

### Avoiding Common Issues

- **Token Limits**: Keep total prompt under 6000 tokens for best performance
- **Conflicting Rules**: Don't combine contradictory behavior rules
- **Redundancy**: Avoid repeating the same information in multiple fields
- **Vague Descriptions**: Be specific about personality and behavior

### Optimization

- **Simple Mode**: Use for quick, consistent results
- **Advanced Mode**: Use for fine-tuning and edge cases
- **Presets**: Start with presets and customize
- **Version Control**: Save multiple versions during development

## Troubleshooting

### Card Won't Load in SillyTavern
- Validate the card for errors
- Check JSON formatting
- Ensure all required fields are present
- Try exporting as a fresh JSON file

### Character Behavior is Inconsistent
- Review personality sliders for conflicts
- Check behavior rules
- Add more example dialogues
- Ensure description and personality align

### Import Fails
- Verify the file format is supported
- Check if file is corrupted
- Try manual JSON editing
- Report issue with error message

## Future Enhancements

Planned features for future releases:
- AI-assisted card generation
- Behavior simulation mode
- Community card sharing
- Regex-based advanced rules
- Conditional responses
- Mood state tracking
- Emotional decay system
- Relationship progression memory
- Integration with more platforms

## Support

For issues, feature requests, or questions:
- GitHub Issues: [autocoder/issues](https://github.com/yourusername/autocoder/issues)
- Documentation: [Character Builder Wiki](https://github.com/yourusername/autocoder/wiki/Character-Builder)
- Community: [Discussions](https://github.com/yourusername/autocoder/discussions)

## License

The Character Card Builder is part of AutoCoder and is licensed under the MIT License.

---

**Made with ❤️ for the AI roleplay community**
