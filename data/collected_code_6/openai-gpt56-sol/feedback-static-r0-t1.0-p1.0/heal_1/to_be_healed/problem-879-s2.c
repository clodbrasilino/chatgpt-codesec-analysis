#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int matches_pattern(const char *text, bool *matches)
{
    regex_t regex;
    int result;

    if (text == NULL || matches == NULL) {
        return REG_BADPAT;
    }

    *matches = false;

    result = regcomp(&regex, "^a.*b$", REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return result;
    }

    result = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);

    if (result == 0) {
        *matches = true;
        return 0;
    }

    if (result == REG_NOMATCH) {
        return 0;
    }

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    bool matches;
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = matches_pattern(argv[1], &matches);
    if (result != 0) {
        fprintf(stderr, "Regex matching failed with error code %d\n", result);
        return EXIT_FAILURE;
    }

    printf("%s\n", matches ? "Match" : "No match");
    return EXIT_SUCCESS;
}