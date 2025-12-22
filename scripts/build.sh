#!/bin/bash
# Build script for AutoCoder

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}AutoCoder Build Script${NC}"
echo "======================="

# Check for required tools
command -v cmake >/dev/null 2>&1 || { echo -e "${RED}Error: cmake is required but not installed.${NC}" >&2; exit 1; }
command -v g++ >/dev/null 2>&1 || command -v clang++ >/dev/null 2>&1 || { echo -e "${RED}Error: C++ compiler is required.${NC}" >&2; exit 1; }

# Parse arguments
BUILD_TYPE="Release"
BUILD_TESTS="OFF"
BUILD_INSTALLER="OFF"
CLEAN_BUILD=false
NUM_JOBS=$(nproc 2>/dev/null || echo 4)

while [[ $# -gt 0 ]]; do
    case $1 in
        --debug)
            BUILD_TYPE="Debug"
            shift
            ;;
        --tests)
            BUILD_TESTS="ON"
            shift
            ;;
        --installer)
            BUILD_INSTALLER="ON"
            shift
            ;;
        --clean)
            CLEAN_BUILD=true
            shift
            ;;
        --jobs)
            NUM_JOBS="$2"
            shift 2
            ;;
        *)
            echo -e "${RED}Unknown option: $1${NC}"
            echo "Usage: $0 [--debug] [--tests] [--installer] [--clean] [--jobs N]"
            exit 1
            ;;
    esac
done

# Clean if requested
if [ "$CLEAN_BUILD" = true ]; then
    echo -e "${YELLOW}Cleaning build directory...${NC}"
    rm -rf build
fi

# Create build directory
mkdir -p build
cd build

# Configure
echo -e "${GREEN}Configuring...${NC}"
cmake .. \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
    -DBUILD_TESTS=$BUILD_TESTS \
    -DBUILD_INSTALLER=$BUILD_INSTALLER

# Build
echo -e "${GREEN}Building with $NUM_JOBS parallel jobs...${NC}"
cmake --build . -j$NUM_JOBS

# Run tests if enabled
if [ "$BUILD_TESTS" = "ON" ]; then
    echo -e "${GREEN}Running tests...${NC}"
    ctest --output-on-failure
fi

# Build installer if enabled
if [ "$BUILD_INSTALLER" = "ON" ]; then
    echo -e "${GREEN}Building installer...${NC}"
    cpack
fi

echo -e "${GREEN}Build complete!${NC}"
echo "Binary location: $(pwd)/autocoder"
