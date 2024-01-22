#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

#define IP_ADDR_LEN 16

int isIpAddressValid(const char *ipAddress) {
    regex_t regex;
    int reti;
    const char *pattern = "^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return -1;
    }
    reti = regexec(&regex, ipAddress, 0, NULL, 0);
    regfree(&regex);
    if (!reti) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char *ipAddress = (char *)malloc(IP_ADDR_LEN + 1);
    printf("Enter an IP address: ");
    if (fgets(ipAddress, IP_ADDR_LEN + 1, stdin) != NULL) {
        /* Possible weaknesses found:
         *  use of possibly-NULL 'ipAddress' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
         */
        ipAddress[strcspn(ipAddress, "\n")] = 0;
        if (isIpAddressValid(ipAddress)) {
            printf("Valid IP address\n");
        } else {
            printf("Invalid IP address\n");
        }
    }
    free(ipAddress);
    return 0;
}