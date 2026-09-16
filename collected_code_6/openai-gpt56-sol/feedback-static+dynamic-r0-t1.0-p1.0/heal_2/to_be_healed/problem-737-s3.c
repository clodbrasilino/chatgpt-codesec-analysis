#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool starts_with_vowel(const char *string, int *error_code)
{
    regex_t regex;
    int result;

    if (string == NULL || error_code == NULL) {
        return false;
    }

    *error_code = regcomp(&regex, "^[AEIOUaeiou]", REG_EXTENDED | REG_NOSUB);
    if (*error_code != 0) {
        return false;
    }

    result = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (result == 0) {
        return true;
    }

    if (result == REG_NOMATCH) {
        return false;
    }

    *error_code = result;
    return false;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    bool matches;
    int error_code = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    matches = starts_with_vowel(argv[1], &error_code);
    if (error_code != 0) {
        fprintf(stderr, "Regular expression error: %d\n", error_code);
        return EXIT_FAILURE;
    }

    printf("%s\n",
           matches ? "Starts with a vowel" : "Does not start with a vowel");

    return EXIT_SUCCESS;
}