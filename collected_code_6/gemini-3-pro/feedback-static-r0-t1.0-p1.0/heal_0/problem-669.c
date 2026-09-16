#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <regex.h>

bool is_valid_ip(const char *ip);

bool is_valid_ip(const char *ip) {
    if (ip == NULL) {
        return false;
    }

    regex_t regex;
    int comp_ret;
    int exec_ret;
    
    const char *pattern = "^([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$";

    comp_ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (comp_ret != 0) {
        return false;
    }

    exec_ret = regexec(&regex, ip, 0, NULL, 0);
    
    regfree(&regex);

    return (exec_ret == 0);
}

int main(void) {
    const char *test_ips[] = {
        "192.168.1.1",
        "255.255.255.255",
        "0.0.0.0",
        "256.256.256.256",
        "192.168.1",
        "192.168.01.1",
        "abc.def.ghi.jkl",
        NULL
    };

    for (size_t i = 0; test_ips[i] != NULL; i++) {
        bool valid = is_valid_ip(test_ips[i]);
        printf("%s: %s\n", test_ips[i], valid ? "Valid" : "Invalid");
    }

    return EXIT_SUCCESS;
}