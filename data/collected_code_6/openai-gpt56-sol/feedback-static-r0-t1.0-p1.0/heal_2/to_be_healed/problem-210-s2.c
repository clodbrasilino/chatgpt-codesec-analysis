#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool contains_only_allowed_characters(const char *string)
{
    regex_t regex;

    if (string == NULL) {
        return false;
    }

    if (regcomp(&regex, "^[A-Za-z0-9]+$", REG_EXTENDED | REG_NOSUB) != 0) {
        return false;
    }

    const int result = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (contains_only_allowed_characters(argv[1])) {
        puts("Valid");
        return EXIT_SUCCESS;
    }

    puts("Invalid");
    return EXIT_FAILURE;
}