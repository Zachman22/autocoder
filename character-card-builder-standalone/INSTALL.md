# Installation Guide

## Quick Start

### Option 1: Automated Build (Linux/macOS)
```bash
./build.sh
cd build
./character-card-builder
```

### Option 2: Manual Build
```bash
mkdir build && cd build
cmake ..
cmake --build . -j$(nproc)
./character-card-builder
```

## System Installation

After building:
```bash
cd build
sudo cmake --install .
```

The application will be installed to `/usr/local/bin` by default.

## Creating Installers

### Linux (.deb)
```bash
cd build
cpack -G DEB
sudo dpkg -i CharacterCardBuilder-1.0.0-Linux.deb
```

### Linux (.rpm)
```bash
cd build
cpack -G RPM
sudo rpm -i CharacterCardBuilder-1.0.0-Linux.rpm
```

### macOS (.dmg)
```bash
cd build
cpack -G DragNDrop
# Open CharacterCardBuilder-1.0.0-Darwin.dmg and drag to Applications
```

### Windows (.exe)
```powershell
cd build
cpack -G NSIS
# Run CharacterCardBuilder-1.0.0-win64.exe
```

## Dependencies

All platforms require:
- Qt6 (6.2+)
- OpenSSL (1.1.1+)
- libcurl (7.68.0+)

See [BUILD.md](BUILD.md) for detailed dependency installation instructions.

## Uninstall

### From package:
```bash
# Debian/Ubuntu
sudo apt-get remove character-card-builder

# Fedora/RHEL
sudo dnf remove character-card-builder

# macOS
rm -rf /Applications/CharacterCardBuilder.app
```

### From source installation:
```bash
cd build
sudo xargs rm < install_manifest.txt
```

## Troubleshooting

See [BUILD.md](BUILD.md#troubleshooting) for common issues and solutions.
