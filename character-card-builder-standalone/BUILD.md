# Building Character Card Builder

This guide provides detailed instructions for building Character Card Builder from source on different platforms.

## Table of Contents
- [System Requirements](#system-requirements)
- [Dependencies](#dependencies)
- [Building on Linux](#building-on-linux)
- [Building on macOS](#building-on-macos)
- [Building on Windows](#building-on-windows)
- [Creating Installers](#creating-installers)
- [Troubleshooting](#troubleshooting)

## System Requirements

### Minimum Requirements
- **CPU**: x64 processor, 2+ cores
- **RAM**: 2 GB minimum, 4 GB recommended
- **Disk**: 500 MB for application + dependencies
- **OS**:
  - Linux: Ubuntu 20.04+, Fedora 35+, or equivalent
  - macOS: 11.0 (Big Sur) or later
  - Windows: Windows 10 or later

### Build Requirements
- **CMake**: 3.15 or higher
- **C++ Compiler**:
  - GCC 7+ or Clang 6+ (Linux/macOS)
  - MSVC 2019+ or MinGW-w64 (Windows)
- **Qt**: 6.2 or higher
- **OpenSSL**: 1.1.1 or higher
- **libcurl**: 7.68.0 or higher

## Dependencies

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    cmake \
    git \
    qt6-base-dev \
    qt6-base-dev-tools \
    libqt6network6 \
    libssl-dev \
    libcurl4-openssl-dev \
    pkg-config
```

### Fedora/RHEL
```bash
sudo dnf install -y \
    gcc-c++ \
    cmake \
    git \
    qt6-qtbase-devel \
    openssl-devel \
    libcurl-devel \
    pkg-config
```

### Arch Linux
```bash
sudo pacman -S --needed \
    base-devel \
    cmake \
    git \
    qt6-base \
    openssl \
    curl
```

### macOS (Homebrew)
```bash
brew install cmake qt@6 openssl curl
```

### Windows

**Option 1: vcpkg (Recommended)**
```powershell
# Install vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# Install dependencies
.\vcpkg install qt6 openssl curl
```

**Option 2: Manual Installation**
- Download Qt6 from https://www.qt.io/download
- Download OpenSSL from https://slproweb.com/products/Win32OpenSSL.html
- Download libcurl from https://curl.se/download.html

## Building on Linux

### Standard Build
```bash
# Clone the repository
git clone https://github.com/yourusername/character-card-builder.git
cd character-card-builder

# Create build directory
mkdir build && cd build

# Configure
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/usr/local

# Build (use all CPU cores)
cmake --build . -j$(nproc)

# Install (optional)
sudo cmake --install .
```

### Debug Build
```bash
mkdir build-debug && cd build-debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . -j$(nproc)
```

### Custom Qt Installation
```bash
# If Qt is installed in a non-standard location
cmake .. \
    -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/gcc_64 \
    -DCMAKE_BUILD_TYPE=Release
```

## Building on macOS

### Standard Build
```bash
# Clone the repository
git clone https://github.com/yourusername/character-card-builder.git
cd character-card-builder

# Create build directory
mkdir build && cd build

# Configure (with Homebrew Qt)
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_PREFIX_PATH=$(brew --prefix qt@6) \
    -DOPENSSL_ROOT_DIR=$(brew --prefix openssl@3)

# Build
cmake --build . -j$(sysctl -n hw.ncpu)

# Create macOS app bundle
cmake --build . --target install
```

### Creating .app Bundle
```bash
# After building
macdeployqt character-card-builder.app -dmg
```

## Building on Windows

### Using Visual Studio (MSVC)

**Prerequisites:**
- Visual Studio 2019 or later
- Qt6 (via online installer or vcpkg)
- CMake (via Visual Studio Installer or standalone)

**Build Steps:**
```powershell
# Clone the repository
git clone https://github.com/yourusername/character-card-builder.git
cd character-card-builder

# Create build directory
mkdir build
cd build

# Configure (if using vcpkg)
cmake .. `
    -DCMAKE_TOOLCHAIN_FILE="C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake" `
    -G "Visual Studio 17 2022" `
    -A x64

# Or configure (if Qt is manually installed)
cmake .. `
    -DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/msvc2019_64" `
    -G "Visual Studio 17 2022" `
    -A x64

# Build
cmake --build . --config Release

# Run
.\Release\character-card-builder.exe
```

### Using MinGW
```powershell
# In MinGW shell
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build . -j%NUMBER_OF_PROCESSORS%
```

## Creating Installers

### Linux (.deb package)
```bash
cd build
cpack -G DEB

# Output: CharacterCardBuilder-1.0.0-Linux.deb
```

### Linux (.rpm package)
```bash
cd build
cpack -G RPM

# Output: CharacterCardBuilder-1.0.0-Linux.rpm
```

### macOS (.dmg)
```bash
cd build
cpack -G DragNDrop

# Output: CharacterCardBuilder-1.0.0-Darwin.dmg
```

### Windows (.exe installer)
```powershell
cd build
cpack -G NSIS -C Release

# Output: CharacterCardBuilder-1.0.0-win64.exe
```

### Cross-platform Archive
```bash
cd build
cpack -G TGZ  # or ZIP for Windows

# Output: CharacterCardBuilder-1.0.0-Linux.tar.gz
```

## Build Options

### CMake Options

```bash
# Disable installer creation
cmake .. -DBUILD_INSTALLER=OFF

# Custom installation prefix
cmake .. -DCMAKE_INSTALL_PREFIX=/opt/character-card-builder

# Verbose build output
cmake --build . --verbose

# Clean build
cmake --build . --target clean
```

## Troubleshooting

### Qt6 Not Found
```bash
# Set Qt6 path explicitly
export CMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/gcc_64
cmake ..
```

### OpenSSL Not Found (macOS)
```bash
# Use Homebrew OpenSSL
export OPENSSL_ROOT_DIR=$(brew --prefix openssl@3)
cmake ..
```

### Missing Dependencies (Linux)
```bash
# Check what libraries are missing
ldd ./character-card-builder

# Install missing libraries
sudo apt-get install -f
```

### CURL Not Found (Windows)
```powershell
# Add to CMake command
-DCURL_INCLUDE_DIR="C:/path/to/curl/include" `
-DCURL_LIBRARY="C:/path/to/curl/lib/libcurl.lib"
```

### Compilation Errors

**Error: "Qt6Core not found"**
```bash
# Solution: Install qt6-base-dev package or set CMAKE_PREFIX_PATH
```

**Error: "OpenSSL not found"**
```bash
# Solution: Install libssl-dev (Debian/Ubuntu) or openssl-devel (Fedora)
```

**Error: "curl/curl.h: No such file"**
```bash
# Solution: Install libcurl4-openssl-dev
```

### Runtime Errors

**Error: "error while loading shared libraries: libQt6Core.so.6"**
```bash
# Solution: Add Qt lib directory to LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/path/to/Qt/6.x.x/gcc_64/lib:$LD_LIBRARY_PATH
```

**Error: "DLL load failed" (Windows)**
```powershell
# Solution: Copy Qt DLLs to application directory or use windeployqt
windeployqt.exe character-card-builder.exe
```

## Performance Optimization

### Link-Time Optimization (LTO)
```bash
cmake .. -DCMAKE_INTERPROCEDURAL_OPTIMIZATION=ON
```

### Strip Debug Symbols (Release)
```bash
strip character-card-builder  # Linux/macOS
```

## Development Build

For faster iteration during development:

```bash
# Use ninja for faster builds
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug
ninja

# Or use ccache for incremental builds
cmake .. -DCMAKE_CXX_COMPILER_LAUNCHER=ccache
```

## Continuous Integration

Example GitHub Actions workflow:

```yaml
name: Build

on: [push, pull_request]

jobs:
  build-linux:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - name: Install dependencies
        run: |
          sudo apt-get update
          sudo apt-get install -y qt6-base-dev libssl-dev libcurl4-openssl-dev
      - name: Build
        run: |
          mkdir build && cd build
          cmake ..
          cmake --build . -j$(nproc)
```

## Support

If you encounter build issues not covered here:
- Check [GitHub Issues](https://github.com/yourusername/character-card-builder/issues)
- Join our [Discord](https://discord.gg/charactercardbuilder)
- Email: build-support@charactercardbuilder.app

---

**Happy Building!** 🎉
