#include "dosgenerator.h"

DosGenerator::DosGenerator()
{

}

bool DosGenerator::pcd_init(const char * dev)
{
    pcd = pcap_open_live(dev,BUFSIZ,0,1,pcap_error_buf);
    if(pcd==NULL)
        return false;

    return true;
}
