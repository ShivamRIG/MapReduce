
if ( ls | grep -q grpc );
then 
 echo "grpc already installed"
else 
 echo "installing grpc"
 sudo ./gRPCinstall.sh
fi 
cd DistributedSystemsHandling/InterProcessCommunication/protofiles/
./generate_cpp.sh
cd ../../../
sudo cmake -S . -B out/build
cd out/build
sudo make