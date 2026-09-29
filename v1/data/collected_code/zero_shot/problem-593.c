#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void removeLeadingZeroes(char* ip_address) {
    int i, j;
    int count = 0;
    
    for (i = 0; ip_address[i] != '\0'; i++) {
        if (ip_address[i] != '0') {
            break;
        }
    }
    
    for (j = 0; ip_address[i] != '\0'; i++, j++) {
        ip_address[j] = ip_address[i];
    }
    
    ip_address[j] = '\0';
}

int main() {
    char ip_address[16];
    
    printf("Enter IP address: ");
    fgets(ip_address, sizeof(ip_address), stdin);
    
    // Removing trailing newline character
    ip_address[strcspn(ip_address, "\n")] = '\0';
    
    removeLeadingZeroes(ip_address);
    
    printf("IP address without leading zeroes: %s\n", ip_address);
    
    return 0;
}