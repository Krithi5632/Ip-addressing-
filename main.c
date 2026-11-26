
#include <stdio.h>
#include <stdint.h>

typedef struct
{
    uint32_t ip;
    uint32_t mask;
    uint32_t network;
    uint32_t broadcast;
} NetworkInfo;

uint32_t ipToInt(int a, int b, int c, int d)
{
    return ((uint32_t)a << 24) |
           ((uint32_t)b << 16) |
           ((uint32_t)c << 8) |
           d;
}

void intToIP(uint32_t ip)
{
    printf("%u.%u.%u.%u",
           (ip >> 24) & 255,
           (ip >> 16) & 255,
           (ip >> 8) & 255,
           ip & 255);
}

uint32_t prefixToMask(int prefix)
{
    if (prefix == 0)
        return 0;

    return 0xFFFFFFFF << (32 - prefix);
}

void printClass(uint32_t ip)
{
    int first = (ip >> 24) & 255;

    printf("Class       : ");

    if (first >= 1 && first <= 126)
        printf("A");
    else if (first >= 128 && first <= 191)
        printf("B");
    else if (first >= 192 && first <= 223)
        printf("C");
    else if (first >= 224 && first <= 239)
        printf("D");
    else if (first >= 240)
        printf("E");
    else
        printf("Special");

    printf("\n");
}

void classifyIP(NetworkInfo info)
{
    int first = (info.ip >> 24) & 255;
    int second = (info.ip >> 16) & 255;

    printf("\n------------ RESULT ------------\n");

    printf("IP Address       : ");
    intToIP(info.ip);

    printf("\nSubnet Mask      : ");
    intToIP(info.mask);

    printf("\nNetwork Address  : ");
    intToIP(info.network);

    printf("\nBroadcast Address: ");
    intToIP(info.broadcast);

    printf("\n");

    printClass(info.ip);

    printf("Type             : ");

    if (info.ip == 0)
    {
        printf("Unspecified Address");
    }
    else if (info.ip == 0xFFFFFFFF)
    {
        printf("Limited Broadcast Address");
    }
    else if (first == 127)
    {
        printf("Loopback Address");
    }
    else if (first == 169 && second == 254)
    {
        printf("APIPA Address");
    }
    else if (first >= 224 && first <= 239)
    {
        printf("Multicast Address");
    }
    else if (first >= 240)
    {
        printf("Experimental / Class E");
    }
    else if (info.ip == info.network)
    {
        printf("Network Address (Cannot be assigned to host)");
    }
    else if (info.ip == info.broadcast)
    {
        printf("Directed Broadcast Address (Cannot be assigned to host)");
    }
    else if (first == 10)
    {
        printf("Private IP (10.0.0.0/8)");
    }
    else if (first == 172 &&
             second >= 16 &&
             second <= 31)
    {
        printf("Private IP (172.16.0.0/12)");
    }
    else if (first == 192 &&
             second == 168)
    {
        printf("Private IP (192.168.0.0/16)");
    }
    else
    {
        printf("Public IP");
    }

    printf("\n");
}

int main()
{
    int a, b, c, d;
    int prefix;

    NetworkInfo info;

    printf("Enter IP Address in CIDR format (e.g. 192.168.1.10/24): ");
    scanf("%d.%d.%d.%d/%d",
          &a,
          &b,
          &c,
          &d,
          &prefix);

    if (a < 0 || a > 255 ||
        b < 0 || b > 255 ||
        c < 0 || c > 255 ||
        d < 0 || d > 255)
    {
        printf("invalid IP Address\n");
        return 1;
    }

    if (prefix < 0 || prefix > 32)
    {
        printf("Invalid Prefix Length\n");
        return 1;
    }

    info.ip = ipToInt(a, b, c, d);
    info.mask = prefixToMask(prefix);
    info.network = info.ip & info.mask;
    info.broadcast = info.network | (~info.mask);

    classifyIP(info);

    return 0;
}
