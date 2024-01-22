#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_IP_ADDRESS_SIZE 16

void removeLeadingZeroes(char* ip_address) {
    assert(ip_address != NULL);
    size_t len = strnlen(ip_address, MAX_IP_ADDRESS_SIZE);
    if(len == 0) return;

    size_t i, j;
    for (i = 0; i < len; i++) {
        if (ip_address[i] != '0' || (i+1 < len && ip_address[i+1] == '.')) {
            break;
        }
    }

    for (j = 0; i < len; i++, j++) {
        ip_address[j] = ip_address[i];
    }

    ip_address[j] = '\0';
}

int main() {
    char ip_address[MAX_IP_ADDRESS_SIZE + 2];

    printf("Enter IP address: ");
    if (fgets(ip_address, sizeof(ip_address), stdin) != NULL) {
        if(strlen(ip_address) > MAX_IP_ADDRESS_SIZE) {
            printf("Error: Input too long\n");
            return 1;
        }
        ip_address[strlen(ip_address) - 1] = '\0';
        removeLeadingZeroes(ip_address);
        printf("IP address without leading zeroes: %s\n", ip_address);
    } else {
        printf("Error reading IP address\n");
    }

    return 0;
}