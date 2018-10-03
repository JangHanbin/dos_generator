

# DOS-GENERATOR

* Do NOT Test in NAT Mode. 
  * Hipervisor auto send RST Packet





## Suport Attack Method

| Attack | Description |
| ------ | ----------- |
| Syn Flooding  | Send Syn Packet to victim as Random Src IP |
| ICMP Flooding | Send ICMP Packet to victim or broadcast (optional) |



## run

```console
foo@bar:~# qmake
foo@bar:~# make
foo@bar:~# ./dos_generator <target ip>
```



## Environment



**OS** :  Linux kali 4.15.0-kali3-amd64 #1 SMP Debian 4.15.17-1kali1 (2018-04-25) x86_64 GNU/Linux



**IDE** : Qt Creator 





