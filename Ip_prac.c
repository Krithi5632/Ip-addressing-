#include <stdio.h>

void printBinary(int num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

int main() {
    int o1, o2, o3, o4;

    printf("Enter an IPv4 address (e.g., 192.168.1.25): ");
    if (scanf("%d.%d.%d.%d", &o1, &o2, &o3, &o4) != 4) {
        printf("Invalid format! Use X.X.X.X\n");
        return 1;
    }

    if (o1 < 0 || o1 > 255 || o2 < 0 || o2 > 255 || 
        o3 < 0 || o3 > 255 || o4 < 0 || o4 > 255) {
        printf("Invalid IP! Each number must be between 0 and 255.\n");
        return 1;
    }

    printf("\n--- HOW THIS IP ADDRESS WORKS ---\n");

    printf("1. Decimal Format : %d.%d.%d.%d\n", o1, o2, o3, o4);
    printf("2. 32-Bit Binary  : ");
    printBinary(o1); printf(".");
    printBinary(o2); printf(".");
    printBinary(o3); printf(".");
    printBinary(o4); printf("\n");

    if (o1 >= 1 && o1 <= 126) {
        printf("3. IP Class       : Class A (First bit starts with 0)\n");
        printf("4. Subnet Mask    : 255.0.0.0 (/8)\n");
        printf("5. Network ID     : %d.0.0.0 (Identifies the Network)\n", o1);
        printf("6. Host ID        : 0.%d.%d.%d (Identifies the Device)\n", o2, o3, o4);
    } 
    else if (o1 == 127) {
        printf("3. IP Class       : Loopback Address (Reserved for self-testing)\n");
    } 
    else if (o1 >= 128 && o1 <= 191) {
        printf("3. IP Class       : Class B (First bits start with 10)\n");
        printf("4. Subnet Mask    : 255.255.0.0 (/16)\n");
        printf("5. Network ID     : %d.%d.0.0 (Identifies the Network)\n", o1, o2);
        printf("6. Host ID        : 0.0.%d.%d (Identifies the Device)\n", o3, o4);
    } 
    else if (o1 >= 192 && o1 <= 223) {
        printf("3. IP Class       : Class C (First bits start with 110)\n");
        printf("4. Subnet Mask    : 255.255.255.0 (/24)\n");
        printf("5. Network ID     : %d.%d.%d.0 (Identifies the Network)\n", o1, o2, o3);
        printf("6. Host ID        : 0.0.0.%d (Identifies the Device)\n", o4);
    } 
    else if (o1 >= 224 && o1 <= 239) {
        printf("3. IP Class       : Class D (Multicast - No Host/Network split)\n");
    } 
    else if (o1 >= 240 && o1 <= 255) {
        printf("3. IP Class       : Class E (Experimental - Reserved)\n");
    } 
    else {
        printf("3. IP Class       : Special/Default Network (0.x.x.x)\n");
    }

    return 0;
}
