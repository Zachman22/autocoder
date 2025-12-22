# Quick Start: Generating AutoCoder Installers

## Overview

AutoCoder provides **two methods** for generating installers:

1. **Automated (Recommended)**: GitHub Actions automatically builds installers when you push a version tag
2. **Manual**: Build installers locally on your machine

## Method 1: Automated via GitHub Actions (Recommended)

### What Gets Built Automatically

When you push a version tag, GitHub Actions automatically builds:
- ✅ **Linux DEB** package (Ubuntu/Debian)
- ✅ **Linux RPM** package (Fedora/RHEL/CentOS)
- ✅ **macOS DMG** package
- ✅ **Windows NSIS** installer (.exe)

### How to Trigger Automated Build

```bash
# 1. Create and push a version tag
git tag -a v1.0.0 -m "Release version 1.0.0"
git push origin v1.0.0

# 2. GitHub Actions automatically:
#    - Detects the new tag
#    - Builds for all platforms
#    - Creates installers
#    - Publishes to GitHub Releases

# 3. Download installers from:
#    https://github.com/yourusername/autocoder/releases
```

### Monitoring the Build

1. Go to: `https://github.com/yourusername/autocoder/actions`
2. Watch the "Build Release Installers" workflow
3. Wait for completion (~15-30 minutes for all platforms)
4. Installers appear at: `https://github.com/yourusername/autocoder/releases`

## Method 2: Build Locally (Manual)

### Prerequisites

You must have these installed:

**All Platforms:**
- CMake 3.15+
- C++17 compiler
- Qt6 (with development files)
- OpenSSL
- libcurl

**Linux Only:**
- `dpkg-dev` (for DEB)
- `rpm-build` (for RPM)

**Windows Only:**
- NSIS (Nullsoft Scriptable Install System)

**macOS Only:**
- Xcode Command Line Tools

### Quick Local Build

```bash
# One command to build installers
./scripts/package-installers.sh
```

This will:
- Detect your platform
- Build the project
- Generate appropriate installer(s)
- Output location: `build-release/`

### Platform-Specific Output

**Linux:**
```
build-release/AutoCoder-1.0.0-Linux.deb
build-release/AutoCoder-1.0.0-Linux.rpm
```

**macOS:**
```
build-release/AutoCoder-1.0.0-Darwin.dmg
```

**Windows:**
```
build-release/AutoCoder-1.0.0-win64.exe
```

## Installation

### Linux (DEB)

```bash
sudo dpkg -i AutoCoder-1.0.0-Linux.deb
sudo apt-get install -f  # Fix dependencies if needed
```

### Linux (RPM)

```bash
sudo dnf install AutoCoder-1.0.0-Linux.rpm
# or
sudo rpm -i AutoCoder-1.0.0-Linux.rpm
```

### macOS

1. Double-click `AutoCoder-1.0.0-Darwin.dmg`
2. Drag **AutoCoder.app** to **Applications**
3. Launch from Applications

### Windows

1. Double-click `AutoCoder-1.0.0-win64.exe`
2. Follow installation wizard
3. Launch from Start Menu

## Common Issues

### Qt6 Not Found

**Linux:**
```bash
sudo apt install qt6-base-dev libqt6websockets6-dev
```

**macOS:**
```bash
brew install qt@6
export CMAKE_PREFIX_PATH="$(brew --prefix qt@6)"
```

**Windows:**
```powershell
# Use vcpkg
vcpkg install qt6:x64-windows
```

### NSIS Not Found (Windows)

```powershell
# Install NSIS
choco install nsis
# or download from: https://nsis.sourceforge.io/Download
```

### Build Fails

```bash
# Clean and retry
rm -rf build-release
./scripts/package-installers.sh
```

## Testing Installers

### Before Distribution

Always test installers on clean systems:

**Linux (Docker):**
```bash
# Test DEB
docker run -it --rm -v $(pwd):/pkg ubuntu:22.04 bash
apt update && apt install -y /pkg/AutoCoder-1.0.0-Linux.deb

# Test RPM
docker run -it --rm -v $(pwd):/pkg fedora:latest bash
dnf install -y /pkg/AutoCoder-1.0.0-Linux.rpm
```

**Windows (Silent Install):**
```powershell
AutoCoder-1.0.0-win64.exe /S /D=C:\TestInstall
C:\TestInstall\autocoder.exe --version
```

**macOS:**
```bash
hdiutil attach AutoCoder-1.0.0-Darwin.dmg
# Test app
hdiutil detach /Volumes/AutoCoder
```

## Version Numbering

Follow [Semantic Versioning](https://semver.org/):

- **v1.0.0** - Major release (breaking changes)
- **v1.1.0** - Minor release (new features)
- **v1.1.1** - Patch release (bug fixes)

## Distribution Checklist

Before publishing installers:

- [ ] Test on clean systems
- [ ] Verify all dependencies are bundled
- [ ] Check installer size is reasonable
- [ ] Test installation and uninstallation
- [ ] Verify application launches correctly
- [ ] Run smoke tests on installed version
- [ ] Update release notes
- [ ] Create checksums (SHA256) for downloads

## Getting Help

- **Full Documentation**: See [PACKAGING.md](PACKAGING.md)
- **Release Process**: See [RELEASE.md](RELEASE.md)
- **Build Instructions**: See [BUILD.md](BUILD.md)
- **Issues**: https://github.com/yourusername/autocoder/issues

## Quick Reference

| Platform | Command | Output |
|----------|---------|--------|
| **Auto** | `git push origin v1.0.0` | All platforms via CI |
| **Linux** | `./scripts/package-installers.sh` | `.deb` and `.rpm` |
| **macOS** | `./scripts/package-installers.sh` | `.dmg` |
| **Windows** | `.\scripts\package-installers.bat` | `.exe` |

## Summary

**For releases**: Use automated GitHub Actions (push a tag)

**For testing**: Build locally with `./scripts/package-installers.sh`

**For users**: Download from [GitHub Releases](https://github.com/yourusername/autocoder/releases)

---

**That's it!** You now have professional installers for all platforms. 🚀
