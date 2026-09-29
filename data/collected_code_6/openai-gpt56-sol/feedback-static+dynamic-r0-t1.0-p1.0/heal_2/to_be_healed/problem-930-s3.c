#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

static int matches_pattern(const char *input, int *matched)
{
    regex_t regex;
    int result;

    if (input == NULL || matched == NULL) {
        return -1;
    }

    result = regcomp(&regex, "^ab*$", REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return -1;
    }

    result = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);

    if (result == 0) {
        *matched = 1;
        return 0;
    }

    if (result == REG_NOMATCH) {
        *matched = 0;
        return 0;
    }

    return -1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    int matched;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (matches_pattern(argv[1], &matched) != 0) {
        fprintf(stderr, "Regular expression processing failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", matched ? "Match" : "No match");
    return EXIT_SUCCESS;
}