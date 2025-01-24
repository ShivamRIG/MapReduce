pushd DistributedSystemsHandling/InterNodeCommunication/protofiles/
./generate_cpp.sh
popd
cmake -S . -B out/build
cd out/build
make