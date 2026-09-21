#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define IP_PATTERN "^((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])$"

static void print_regex_error(int errcode, const regex_t *regex)
{
    size_t needed = regerror(errcode, regex, NULL, 0);
    char *errbuf = malloc(needed);

    if (errbuf != NULL) {
        regerror(errcode, regex, errbuf, needed);
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        free(errbuf);
    } else {
        fprintf(stderr, "Regex compilation failed (unable to allocate error buffer)\n");
    }
}

int is_valid_ip(const char *ip)
{
    regex_t regex;
    int ret;

    if (ip == NULL) {
        return 0;
    }

    ret = regcomp(&regex, IP_PATTERN, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        print_regex_error(ret, &regex);
        return -1;
    }

    ret = regexec(&regex, ip, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    }
    if (ret == REG_NOMATCH) {
        return 0;
    }

    fprintf(stderr, "Regex execution failed\n");
    return -1;
}

int main(void)
{
    const char *test_ips[] = {
        "192.168.1.1",
        "255.255.255.255",
        "0.0.0.0",
        "256.1.1.1",
        "192.168.1",
        "192.168.1.1.1",
        "abc.def.ghi.jkl",
        "10.0.0.01",
        "1.2.3.4"
    };
    size_t count = sizeof(test_ips) / sizeof(test_ips[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int result = is_valid_ip(test_ips[i]);

        if (result < 0) {
            fprintf(stderr, "Error validating %s\n", test_ips[i]);
            return EXIT_FAILURE;
        }
        printf("%s is %s\n", test_ips[i], result ? "valid" : "invalid");
    }

    return EXIT_SUCCESS;
}