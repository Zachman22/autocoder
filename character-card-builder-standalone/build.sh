#!/bin/bash
# Character Card Builder - Build Script
# Automatically detects platform and builds the application

set -e

echo "🎭 Character Card Builder - Build Script"
echo "========================================"
echo ""

# Detect platform
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    PLATFORM="Linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    PLATFORM="macOS"
else
    echo "❌ Unsupported platform: $OSTYPE"
    exit 1
fi

echo "📍 Platform: $PLATFORM"
echo ""

# Check for dependencies
echo "🔍 Checking dependencies..."

check_command() {
    if ! command -v $1 &> /dev/null; then
        echo "❌ $1 not found. Please install it first."
        return 1
    else
        echo "✅ $1 found"
        return 0
    fi
}

DEPS_OK=true
check_command cmake || DEPS_OK=false
check_command git || DEPS_OK=false

if [ "$DEPS_OK" = false ]; then
    echo ""
    echo "❌ Missing dependencies. Please install them first."
    echo ""
    if [ "$PLATFORM" = "Linux" ]; then
        echo "For Ubuntu/Debian:"
        echo "  sudo apt-get install cmake qt6-base-dev libssl-dev libcurl4-openssl-dev"
        echo ""
        echo "For Fedora:"
        echo "  sudo dnf install cmake qt6-qtbase-devel openssl-devel libcurl-devel"
    else
        echo "For macOS (Homebrew):"
        echo "  brew install cmake qt@6 openssl curl"
    fi
    exit 1
fi

echo ""
echo "🔨 Building Character Card Builder..."
echo ""

# Create build directory
mkdir -p build
cd build

# Configure
echo "⚙️  Configuring..."
if [ "$PLATFORM" = "macOS" ]; then
    cmake .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_PREFIX_PATH=$(brew --prefix qt@6) \
        -DOPENSSL_ROOT_DIR=$(brew --prefix openssl@3)
else
    cmake .. -DCMAKE_BUILD_TYPE=Release
fi

# Build
echo ""
echo "🔧 Compiling..."
CPU_COUNT=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
cmake --build . -j$CPU_COUNT

echo ""
echo "✅ Build complete!"
echo ""
echo "📍 Binary location: $(pwd)/character-card-builder"
echo ""
echo "To run the application:"
echo "  cd build"
echo "  ./character-card-builder"
echo ""
echo "To install system-wide:"
echo "  sudo cmake --install ."
echo ""
echo "To create installer package:"
if [ "$PLATFORM" = "Linux" ]; then
    echo "  cpack -G DEB    # For Debian/Ubuntu (.deb)"
    echo "  cpack -G RPM    # For Fedora/RHEL (.rpm)"
else
    echo "  cpack -G DragNDrop  # For macOS (.dmg)"
fi
echo ""
