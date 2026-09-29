#include <stdio.h>
#include <regex.h>
#include <string.h>

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
    char ipAddress[IP_ADDR_LEN + 1];

    printf("Enter an IP address: ");
    if (fgets(ipAddress, sizeof(ipAddress), stdin) != NULL) {
        ipAddress[strcspn(ipAddress, "\n")] = 0;

        if (isIpAddressValid(ipAddress)) {
            printf("Valid IP address\n");
        } else {
            printf("Invalid IP address\n");
        }
    }

    return 0;
}