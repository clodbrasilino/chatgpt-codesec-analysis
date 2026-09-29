#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

#define IPV4_PATTERN "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$"
#define MAX_IP_LEN 15
#define BUFFER_SIZE (MAX_IP_LEN + 2)

int is_valid_ip(const char *ip_address, size_t max_len) {
    regex_t regex;
    int reti;
    int result = 0;
    size_t len;

    if (ip_address == NULL || max_len == 0) {
        return 0;
    }

    len = strnlen(ip_address, max_len);
    if (len == 0 || len > MAX_IP_LEN || len == max_len) {
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
    char *ip_address = NULL;
    size_t buffer_size = 0;
    ssize_t len;

    printf("Enter an IP address: ");

    len = getline(&ip_address, &buffer_size, stdin);
    if (len == -1) {
        free(ip_address);
        return 1;
    }

    if (len > 0 && ip_address[len - 1] == '\n') {
        ip_address[len - 1] = '\0';
        len--;
    }

    if (len == 0 || len > MAX_IP_LEN) {
        fprintf(stderr, "Input too long\n");
        free(ip_address);
        return 1;
    }

    if (is_valid_ip(ip_address, len + 1)) {
        printf("Valid IP address\n");
    } else {
        printf("Invalid IP address\n");
    }

    free(ip_address);
    return 0;
}