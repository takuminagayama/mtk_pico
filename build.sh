#!/bin/bash

# Build script for mtk3-pico-gmake project
# This script performs: clean, build, and UF2 generation

set -e  # Exit on error

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build_make"

echo "=== mtk3-pico-gmake Build Script ==="
echo "Script directory: $SCRIPT_DIR"
echo "Build directory: $BUILD_DIR"
echo ""

# Change to build directory
cd "$BUILD_DIR"

# Step 1: Clean
echo "[1/3] Cleaning build directory..."
make clean
echo "✓ Clean completed"
echo ""

# Step 2: Build
echo "[2/3] Building project..."
make
if [ $? -eq 0 ]; then
    echo "✓ Build completed successfully"
else
    echo "✗ Build failed"
    exit 1
fi
echo ""

# Step 3: Generate UF2
echo "[3/3] Generating UF2 file..."
if [ -f "mtk3pico.elf" ]; then
    tools/elf2uf2 mtk3pico.elf mtk3pico.uf2
    if [ $? -eq 0 ]; then
        echo "✓ UF2 generation completed"
        echo ""
        echo "=== Build Summary ==="
        ls -lh mtk3pico.{elf,map,uf2}
        echo ""
        echo "UF2 file ready for flashing: $(pwd)/mtk3pico.uf2"
    else
        echo "✗ UF2 generation failed"
        exit 1
    fi
else
    echo "✗ ELF file not found: mtk3pico.elf"
    exit 1
fi

echo ""
echo "=== Build completed successfully ==="
