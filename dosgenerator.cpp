#include "dosgenerator.h"

pcap_t *DosGenerator::get_pcd() const
{
    return pcd_;
}

void DosGenerator::set_pcd(pcap_t *value)
{
    pcd_ = value;
}

int DosGenerator::get_raw_fd() const
{
    return raw_fd_;
}

void DosGenerator::set_raw_fd(int raw_fd)
{
    raw_fd_ = raw_fd;
}

bool DosGenerator::init_iph(uint32_t& src_ip, uint32_t& dest_ip)
{

    memset(iph_,0,sizeof(struct iphdr));

    //set ip header
    iph_.version=4;
    iph_.ihl=5;
    iph_.frag_off=htons(IP_DF); //don't flagment set
    iph_.ttl=64;
    iph_.protocol=IPPROTO_TCP;


    iph_.saddr = htonl(src_ip);
    iph_.daddr = htonl(dest_ip);


    return true;


}

bool DosGenerator::init_tcph(uint16_t &src_port, uint16_t &dest_port)
{
    memset(tcph_,0,sizeof(struct tcphdr));

    //set tcp header
    tcph_.doff=5;
    tcph_.window=htons(1024);
    tcph_.source = htons(src_port);
    tcph_.dest = htons(dest_port);

    return true;

}

DosGenerator::DosGenerator()
{

}

bool DosGenerator::pcd_init(const char * dev)
{
    pcd_ = pcap_open_live(dev,BUFSIZ,0,1,pcap_error_buf_);
    if(pcd_==NULL)
        return false;

    return true;
}

bool DosGenerator::raw_init(int type)
{
    if((raw_fd_ = socket(AF_INET,SOCK_RAW,type))<0)
        return false;

    return true;
}
