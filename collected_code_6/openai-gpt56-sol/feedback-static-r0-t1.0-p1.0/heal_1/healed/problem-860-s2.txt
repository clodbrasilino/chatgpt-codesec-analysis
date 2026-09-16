#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool ends_with_alphanumeric(const char *string)
{
    regex_t regex;

    if (string == NULL) {
        return false;
    }

    if (regcomp(&regex, "[[:alnum:]]+$", REG_EXTENDED | REG_NOSUB) != 0) {
        return false;
    }

    const int result = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (ends_with_alphanumeric(argv[1])) {
        puts("The string ends with alphanumeric characters.");
    } else {
        puts("The string does not end with alphanumeric characters.");
    }

    return EXIT_SUCCESS;
}