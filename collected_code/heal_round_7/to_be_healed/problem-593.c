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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char ip_address[MAX_IP_ADDRESS_SIZE + 1] = {0};

    printf("Enter IP address: ");
    if (fgets(ip_address, sizeof(ip_address), stdin) != NULL) {
        ip_address[strcspn(ip_address, "\n")] = '\0';
        removeLeadingZeroes(ip_address);
        printf("IP address without leading zeroes: %s\n", ip_address);
    } else {
        printf("Error reading IP address\n");
    }

    return 0;
}