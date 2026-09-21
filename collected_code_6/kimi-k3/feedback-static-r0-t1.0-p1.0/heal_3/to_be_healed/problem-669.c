#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip[46];

    printf("Enter an IP address: ");
    if (fgets(ip, sizeof(ip), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t len = strcspn(ip, "\n");
    if (len == 0) {
        fprintf(stderr, "Empty input\n");
        return EXIT_FAILURE;
    }
    ip[len] = '\0';

    if (is_valid_ip(ip)) {
        printf("Valid IP address\n");
    } else {
        printf("Invalid IP address\n");
    }

    return EXIT_SUCCESS;
}