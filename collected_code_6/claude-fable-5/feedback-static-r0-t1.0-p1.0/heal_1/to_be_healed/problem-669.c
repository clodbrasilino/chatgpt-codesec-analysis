#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define IP_PATTERN "^((25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])$"

int is_valid_ip(const char *ip)
{
    regex_t regex;
    int result;

    if (ip == NULL) {
        return 0;
    }

    result = regcomp(&regex, IP_PATTERN, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        char errbuf[256];
        regerror(result, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    result = regexec(&regex, ip, 0, NULL, 0);
    regfree(&regex);

    if (result == 0) {
        return 1;
    } else if (result == REG_NOMATCH) {
        return 0;
    } else {
        fprintf(stderr, "Regex execution failed\n");
        return -1;
    }
}

int main(void)
{
    const char *test_ips[] = {
        "192.168.1.1",
        "255.255.255.255",
        "0.0.0.0",
        "256.1.1.1",
        "192.168.1",
        "abc.def.ghi.jkl",
        "10.0.0.1",
        "999.999.999.999",
        "1.2.3.4.5",
        ""
    };
    size_t count = sizeof(test_ips) / sizeof(test_ips[0]);
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'status' can be reduced. [variableScope]
     */
    int status;

    for (i = 0; i < count; i++) {
        status = is_valid_ip(test_ips[i]);
        if (status < 0) {
            fprintf(stderr, "Error validating IP: %s\n", test_ips[i]);
            return EXIT_FAILURE;
        }
        printf("%-20s : %s\n", test_ips[i], status == 1 ? "Valid" : "Invalid");
    }

    return EXIT_SUCCESS;
}