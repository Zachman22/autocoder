# Building AutoCoder

This document provides detailed instructions for building AutoCoder from source on various platforms.

## Table of Contents

- [Prerequisites](#prerequisites)
- [Linux](#linux)
- [macOS](#macos)
- [Windows](#windows)
- [Build Options](#build-options)
- [Troubleshooting](#troubleshooting)

## Prerequisites

### Required Dependencies

- **CMake** 3.15 or higher
- **C++ Compiler** with C++17 support:
  - GCC 7+ (Linux)
  - Clang 5+ (macOS/Linux)
  - MSVC 2019+ (Windows)
- **Qt6** (Core, Widgets, Network, WebSockets, Gui)
- **OpenSSL** 1.1.1 or higher
- **libcurl** 7.68 or higher

### Optional Dependencies

- **Doxygen** (for documentation generation)
- **Graphviz** (for documentation graphs)

## Linux

### Ubuntu/Debian

```bash
# Install dependencies
sudo apt update
sudo apt install -y cmake build-essential qt6-base-dev libqt6websockets6-dev \
    libssl-dev libcurl4-openssl-dev git

# Clone repository
git clone https://github.com/yourusername/autocoder.git
cd autocoder

# Build
mkdir build && cd build
cmake ..
cmake --build . -j$(nproc)

# Install (optional)
sudo cmake --install .

# Run
./autocoder
```

### Fedora/RHEL/CentOS

```bash
# Install dependencies
sudo dnf install -y cmake gcc-c++ qt6-qtbase-devel qt6-qtwebsockets-devel \
    openssl-devel libcurl-devel git

# Clone, build, and install same as Ubuntu
```

### Arch Linux

```bash
# Install dependencies
sudo pacman -S cmake gcc qt6-base qt6-websockets openssl curl git

# Clone, build, and install same as Ubuntu
```

## macOS

### Using Homebrew

```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install cmake qt@6 openssl@3 curl

# Set Qt6 path
export CMAKE_PREFIX_PATH="$(brew --prefix qt@6):$CMAKE_PREFIX_PATH"

# Clone repository
git clone https://github.com/yourusername/autocoder.git
cd autocoder

# Build
mkdir build && cd build
cmake ..
cmake --build . -j$(sysctl -n hw.ncpu)

# Create app bundle (optional)
make install

# Run
./autocoder
```

## Windows

### Using Visual Studio 2019/2022

```powershell
# Install vcpkg (package manager)
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install

# Install dependencies
.\vcpkg install qt6:x64-windows openssl:x64-windows curl:x64-windows

# Clone AutoCoder
cd ..
git clone https://github.com/yourusername/autocoder.git
cd autocoder

# Build
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=..\..\vcpkg\scripts\buildsystems\vcpkg.cmake
cmake --build . --config Release

# Run
Release\autocoder.exe
```

### Using MSYS2/MinGW

```bash
# In MSYS2 shell
pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-gcc \
    mingw-w64-x86_64-qt6 mingw-w64-x86_64-openssl \
    mingw-w64-x86_64-curl

# Clone and build
git clone https://github.com/yourusername/autocoder.git
cd autocoder
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
cmake --build .

# Run
./autocoder.exe
```

## Build Options

### CMake Configuration Options

```bash
# Enable/disable tests
cmake .. -DBUILD_TESTS=ON

# Enable/disable installer generation
cmake .. -DBUILD_INSTALLER=ON

# Set build type
cmake .. -DCMAKE_BUILD_TYPE=Release    # or Debug, RelWithDebInfo

# Set installation prefix
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local

# Enable specific compiler
cmake .. -DCMAKE_CXX_COMPILER=g++      # or clang++, cl.exe

# Combine multiple options
cmake .. -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=~/autocoder
```

### Build Types

- **Debug**: No optimization, debug symbols, assertions enabled
- **Release**: Full optimization, no debug symbols
- **RelWithDebInfo**: Optimization with debug symbols
- **MinSizeRel**: Optimization for minimal binary size

## Building Installer Packages

### Linux (DEB/RPM)

```bash
cd build
cmake .. -DBUILD_INSTALLER=ON
cmake --build .
cpack

# Outputs:
# - AutoCoder-1.0.0-Linux.deb
# - AutoCoder-1.0.0-Linux.rpm
```

### macOS (DMG)

```bash
cd build
cmake .. -DBUILD_INSTALLER=ON
cmake --build .
cpack

# Output: AutoCoder-1.0.0-Darwin.dmg
```

### Windows (NSIS)

```powershell
cd build
cmake .. -DBUILD_INSTALLER=ON
cmake --build . --config Release
cpack -C Release

# Output: AutoCoder-1.0.0-win64.exe
```

## Development Build

For active development with faster incremental builds:

```bash
mkdir build-dev && cd build-dev

# Configure with debug symbols and tests
cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DBUILD_TESTS=ON \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Build (use -j for parallel builds)
cmake --build . -j$(nproc)

# Run tests
ctest --output-on-failure
```

## Troubleshooting

### Qt6 Not Found

```bash
# Linux: Install qt6-base-dev
sudo apt install qt6-base-dev

# macOS: Set CMAKE_PREFIX_PATH
export CMAKE_PREFIX_PATH="$(brew --prefix qt@6)"

# Windows: Use vcpkg or set Qt6_DIR
cmake .. -DQt6_DIR="C:/Qt/6.5.0/msvc2019_64/lib/cmake/Qt6"
```

### OpenSSL Not Found

```bash
# Linux
sudo apt install libssl-dev

# macOS
brew install openssl@3
export OPENSSL_ROOT_DIR=$(brew --prefix openssl@3)

# Windows (vcpkg)
vcpkg install openssl:x64-windows
```

### CURL Not Found

```bash
# Linux
sudo apt install libcurl4-openssl-dev

# macOS
brew install curl

# Windows (vcpkg)
vcpkg install curl:x64-windows
```

### Compiler Errors

If you encounter C++17 related errors:

```bash
# Ensure your compiler supports C++17
g++ --version    # Should be 7.0+
clang++ --version    # Should be 5.0+

# Explicitly set C++ standard
cmake .. -DCMAKE_CXX_STANDARD=17
```

### Linking Errors

If you get undefined reference errors:

```bash
# Clean and rebuild
rm -rf build
mkdir build && cd build
cmake ..
cmake --build . -j$(nproc)
```

### Permission Denied on Install

```bash
# Use sudo for system-wide installation
sudo cmake --install .

# Or install to user directory
cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/.local
cmake --build .
cmake --install .
```

## Build Performance Tips

1. **Use Ninja** (faster than make):
   ```bash
   cmake .. -G Ninja
   ninja
   ```

2. **Use ccache** (cache compilation):
   ```bash
   sudo apt install ccache
   cmake .. -DCMAKE_CXX_COMPILER_LAUNCHER=ccache
   ```

3. **Parallel builds**:
   ```bash
   cmake --build . -j$(nproc)    # Linux
   cmake --build . -j$(sysctl -n hw.ncpu)    # macOS
   cmake --build . -j%NUMBER_OF_PROCESSORS%    # Windows
   ```

## Clean Build

```bash
# Remove build directory
rm -rf build

# Or use CMake clean
cd build
cmake --build . --target clean
```

## Cross-Compilation

### For ARM (Raspberry Pi)

```bash
# Install cross-compiler
sudo apt install g++-arm-linux-gnueabihf

# Configure for ARM
cmake .. \
    -DCMAKE_SYSTEM_NAME=Linux \
    -DCMAKE_SYSTEM_PROCESSOR=arm \
    -DCMAKE_C_COMPILER=arm-linux-gnueabihf-gcc \
    -DCMAKE_CXX_COMPILER=arm-linux-gnueabihf-g++

cmake --build .
```

## Getting Help

If you encounter issues not covered here:

1. Check the [GitHub Issues](https://github.com/yourusername/autocoder/issues)
2. Ask in [GitHub Discussions](https://github.com/yourusername/autocoder/discussions)
3. Email: support@autocoder.dev
