#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void removeLeadingZeroes(char* ip_address) {
    int i, j;
    int count = 0;
    
    /* Possible weaknesses found:
     *  Cannot determine that 'ip_address[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (i = 0; ip_address[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'ip_address[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (ip_address[i] != '0') {
            break;
        }
    }
    
    /* Possible weaknesses found:
     *  Cannot determine that 'ip_address[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (j = 0; ip_address[i] != '\0'; i++, j++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'ip_address[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        ip_address[j] = ip_address[i];
    }
    
    ip_address[j] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char ip_address[16];
    
    printf("Enter IP address: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'ip_address[0]' is initialized [premium-bughuntingUninit]
     */
    fgets(ip_address, sizeof(ip_address), stdin);
    
    // Removing trailing newline character
    ip_address[strcspn(ip_address, "\n")] = '\0';
    
    removeLeadingZeroes(ip_address);
    
    printf("IP address without leading zeroes: %s\n", ip_address);
    
    return 0;
}