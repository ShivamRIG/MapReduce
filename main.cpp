#include <iostream>
#include "RemoteProcedureCalls.h"
using namespace std;

int main(int argc, char** argv) {
//argv
//1 w/m Worker Node/Master Node
//
 if(argc<2) {
  cout<<"Invalid input please inter W/w :worker or M/m :master\n";
  return -1;
  }
 string nodeType=argv[1];
 if(nodeType=="W" or nodeType=="w")cout<<"This is a worker Node\n";
 else if(nodeType=="M" or nodeType=="m")cout<<"This is a master Node\n";
 else cout<<"Invalid input please inter W/w :worker or M/m :master\n";
}

