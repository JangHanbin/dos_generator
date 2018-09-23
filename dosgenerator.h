#ifndef DOSGENERATOR_H
#define DOSGENERATOR_H

#include <sys/socket.h>
#include "jpcap/jpcaplib.h"
#include "jpcap/mac.h"
#include "jpcap/ip.h"

class DosGenerator
{
    char pcap_error_buf_[PCAP_ERRBUF_SIZE];
    pcap_t* pcd_;
    int raw_fd_;
    struct iphdr iph_;
    struct tcphdr tcph_;

public:
    DosGenerator();
    //Ip class must be init to public that's why there is an fucntion

    Ip sender_ip_;
    Ip target_ip_;
    bool pcd_init(const char *dev);

    //there is an default value.
    //also it can replace to function overloading.
    bool raw_init(int type = IPPROTO_RAW);
    pcap_t *get_pcd() const;
    void set_pcd(pcap_t *value);
    int get_raw_fd() const;
    void set_raw_fd(int raw_fd);

    bool init_iph(uint32_t &src_ip, uint32_t &dest_ip);
    bool init_tcph(uint16_t &src_port, uint16_t &dest_port);
};

#endif // DOSGENERATOR_H
