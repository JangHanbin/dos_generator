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
