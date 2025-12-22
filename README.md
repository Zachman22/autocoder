# AutoCoder - Self-Improving AI Code Generator

**AutoCoder** is a powerful, self-improving code generation platform powered by DeepSeeker 6.7b AI model. It features continuous debugging, multi-language support, an integrated compiler, GUI builder, and an elegant Qt-based interface.

## Features

### 🤖 AI-Powered Code Generation
- **DeepSeeker 6.7b Integration**: Leverage the power of DeepSeeker's 6.7 billion parameter model for intelligent code generation
- **Self-Improving**: Learns from feedback and continuously improves code quality
- **Multi-Language Support**: Generate code in all major programming languages (Python, JavaScript, C++, Java, Go, Rust, and more)
- **Context-Aware**: Understands project context and generates appropriate code

### 🐛 Continuous Debugger
- **Non-Stop Monitoring**: Continuously scans code for potential issues
- **Real-Time Analysis**: Detects errors, warnings, and code smells as you type
- **Auto-Fix**: Automatically suggests and applies fixes for common issues
- **Stack Tracing**: Advanced stack trace analysis and visualization
- **Variable Inspection**: Real-time variable monitoring and inspection

### 💬 Intelligent Chatbot
- **Natural Language Interface**: Describe what you want to code in plain English
- **Intent Understanding**: Parses your requests and generates appropriate code
- **Interactive Assistance**: Ask questions about your code and get instant answers
- **Code Explanations**: Get detailed explanations of how your code works

### 🔨 Integrated Compiler
- **Multi-Compiler Support**: GCC, Clang, and MSVC support
- **One-Click Compilation**: Compile and run your code with a single click
- **Build Management**: Advanced build configuration and management
- **Error Highlighting**: Compiler errors highlighted in the editor

### 🎨 GUI Builder
- **Visual Design**: Drag-and-drop interface for building GUIs
- **Framework Support**: Export to Qt, wxWidgets, GTK, or HTML
- **Code Generation**: Automatically generates GUI code in your target language
- **Widget Library**: Extensive library of pre-built widgets and components

### ✍️ Enhanced Spell Checker
- **Context-Aware**: Understands code context for better suggestions
- **Multi-Language**: Supports multiple natural languages
- **CamelCase Support**: Handles programming identifiers correctly
- **Custom Dictionaries**: Add project-specific terms and acronyms

### 🎯 Code Editor
- **Syntax Highlighting**: Beautiful syntax highlighting for all languages
- **Auto-Completion**: Intelligent code completion
- **Line Numbers**: Easy navigation with line numbers
- **Multiple Themes**: Choose from various color themes

## Installation

### Prerequisites
- CMake 3.15 or higher
- Qt6
- OpenSSL
- libcurl
- GCC/Clang (C++17 compatible)

### Building from Source

```bash
# Clone the repository
git clone https://github.com/yourusername/autocoder.git
cd autocoder

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build
cmake --build . -j$(nproc)

# Install (optional)
sudo cmake --install .
```

### Using Pre-Built Installers

Pre-built installers are automatically generated via GitHub Actions when releases are created:

1. **Download from GitHub Releases** (once available):
   - Go to the [Releases](https://github.com/yourusername/autocoder/releases) page
   - Download the installer for your platform:
     - **Windows**: `AutoCoder-1.0.0-win64.exe`
     - **Linux (DEB)**: `AutoCoder-1.0.0-Linux.deb`
     - **Linux (RPM)**: `AutoCoder-1.0.0-Linux.rpm`
     - **macOS**: `AutoCoder-1.0.0-Darwin.dmg`

2. **Or Build Installers Locally**:

   If you have all dependencies installed (Qt6, OpenSSL, libcurl), you can generate installers:

   ```bash
   # Automated packaging
   ./scripts/package-installers.sh

   # Installers will be in build-release/
   ```

   For detailed packaging instructions, see [PACKAGING.md](PACKAGING.md)

## Configuration

### API Key Setup

AutoCoder requires a DeepSeeker API key to function. You can obtain one from [DeepSeeker](https://deepseek.com).

1. Go to **Tools** → **Settings**
2. Navigate to the **AI** tab
3. Enter your DeepSeeker API key
4. Click **Test Connection** to verify
5. Click **Apply** to save

### Configuration File

AutoCoder stores its configuration in `config.json` in the application directory:

```json
{
  "theme": "dark",
  "font_size": 12,
  "auto_save": true,
  "api_endpoint": "https://api.deepseek.com/v1",
  "model": "deepseek-coder",
  "continuous_debug": true,
  "auto_fix": false
}
```

## Usage

### Generating Code with AI

1. Open the AI Chat panel (right side)
2. Type your request in natural language:
   ```
   Create a Python function that sorts a list of numbers using quicksort
   ```
3. Click **Generate Code** or press Enter
4. The generated code will appear in the editor

### Using the Continuous Debugger

1. Click **Build** → **Debug** or press F8
2. The debugger will continuously monitor your code
3. Issues are highlighted in real-time
4. Click on an issue to see suggested fixes
5. Enable **Auto-Fix** in settings for automatic corrections

### Building a GUI

1. Click **Tools** → **GUI Builder**
2. Drag widgets from the library to your canvas
3. Configure widget properties in the properties panel
4. Click **Export Code** to generate implementation
5. Choose your target framework (Qt, wxWidgets, etc.)

### Compiling Your Code

1. Write or generate your C++ code
2. Click **Build** → **Compile** or press F7
3. View compilation output in the Output panel
4. Click **Build** → **Run** or press F5 to execute

## Architecture

### Core Components

- **Application**: Main application controller
- **ConfigManager**: Configuration management
- **Logger**: Comprehensive logging system
- **PluginManager**: Extensibility through plugins

### AI Engine

- **DeepSeekerClient**: Interface to DeepSeeker API
- **ModelManager**: Model loading and management
- **InferenceEngine**: Local inference capabilities
- **SelfImprovement**: Learning and improvement system

### Debugging System

- **ContinuousDebugger**: Non-stop code analysis
- **BreakpointManager**: Breakpoint management
- **StackTracer**: Stack trace capture and analysis
- **VariableInspector**: Variable monitoring

### Code Generation

- **CodeGenerator**: Main code generation engine
- **LanguageDetector**: Programming language detection
- **SyntaxValidator**: Syntax checking and validation
- **MultiLanguageSupport**: Support for all major languages

## Development

### Project Structure

```
autocoder/
├── include/          # Header files
│   ├── core/
│   ├── ai_engine/
│   ├── debugger/
│   ├── chatbot/
│   ├── codegen/
│   ├── spellchecker/
│   ├── gui_maker/
│   ├── compiler/
│   └── gui/
├── src/              # Source files
│   ├── core/
│   ├── ai_engine/
│   ├── debugger/
│   ├── chatbot/
│   ├── codegen/
│   ├── spellchecker/
│   ├── gui_maker/
│   ├── compiler/
│   ├── gui/
│   └── main.cpp
├── tests/            # Unit tests
├── resources/        # Resources (icons, themes, templates)
├── docs/             # Documentation
├── scripts/          # Build and utility scripts
└── CMakeLists.txt    # CMake configuration
```

### Adding a New Language

To add support for a new programming language:

1. Create a new language handler class inheriting from `LanguageHandler`
2. Implement the required methods (format, validate, generate)
3. Register your handler with `MultiLanguageSupport`
4. Add language-specific templates to `resources/templates/`

### Creating Plugins

AutoCoder supports plugins for extending functionality:

```cpp
class MyPlugin : public AutoCoder::Core::Plugin {
public:
    std::string getName() const override { return "MyPlugin"; }
    std::string getVersion() const override { return "1.0.0"; }

    bool initialize() override {
        // Plugin initialization
        return true;
    }

    void shutdown() override {
        // Cleanup
    }
};
```

## Contributing

We welcome contributions! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

### Development Setup

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/amazing-feature`
3. Make your changes
4. Run tests: `ctest`
5. Commit: `git commit -m 'Add amazing feature'`
6. Push: `git push origin feature/amazing-feature`
7. Open a Pull Request

## Testing

```bash
# Build with tests
cmake -DBUILD_TESTS=ON ..
cmake --build .

# Run tests
ctest --output-on-failure
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- **DeepSeeker** for providing the powerful AI model
- **Qt Project** for the excellent GUI framework
- All contributors who have helped improve this project

## Support

- **Documentation**: [https://autocoder.readthedocs.io](https://autocoder.readthedocs.io)
- **Issues**: [GitHub Issues](https://github.com/yourusername/autocoder/issues)
- **Discussions**: [GitHub Discussions](https://github.com/yourusername/autocoder/discussions)
- **Email**: support@autocoder.dev

## Roadmap

- [ ] GPT-4 integration as alternative AI backend
- [ ] Cloud synchronization of projects
- [ ] Collaborative coding features
- [ ] Mobile app for code review
- [ ] Integration with popular IDEs (VS Code, IntelliJ)
- [ ] Docker container support
- [ ] CI/CD pipeline integration

## Version History

### v1.0.0 (Current)
- Initial release
- DeepSeeker 6.7b integration
- Continuous debugger
- Multi-language code generation
- GUI builder
- Integrated compiler
- Enhanced spell checker

---

**Made with ❤️ by the AutoCoder Team**
