#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Variables
GRPC_VERSION="v1.56.0"
GRPC_REPO="https://github.com/grpc/grpc"
BUILD_DIR="cmake/build"

# Update and install dependencies
echo "Installing dependencies..."
sudo apt-get update
sudo apt-get install -y build-essential cmake git libssl-dev zlib1g-dev protobuf-compiler libprotobuf-dev

# Clone the protobuf repository
echo "Cloning gRPC repository..."
git clone --depth=1 -b v21.12 https://github.com/protocolbuffers/protobuf.git
cd protobuf

# Build and install Protobuf
cmake -S . -B cmake/build -Dprotobuf_BUILD_SHARED_LIBS=ON
cmake --build cmake/build --parallel $(nproc)
sudo cmake --install cmake/build
# Update library cache
sudo ldconfig
# Go back to the original directory
cd ..
rm -rf protobuf

# Clone the gRPC repository
echo "Cloning gRPC repository..."
git clone -b $GRPC_VERSION --depth 1 $GRPC_REPO
cd grpc

# Initialize submodules
echo "Updating submodules..."
git submodule update --init

# Create the build directory
echo "Creating build directory..."
mkdir -p $BUILD_DIR
cd $BUILD_DIR

# Configure with CMake
echo "Configuring with CMake..."
cmake ../.. -DBUILD_SHARED_LIBS=ON

# Build gRPC
echo "Building gRPC..."
make -j$(nproc)

# Install gRPC
echo "Installing gRPC..."
sudo make install

# Update shared library cache
echo "Updating shared library cache..."
sudo ldconfig

# Cleanup
echo "Cleaning up build files..."
cd ../../..
rm -rf grpc

echo "gRPC installation completed successfully."
