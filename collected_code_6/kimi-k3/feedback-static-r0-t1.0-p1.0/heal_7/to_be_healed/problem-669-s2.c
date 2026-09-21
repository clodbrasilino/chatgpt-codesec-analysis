#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

#define IPV4_PATTERN "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$"
#define IPV4_MAX_LEN 15
#define BUFFER_SIZE (IPV4_MAX_LEN + 2)

int is_valid_ip(const char *ip_address, size_t max_len) {
    regex_t regex;
    int reti;
    int result = 0;
    size_t len;

    if (ip_address == NULL || max_len == 0 || max_len > BUFFER_SIZE) {
        return 0;
    }

    len = strnlen(ip_address, max_len);
    if (len == 0 || len > IPV4_MAX_LEN || len == max_len) {
        return 0;
    }

    reti = regcomp(&regex, IPV4_PATTERN, REG_EXTENDED);
    if (reti) {
        return 0;
    }

    reti = regexec(&regex, ip_address, 0, NULL, 0);
    if (reti == 0) {
        result = 1;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ip_address[BUFFER_SIZE];
    size_t len;

    printf("Enter an IP address: ");
    if (fgets(ip_address, sizeof(ip_address), stdin) == NULL) {
        return 1;
    }

    len = strcspn(ip_address, "\n");
    if (len == sizeof(ip_address) - 1 && ip_address[len] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Invalid IP address\n");
        return 1;
    }
    ip_address[len] = '\0';

    if (is_valid_ip(ip_address, sizeof(ip_address))) {
        printf("Valid IP address\n");
    } else {
        printf("Invalid IP address\n");
    }

    return 0;
}