#include <iostream>
#include "DistributedSystemsHandling/InterProcessCommunication/RemoteProcedureCalls.h"
using namespace std;
void mg11(char* st){
cout<<st<<endl;
}

int main(int argc, char** argv) {
    int n;
    n=argc;
    cout<<n<<endl;
    mg11(argv[0]);
    for(int i=0;i<n;i++)cout<<argv[i]<<endl;
    cout<<"hello"<<n;
    cout<<communication::add(54,66)<<endl;
}

