FROM ubuntu:latest
RUN mkdir project
COPY gRPCinstall.sh ./project
RUN ./project/gRPCinstall.sh
COPY . ./project