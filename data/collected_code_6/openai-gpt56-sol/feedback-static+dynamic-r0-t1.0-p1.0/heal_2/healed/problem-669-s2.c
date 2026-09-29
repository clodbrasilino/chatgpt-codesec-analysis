#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_valid_ipv4(const char *ip)
{
    static const char pattern[] =
        "^((25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9][0-9]|[0-9])\\.){3}"
        "(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9][0-9]|[0-9])$";
    regex_t regex;

    if (ip == NULL) {
        return false;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return false;
    }

    const int status = regexec(&regex, ip, 0, NULL, 0);
    regfree(&regex);

    return status == 0;
}

int main(int argc, const char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <IPv4-address>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (is_valid_ipv4(argv[1])) {
        puts("Valid");
        return EXIT_SUCCESS;
    }

    puts("Invalid");
    return EXIT_FAILURE;
}