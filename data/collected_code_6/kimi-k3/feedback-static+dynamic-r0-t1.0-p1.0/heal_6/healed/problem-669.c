#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <stdint.h>

#define MAX_IP_LEN 45

int is_valid_ip(const char *ip, size_t max_len) {
    regex_t regex;
    int ret;
    const char *pattern = "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$";

    if (ip == NULL) {
        return 0;
    }

    size_t len = 0;
    while (len < max_len && ip[len] != '\0') {
        len++;
    }
    
    if (len == 0 || len > MAX_IP_LEN) {
        return 0;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, ip, 0, NULL, 0);
    regfree(&regex);

    return (ret == 0) ? 1 : 0;
}

int main(void) {
    char ip[MAX_IP_LEN + 2];
    int c;
    size_t len;

    printf("Enter an IP address: ");
    
    if (fgets(ip, sizeof(ip), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strcspn(ip, "\n");
    
    if (len == sizeof(ip) - 1) {
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    ip[len] = '\0';

    if (is_valid_ip(ip, sizeof(ip))) {
        printf("Valid IP address\n");
    } else {
        printf("Invalid IP address\n");
    }

    return EXIT_SUCCESS;
}