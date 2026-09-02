#include <stdio.h>
#include <string.h>
#include <regex.h>

int is_valid_ip(const char *ip) {
    regex_t regex;
    int ret;
    const char *pattern = "^((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])$";
    
    if (ip == NULL) {
        return 0;
    }
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }
    
    ret = regexec(&regex, ip, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0;
}

int main(void) {
    const char *test_ips[] = {
        "192.168.1.1",
        "255.255.255.255",
        "0.0.0.0",
        "256.256.256.256",
        "1.2.3.4",
        "10.0.0",
        "10.0.0.1.2",
        "abc.def.ghi.jkl",
        "1.2.3.4.5",
        "123.045.067.089",
        NULL
    };
    
    for (int i = 0; test_ips[i] != NULL; i++) {
        printf("%s => %s\n", test_ips[i], is_valid_ip(test_ips[i]) ? "Valid" : "Invalid");
    }
    
    return 0;
}