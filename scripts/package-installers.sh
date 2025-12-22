#!/bin/bash
# Package installer generation script for AutoCoder

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_DIR/build-release"

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${GREEN}AutoCoder Installer Packaging Script${NC}"
echo "======================================"

# Check for required tools
check_tool() {
    if ! command -v "$1" &> /dev/null; then
        echo -e "${RED}Error: $1 is required but not installed.${NC}"
        return 1
    fi
    return 0
}

# Platform detection
PLATFORM="$(uname -s)"
case "$PLATFORM" in
    Linux*)
        OS="Linux"
        ;;
    Darwin*)
        OS="macOS"
        ;;
    MINGW*|MSYS*|CYGWIN*)
        OS="Windows"
        ;;
    *)
        echo -e "${RED}Unsupported platform: $PLATFORM${NC}"
        exit 1
        ;;
esac

echo -e "${BLUE}Detected platform: $OS${NC}"

# Check platform-specific requirements
if [ "$OS" = "Linux" ]; then
    check_tool cmake || exit 1
    check_tool cpack || exit 1
    check_tool rpmbuild || echo -e "${YELLOW}Warning: rpmbuild not found. RPM packages will not be generated.${NC}"
elif [ "$OS" = "macOS" ]; then
    check_tool cmake || exit 1
    check_tool cpack || exit 1
elif [ "$OS" = "Windows" ]; then
    check_tool cmake || exit 1
    check_tool cpack || exit 1
fi

# Clean and create build directory
echo -e "${GREEN}Setting up build directory...${NC}"
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Configure
echo -e "${GREEN}Configuring CMake...${NC}"
if [ "$OS" = "macOS" ]; then
    # Add Qt6 path for macOS
    export CMAKE_PREFIX_PATH="$(brew --prefix qt@6 2>/dev/null):$CMAKE_PREFIX_PATH"
fi

cmake "$PROJECT_DIR" \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_INSTALLER=ON \
    -DBUILD_TESTS=OFF

# Build
echo -e "${GREEN}Building project...${NC}"
if [ "$OS" = "Windows" ]; then
    cmake --build . --config Release -j
else
    cmake --build . -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
fi

# Package
echo -e "${GREEN}Generating installer packages...${NC}"

if [ "$OS" = "Linux" ]; then
    # Generate DEB package
    echo -e "${BLUE}Generating DEB package...${NC}"
    cpack -G DEB

    # Generate RPM package if rpmbuild is available
    if command -v rpmbuild &> /dev/null; then
        echo -e "${BLUE}Generating RPM package...${NC}"
        cpack -G RPM
    fi

elif [ "$OS" = "macOS" ]; then
    # Generate DMG package
    echo -e "${BLUE}Generating DMG package...${NC}"
    cpack -G DragNDrop

elif [ "$OS" = "Windows" ]; then
    # Generate NSIS installer
    echo -e "${BLUE}Generating NSIS installer...${NC}"
    cpack -C Release -G NSIS
fi

# List generated packages
echo ""
echo -e "${GREEN}Generated packages:${NC}"
echo "==================="
find "$BUILD_DIR" -maxdepth 1 -type f \( -name "*.deb" -o -name "*.rpm" -o -name "*.dmg" -o -name "*.exe" \) -exec ls -lh {} \;

echo ""
echo -e "${GREEN}Packaging complete!${NC}"
echo -e "${YELLOW}Packages are located in: $BUILD_DIR${NC}"
