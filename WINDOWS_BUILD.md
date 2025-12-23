# Building AutoCoder on Windows

Quick guide to build the Windows installer with the app menu integration fixes.

## Prerequisites

- Windows 10/11
- Visual Studio 2022 (Community Edition or higher) with C++ tools
- Git
- PowerShell

## Quick Build (Automated)

```powershell
# Run the automated build script
.\build-windows.ps1
```

This script will:
1. Install vcpkg if not present
2. Install Qt6 and dependencies (takes 30-60 minutes first time)
3. Configure CMake with proper toolchain
4. Build the project
5. Generate installer (.exe or .zip)

## Manual Build

### 1. Install vcpkg

```powershell
git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
cd C:\vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
```

### 2. Install Dependencies

```powershell
cd C:\vcpkg
.\vcpkg install qt6-base:x64-windows
.\vcpkg install qt6-websockets:x64-windows
.\vcpkg install openssl:x64-windows
.\vcpkg install curl:x64-windows
```

**Note:** This step takes 30-60 minutes as Qt6 is compiled from source.

### 3. Build AutoCoder

```powershell
cd C:\Users\YourUser\path\to\autocoder
mkdir build
cd build

# Configure
cmake .. `
    -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake `
    -DCMAKE_BUILD_TYPE=Release `
    -DBUILD_INSTALLER=ON `
    -G "Visual Studio 17 2022" `
    -A x64

# Build
cmake --build . --config Release -j
```

### 4. Create Installer

**Option A: NSIS Installer (recommended)**

Install NSIS first:
```powershell
# Using Chocolatey
choco install nsis

# Or download from: https://nsis.sourceforge.io/Download
```

Then create installer:
```powershell
cd build
cpack -G NSIS -C Release
```

**Option B: ZIP Package (no NSIS required)**

```powershell
cd build
cpack -G ZIP -C Release
```

## Output

The installer will be created in the `build/` directory:
- NSIS: `AutoCoder-1.0.0-win64.exe` (installer)
- ZIP: `AutoCoder-1.0.0-win64.zip` (portable)

## Installation

### Using NSIS Installer
1. Run `AutoCoder-1.0.0-win64.exe`
2. Follow installation wizard
3. Launch from Start Menu

### Using ZIP Package
1. Extract to desired location (e.g., `C:\Program Files\AutoCoder`)
2. Run `autocoder.exe`

## Troubleshooting

### Qt6 Not Found
Make sure vcpkg toolchain file is specified:
```powershell
-DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake
```

### Build Fails
- Ensure Visual Studio 2022 with C++ tools is installed
- Make sure vcpkg integration is installed: `.\vcpkg integrate install`
- Try cleaning build directory: `Remove-Item -Recurse build`

### NSIS Not Found
Either:
1. Install NSIS and add to PATH
2. Use ZIP package instead: `cpack -G ZIP -C Release`

## What's New in This Build

✓ App menu integration (Linux/macOS)
✓ Desktop entry and icon files
✓ Post-install scripts for proper registration
✓ Complete installation process

## Development Build (Debug)

For development with debugging:
```powershell
cmake .. `
    -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake `
    -DCMAKE_BUILD_TYPE=Debug `
    -DBUILD_TESTS=ON `
    -G "Visual Studio 17 2022"

cmake --build . --config Debug
```

## Support

For build issues, check:
- [GitHub Issues](https://github.com/Zachman22/autocoder/issues)
- [PACKAGING.md](PACKAGING.md) for more details
