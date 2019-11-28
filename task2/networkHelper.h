#ifndef _Network_Header
#define _Network_Header
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <linux/if_link.h>
#include <ctype.h>
#include <cstdlib>
#endif

char *net_mask()
{
    struct ifaddrs *ifaddr, *ifa, *tmp;
    int family, s, n;
    unsigned int tmpMask;

    char *netmask = NULL;

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }
    tmp = ifaddr;

    while (tmp)
    {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET)
        {
            struct sockaddr_in *ifn = (struct sockaddr_in *)tmp->ifa_netmask;
            if (strcmp(tmp->ifa_name, "lo") != 0)
            {
                netmask = (char *)calloc(200, sizeof(char *));
                inet_ntop(tmp->ifa_addr->sa_family, (void *)&ifn->sin_addr, netmask, 200);
                break;
            }
        }
        tmp = tmp->ifa_next;
    }
    freeifaddrs(ifaddr);
    return netmask;
}

char *IPAddress()
{
    struct ifaddrs *ifaddr, *ifa, *tmp;
    int family, s, n;
    unsigned int tmpMask;

    char *ifa_addr = NULL;

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }
    tmp = ifaddr;

    while (tmp)
    {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET)
        {
            struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
            if (strcmp(tmp->ifa_name, "lo") != 0)
            {
                ifa_addr = (char *)calloc(200, sizeof(char *));
                inet_ntop(tmp->ifa_addr->sa_family, (void *)&pAddr->sin_addr, ifa_addr, 200);
                break;
            }
        }
        tmp = tmp->ifa_next;
    }
    freeifaddrs(ifaddr);
    return ifa_addr;
}

char *Broadcast_Address()
{
    struct ifaddrs *ifaddr, *ifa, *tmp;
    int family, s, n;
    unsigned int tmpMask;
    char *ip = NULL;
    char *netmask = NULL;
    char *broadcast_address = (char *)malloc(16);
    ;
    struct in_addr host, mask, broadcast;

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }
    tmp = ifaddr;

    while (tmp)
    {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET)
        {
            struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
            struct sockaddr_in *ifn = (struct sockaddr_in *)tmp->ifa_netmask;
            if (strcmp(tmp->ifa_name, "lo") != 0)
            {
                netmask = (char *)calloc(200, sizeof(char *));
                ip = (char *)calloc(200, sizeof(char *));
                inet_ntop(tmp->ifa_addr->sa_family, (void *)&pAddr->sin_addr, ip, 200);
                inet_ntop(tmp->ifa_addr->sa_family, (void *)&ifn->sin_addr, netmask, 200);
                if (inet_pton(AF_INET, ip, &host) == 1 &&
                    inet_pton(AF_INET, netmask, &mask) == 1)
                    broadcast.s_addr = host.s_addr | ~mask.s_addr;
                else
                {
                    fprintf(stderr, "Failed converting strings to numbers\n");
                    return NULL;
                }
                if (inet_ntop(AF_INET, &broadcast, broadcast_address, INET_ADDRSTRLEN) == NULL)
                {
                    fprintf(stderr, "Failed converting number to string\n");
                    return NULL;
                }
            }
        }
        tmp = tmp->ifa_next;
    }

    freeifaddrs(ifaddr);
    return broadcast_address;
}
