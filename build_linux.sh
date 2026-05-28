#!/bin/bash
# Cross-platform RandomKingOnChessboard Build Script for Linux
# This script builds the project and provides instructions for running

echo ============================================
echo "RandomKingOnChessboard - Linux Build"
echo "============================================"
echo

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir -p build
fi

cd build

echo "Step 1: Configuring CMake..."
cmake ..

if [ $? -ne 0 ]; then
    echo "ERROR: CMake configuration failed!"
    exit 1
fi

echo
echo "Step 2: Building the project..."
make -j$(nproc)

if [ $? -ne 0 ]; then
    echo "ERROR: Build failed!"
    exit 1
fi

echo
echo "============================================"
echo "Build successful!"
echo
echo "To run the program:"
echo "  1. Navigate to: $(pwd)/bin/"
echo "  2. Run: ./RandomKingOnChessboard"
echo
echo "Or directly:"
echo "  ./bin/RandomKingOnChessboard"
echo "============================================"
echo

echo
echo "Font Requirements:"
echo "  - Linux should have DejaVu Sans font by default"
echo "  - If not, install with: sudo apt-get install fonts-dejavu-core"
echo "  - Or copy DejaVuSans.ttf to Resources/ folder"
echo
