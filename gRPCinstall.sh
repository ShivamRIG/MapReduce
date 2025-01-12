#! /bin/bash

#Installations as mentioned on gRPC website for C++
export MY_INSTALL_DIR=$HOME/.local
mkdir -p $MY_INSTALL_DIR
apt update && apt-get install -y cmake build-essential git protobuf-compiler autoconf libtool pkg-config sudo
git clone --recurse-submodules -b v1.66.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc


# git clone --recurse-submodules -b v1.66.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc
cd grpc
mkdir -p cmake/build
pushd cmake/build
sudo cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
      ../..
sudo make -j 4
sudo make install
popd