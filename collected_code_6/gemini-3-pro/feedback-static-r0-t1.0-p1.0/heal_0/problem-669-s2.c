#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int is_valid_ip(const char *ip_address) {
    if (ip_address == NULL) {
        return 0;
    }

    regex_t regex;
    int ret;
    const char *pattern = "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, ip_address, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
    const char *test_ips[] = {
        "192.168.1.1",
        "255.255.255.255",
        "256.0.0.1",
        "invalid_ip",
        "1.2.3.4",
        "0.0.0.0",
        "192.168.1",
        NULL
    };

    for (int i = 0; test_ips[i] != NULL; i++) {
        if (is_valid_ip(test_ips[i])) {
            printf("%s is a valid IP address.\n", test_ips[i]);
        } else {
            printf("%s is an invalid IP address.\n", test_ips[i]);
        }
    }

    return 0;
}