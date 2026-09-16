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
    int result;

    if (ip == NULL) {
        return false;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return false;
    }

    result = regexec(&regex, ip, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <IPv4-address>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (is_valid_ipv4(argv[1])) {
        printf("Valid IPv4 address\n");
        return EXIT_SUCCESS;
    }

    printf("Invalid IPv4 address\n");
    return EXIT_FAILURE;
}