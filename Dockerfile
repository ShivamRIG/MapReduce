# FROM ubuntu:latest
# COPY gRPCinstall.sh ./
# RUN ./gRPCinstall.sh
# RUN mkdir project
# COPY . ./project
# CMD ["/bin/bash", "-c", "export PATH=\"$HOME/.local/bin:$PATH\" && /bin/bash"]
# RUN ./project/initialize.sh 
# This file will initialize docker container where the code is already installed 
#NEW docker file on multi-staging
#AS refer to Build stage
# Stage 1: Build
FROM ubuntu:20.04 AS build 
RUN apt-get update && apt-get install -y build-essential cmake git libssl-dev zlib1g-dev
RUN git clone -b v1.56.0 --depth 1 https://github.com/grpc/grpc \
    && cd grpc \
    && git submodule update --init \
    && mkdir -p cmake/build \
    && cd cmake/build \
    && cmake ../.. -DBUILD_SHARED_LIBS=ON \
    && make -j$(nproc) \
    && make install

WORKDIR /app
COPY . /app
RUN mkdir build && cd build && cmake .. && make -j$(nproc)

# Stage 2: Runtime
FROM ubuntu:20.04

RUN apt-get update && apt-get install -y libssl-dev zlib1g-dev && rm -rf /var/lib/apt/lists/*

CMD ["/bin/bash", "-c", "export PATH=\"$HOME/.local/bin:$PATH\" && /bin/bash"]

# ENTRYPOINT ["my_grpc_app"]
