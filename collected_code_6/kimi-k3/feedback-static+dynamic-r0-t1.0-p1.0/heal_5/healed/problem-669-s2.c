#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define IPV4_PATTERN "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$"
#define MAX_IP_LEN 16

int is_valid_ip(const char *ip_address, size_t max_len) {
    regex_t regex;
    int reti;
    int result = 0;
    size_t len;

    if (ip_address == NULL || max_len == 0) {
        return 0;
    }

    len = strnlen(ip_address, max_len);
    if (len == 0 || len > 15 || len == max_len) {
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
    char ip_address[MAX_IP_LEN];
    size_t len;
    int c;

    printf("Enter an IP address: ");
    if (fgets(ip_address, sizeof(ip_address), stdin) == NULL) {
        return 1;
    }

    len = strnlen(ip_address, sizeof(ip_address));
    if (len == sizeof(ip_address)) {
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return 1;
    }

    if (len > 0 && ip_address[len - 1] != '\n') {
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return 1;
    }

    ip_address[strcspn(ip_address, "\n")] = '\0';

    if (is_valid_ip(ip_address, sizeof(ip_address))) {
        printf("Valid IP address\n");
    } else {
        printf("Invalid IP address\n");
    }

    return 0;
}