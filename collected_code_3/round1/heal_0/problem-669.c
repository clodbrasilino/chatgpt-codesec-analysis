#include <stdio.h>
#include <regex.h>

int isValidIP(char *ipAddress) {
    regex_t regex;
    int reti;
    char pattern[] = "^([0-9]{1,3}\\.){3}[0-9]{1,3}$";

    reti = regcomp(&regex, pattern, REG_EXTENDED);
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
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 0;
    }

    regfree(&regex);
    return 0;
}

int main() {
    char ipAddress[16];
    printf("Enter an IP address: ");
    scanf("%15s", ipAddress);

    if (isValidIP(ipAddress)) {
        printf("The IP address is valid.\n");
    } else {
        printf("The IP address is not valid.\n");
    }

    return 0;
}