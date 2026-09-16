#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool contains_only_allowed_characters(const char *string)
{
    regex_t regex;
    int result;

    if (string == NULL) {
        return false;
    }

    result = regcomp(&regex, "^[A-Za-z0-9]+$", REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return false;
    }

    result = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int main(int argc, char *argv[])
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