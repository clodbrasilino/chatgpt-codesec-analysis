#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int is_valid_ip(const char *ip) {
    regex_t reg;
    int ret;
    char pattern[] = "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";

    ret = regcomp(&reg, pattern, REG_EXTENDED);
    if (ret) {
        return 0;
    }

    ret = regexec(&reg, ip, 0, NULL, 0);
    regfree(&reg);

    return !ret;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ip_address>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *ip = argv[1];
    if (is_valid_ip(ip)) {
        printf("Valid IP address\n");
    } else {
        printf("Invalid IP address\n");
    }

    return EXIT_SUCCESS;
}