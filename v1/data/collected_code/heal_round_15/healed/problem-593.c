#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IP_ADDRESS_SIZE 16

void removeLeadingZeroes(char* ip_address) {
    if(ip_address == NULL) {
        return;
    }

    size_t i, j;
    for (i = 0; ip_address[i] != '\0'; i++) {
        if (ip_address[i] != '0' || (ip_address[i+1] != '\0' && ip_address[i+1] == '.')) {
            break;
        }
    }

    for (j = 0; ip_address[i] != '\0'; i++, j++) {
        ip_address[j] = ip_address[i];
    }

    ip_address[j] = '\0';
}

int main() {
    char ip_address[MAX_IP_ADDRESS_SIZE + 1] = {0};

    printf("Enter IP address: ");

    if (fgets(ip_address, sizeof(ip_address), stdin) != NULL) {

        ip_address[strcspn(ip_address, "\n")] = '\0';

        if(strlen(ip_address) > MAX_IP_ADDRESS_SIZE) {
            printf("Error: Input too long\n");
            return 1;
        }

        removeLeadingZeroes(ip_address);
        printf("IP address without leading zeroes: %s\n", ip_address);

    } else {
        printf("Error reading IP address\n");
    }

    return 0;
}