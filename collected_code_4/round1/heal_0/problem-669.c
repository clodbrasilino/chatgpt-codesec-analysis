#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#define MAX_IP_LENGTH 16

int is_valid_ip(const char *ipAddress)
{
    regex_t regex;
    int regCompResult;
    regCompResult = regcomp(&regex, 
            "^([0-9]{1,3}\\.){3}[0-9]{1,3}$", 
            REG_EXTENDED|REG_NOSUB);
    if (regCompResult) {
        return 0;
    }

    regmatch_t items[MAX_IP_LENGTH];
    if (regexec(&regex, ipAddress, MAX_IP_LENGTH, items, 0)) {
        return 0;
    }

    regfree(&regex);
    
    for (char ipPart[4], *pEnd, *pStart = (char *)ipAddress; ; pStart = NULL) {
        char *token = strtok(pStart, ".");
        if (token == NULL) {
            break;
        }
        strncpy(ipPart, token, sizeof(ipPart) - 1);
        ipPart[sizeof(ipPart) - 1] = '\0';
        long num = strtol(ipPart, &pEnd, 10);
        if (pEnd == ipPart 
            || *pEnd != '\0' 
            || num < 0 || num > 255) {
            return 0;
        }
    }

    return 1;
}

int main()
{
    char ipAddress[MAX_IP_LENGTH];
    printf("Enter an IP address: ");
    fgets(ipAddress, sizeof(ipAddress), stdin);
    ipAddress[strcspn(ipAddress, "\n")] = '\0';
    
    if (is_valid_ip(ipAddress)) {
        printf("%s is a valid IP address.\n", ipAddress);
    } else {
        printf("%s is not a valid IP address.\n", ipAddress);
    }

    return 0;
}