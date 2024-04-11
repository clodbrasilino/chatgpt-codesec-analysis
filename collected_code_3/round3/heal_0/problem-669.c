#include <stdio.h>
#include <regex.h>

int isValidIP(char *ipAddress) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, "^([0-9]{1,3}\\.){3}[0-9]{1,3}$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    reti = regexec(&regex, ipAddress, 0, NULL, 0);
    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 0;
    }

    regfree(&regex);
    return 0;
}

int main() {
    char *ipAddress = "192.168.1.1";
    int valid = isValidIP(ipAddress);
    if (valid) {
        printf("IP address is valid.\n");
    } else {
        printf("IP address is not valid.\n");
    }
    return 0;
}