#include <stdio.h>
#include <regex.h>
#include <stdbool.h>

bool is_valid_ip(const char *ip) {
    const char *pattern = "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";
    regex_t reg;
    int reti;

    reti = regcomp(&reg, pattern, REG_EXTENDED);
    if (reti) {
        return false;
    }

    reti = regexec(&reg, ip, 0, NULL, 0);
    regfree(&reg);

    return !reti;
}

int main() {
    const char *test_ips[] = {"192.168.1.1", "255.255.255.255", "256.100.50.25", "192.168.0.254", "192.168.1.256"};
    for (size_t i = 0; i < sizeof(test_ips) / sizeof(test_ips[0]); ++i) {
        printf("%s: %s\n", test_ips[i], is_valid_ip(test_ips[i]) ? "Valid" : "Invalid");
    }
    return 0;
}