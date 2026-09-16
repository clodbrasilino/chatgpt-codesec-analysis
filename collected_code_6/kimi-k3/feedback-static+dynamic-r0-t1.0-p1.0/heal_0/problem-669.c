#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int is_valid_ip(const char *ip) {
    regex_t regex;
    int ret;
    const char *pattern = "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, ip, 0, NULL, 0);
    regfree(&regex);

    return (ret == 0) ? 1 : 0;
}

int main(void) {
    char ip[16];

    printf("Enter an IP address: ");
    if (fgets(ip, sizeof(ip), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t len = 0;
    while (ip[len] != '\0') {
        if (ip[len] == '\n') {
            ip[len] = '\0';
            break;
        }
        len++;
    }

    if (is_valid_ip(ip)) {
        printf("Valid IP address\n");
    } else {
        printf("Invalid IP address\n");
    }

    return EXIT_SUCCESS;
}