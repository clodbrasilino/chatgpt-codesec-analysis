#include <stdio.h>
#include <regex.h>

#define IP_ADDR_LEN 16

int isIpAddressValid(const char *ipAddress) {
    regex_t regex;
    int result;
    
    const char *pattern = "^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return -1;
    }
    
    result = regexec(&regex, ipAddress, 0, NULL, 0);
    regfree(&regex);
    
    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char ipAddress[IP_ADDR_LEN];
    
    printf("Enter an IP address: ");
    scanf("%15s", ipAddress);

    if (isIpAddressValid(ipAddress)) {
        printf("Valid IP address\n");
    } else {
        printf("Invalid IP address\n");
    }
    
    return 0;
}