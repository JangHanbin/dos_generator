#ifndef DOSGENERATOR_H
#define DOSGENERATOR_H

#include "jpcap/jpcaplib.h"

class DosGenerator
{
    char pcap_error_buf[PCAP_ERRBUF_SIZE];
    pcap_t* pcd;

public:
    DosGenerator();
    bool pcd_init(const char *dev);
};

#endif // DOSGENERATOR_H
