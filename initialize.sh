cd DistributedSystemsHandling/InterNodeCommunication/protofiles/
./generate_cpp.sh
cd ../../../
sudo cmake -S . -B out/build
cd out/build
sudo make