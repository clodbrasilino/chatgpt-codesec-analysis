#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_valid_url(const char *url)
{
    static const char pattern[] =
        "^(https?|ftp)://"
        "(([A-Za-z0-9]([A-Za-z0-9-]{0,61}[A-Za-z0-9])?\\.)+"
        "[A-Za-z]{2,63}|"
        "localhost|"
        "([0-9]{1,3}\\.){3}[0-9]{1,3})"
        "(:[0-9]{1,5})?"
        "(/[^[:space:]]*)?$";
    regex_t regex;

    if (url == NULL || *url == '\0') {
        return false;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return false;
    }

    const int result = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (is_valid_url(argv[1])) {
        puts("Valid URL");
        return EXIT_SUCCESS;
    }

    puts("Invalid URL");
    return EXIT_FAILURE;
}