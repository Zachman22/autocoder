# AutoCoder Packaging Guide

This guide explains how to create installer packages for AutoCoder on different platforms.

## Table of Contents

- [Prerequisites](#prerequisites)
- [Automated Packaging](#automated-packaging)
- [Manual Packaging](#manual-packaging)
- [GitHub Actions Release](#github-actions-release)
- [Platform-Specific Details](#platform-specific-details)

## Prerequisites

### All Platforms

- CMake 3.15+
- C++ compiler with C++17 support
- Qt6 with development files
- OpenSSL
- libcurl

### Linux-Specific

For DEB packages:
- `dpkg-dev` or `build-essential`

For RPM packages:
- `rpm-build` or `rpmbuild`

```bash
# Ubuntu/Debian
sudo apt install build-essential cmake qt6-base-dev libssl-dev libcurl4-openssl-dev rpm

# Fedora/RHEL
sudo dnf install cmake gcc-c++ qt6-qtbase-devel openssl-devel libcurl-devel rpm-build
```

### macOS-Specific

```bash
brew install cmake qt@6 openssl@3 curl
```

### Windows-Specific

- NSIS (Nullsoft Scriptable Install System) for creating `.exe` installers
- Visual Studio 2019+ or MinGW-w64

Install NSIS:
- Download from: https://nsis.sourceforge.io/Download
- Or via Chocolatey: `choco install nsis`

## Automated Packaging

The easiest way to create installers:

```bash
./scripts/package-installers.sh
```

This script will:
1. Detect your platform
2. Check for required tools
3. Build the project in Release mode
4. Generate appropriate installer packages

Output packages will be in `build-release/` directory.

## Manual Packaging

### Linux (DEB)

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_INSTALLER=ON
cmake --build . -j$(nproc)
cpack -G DEB
```

Output: `AutoCoder-1.0.0-Linux.deb`

### Linux (RPM)

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_INSTALLER=ON
cmake --build . -j$(nproc)
cpack -G RPM
```

Output: `AutoCoder-1.0.0-Linux.rpm`

### macOS (DMG)

```bash
export CMAKE_PREFIX_PATH="$(brew --prefix qt@6)"
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_INSTALLER=ON
cmake --build . -j$(sysctl -n hw.ncpu)
cpack -G DragNDrop
```

Output: `AutoCoder-1.0.0-Darwin.dmg`

### Windows (NSIS)

```powershell
# Using vcpkg for dependencies
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=path\to\vcpkg\scripts\buildsystems\vcpkg.cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_INSTALLER=ON
cmake --build . --config Release
cpack -C Release -G NSIS
```

Output: `AutoCoder-1.0.0-win64.exe`

## GitHub Actions Release

AutoCoder includes a GitHub Actions workflow that automatically builds installers for all platforms when you push a git tag.

### Creating a Release

1. **Tag the release:**

```bash
git tag -a v1.0.0 -m "Release version 1.0.0"
git push origin v1.0.0
```

2. **GitHub Actions will automatically:**
   - Build for Linux (Ubuntu 22.04)
   - Build for macOS (latest)
   - Build for Windows (latest)
   - Generate DEB, RPM, DMG, and NSIS packages
   - Create a GitHub Release with all packages attached

3. **Download installers from:**
   - Go to: https://github.com/yourusername/autocoder/releases
   - Find the release version
   - Download the appropriate installer for your platform

### Manual Workflow Trigger

You can also trigger the workflow manually:

1. Go to GitHub repository → Actions
2. Select "Build Release Installers"
3. Click "Run workflow"
4. Choose the branch
5. Click "Run workflow"

## Platform-Specific Details

### Linux DEB Package

**Package Information:**
- Package name: `autocoder`
- Installed to: `/usr/local/bin/autocoder`
- Desktop entry: `/usr/share/applications/autocoder.desktop`
- Icon: `/usr/share/pixmaps/autocoder.png`

**Installation:**
```bash
sudo dpkg -i AutoCoder-1.0.0-Linux.deb
sudo apt-get install -f  # Install dependencies
```

**Uninstallation:**
```bash
sudo apt remove autocoder
```

### Linux RPM Package

**Package Information:**
- Package name: `autocoder`
- Installed to: `/usr/local/bin/autocoder`

**Installation:**
```bash
sudo rpm -i AutoCoder-1.0.0-Linux.rpm
# or
sudo dnf install AutoCoder-1.0.0-Linux.rpm
```

**Uninstallation:**
```bash
sudo rpm -e autocoder
# or
sudo dnf remove autocoder
```

### macOS DMG

**Installation:**
1. Open the DMG file
2. Drag AutoCoder.app to Applications folder
3. Launch from Applications or Launchpad

**Uninstallation:**
```bash
rm -rf /Applications/AutoCoder.app
```

### Windows NSIS Installer

**Installation:**
1. Run `AutoCoder-1.0.0-win64.exe`
2. Follow the installation wizard
3. Choose installation directory (default: `C:\Program Files\AutoCoder`)
4. Choose Start Menu folder
5. Click Install

**Features:**
- Creates Start Menu shortcuts
- Adds to Windows PATH (optional)
- Creates desktop shortcut (optional)
- Uninstaller included

**Uninstallation:**
- Control Panel → Programs → Uninstall AutoCoder
- Or run `C:\Program Files\AutoCoder\Uninstall.exe`

## Customizing Installers

### DEB Package Customization

Edit `CMakeLists.txt` and modify:

```cmake
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Your Name <email@example.com>")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "qt6-base, libssl3, libcurl4")
```

### RPM Package Customization

Edit `CMakeLists.txt` and modify:

```cmake
set(CPACK_RPM_PACKAGE_GROUP "Development/Tools")
set(CPACK_RPM_PACKAGE_REQUIRES "qt6-qtbase, openssl, libcurl")
```

### macOS DMG Customization

```cmake
set(CPACK_DMG_VOLUME_NAME "AutoCoder")
set(CPACK_DMG_FORMAT "UDBZ")
set(CPACK_DMG_BACKGROUND_IMAGE "${CMAKE_SOURCE_DIR}/resources/dmg-background.png")
```

### Windows NSIS Customization

```cmake
set(CPACK_NSIS_DISPLAY_NAME "AutoCoder")
set(CPACK_NSIS_HELP_LINK "https://autocoder.dev")
set(CPACK_NSIS_URL_INFO_ABOUT "https://autocoder.dev")
set(CPACK_NSIS_CONTACT "support@autocoder.dev")
set(CPACK_NSIS_MODIFY_PATH ON)
```

## Testing Installers

### Linux

```bash
# Test DEB installation in Docker
docker run -it --rm -v $(pwd):/packages ubuntu:22.04 bash
apt update && apt install -y /packages/AutoCoder-1.0.0-Linux.deb
autocoder --version

# Test RPM installation
docker run -it --rm -v $(pwd):/packages fedora:latest bash
dnf install -y /packages/AutoCoder-1.0.0-Linux.rpm
autocoder --version
```

### macOS

```bash
# Mount DMG
hdiutil attach AutoCoder-1.0.0-Darwin.dmg

# Verify app signature (if signed)
codesign -vv /Volumes/AutoCoder/AutoCoder.app

# Unmount
hdiutil detach /Volumes/AutoCoder
```

### Windows

```powershell
# Silent installation (for testing)
AutoCoder-1.0.0-win64.exe /S /D=C:\TestInstall

# Verify installation
C:\TestInstall\autocoder.exe --version

# Silent uninstallation
C:\TestInstall\Uninstall.exe /S
```

## Code Signing

### macOS

```bash
# Sign the application
codesign --deep --force --sign "Developer ID Application: Your Name" AutoCoder.app

# Verify signature
codesign --verify --verbose AutoCoder.app

# Notarize (required for macOS 10.15+)
xcrun notarytool submit AutoCoder-1.0.0-Darwin.dmg --keychain-profile "notary-profile" --wait
```

### Windows

```powershell
# Sign with signtool (requires code signing certificate)
signtool sign /f certificate.pfx /p password /tr http://timestamp.digicert.com /td sha256 /fd sha256 AutoCoder-1.0.0-win64.exe

# Verify signature
signtool verify /pa AutoCoder-1.0.0-win64.exe
```

## Troubleshooting

### CPack Not Found

```bash
# Ubuntu/Debian
sudo apt install cmake

# The cpack command is included with cmake
```

### Qt6 Not Found

```bash
# Set CMAKE_PREFIX_PATH
export CMAKE_PREFIX_PATH="/path/to/qt6"

# Or specify in cmake command
cmake .. -DQt6_DIR="/path/to/qt6/lib/cmake/Qt6"
```

### NSIS Not Found (Windows)

```powershell
# Install NSIS
choco install nsis

# Or download from: https://nsis.sourceforge.io/Download
# Add to PATH: C:\Program Files (x86)\NSIS
```

### Permission Denied

```bash
# Linux/macOS
chmod +x scripts/package-installers.sh

# Or run with bash
bash scripts/package-installers.sh
```

## Continuous Integration

The `.github/workflows/build-release.yml` workflow handles automated builds. You can also add additional CI platforms:

### GitLab CI

Create `.gitlab-ci.yml`:

```yaml
build:linux:
  image: ubuntu:22.04
  script:
    - apt update && apt install -y cmake build-essential qt6-base-dev libssl-dev libcurl4-openssl-dev rpm
    - ./scripts/package-installers.sh
  artifacts:
    paths:
      - build-release/*.deb
      - build-release/*.rpm
```

### Jenkins

```groovy
pipeline {
    agent any
    stages {
        stage('Build Installers') {
            parallel {
                stage('Linux') {
                    steps {
                        sh './scripts/package-installers.sh'
                    }
                }
                stage('Windows') {
                    agent { label 'windows' }
                    steps {
                        bat 'scripts\\package-installers.bat'
                    }
                }
            }
        }
    }
}
```

## Support

For packaging issues:
- Check [GitHub Issues](https://github.com/yourusername/autocoder/issues)
- Ask in [Discussions](https://github.com/yourusername/autocoder/discussions)
- Email: support@autocoder.dev
