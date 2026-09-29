#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int starts_with_regex(const char *string, const char *pattern, int *matches)
{
    regex_t regex;
    size_t pattern_length;
    size_t anchored_length;
    char *anchored_pattern;
    int result;

    if (string == NULL || pattern == NULL || matches == NULL) {
        return -1;
    }

    *matches = 0;

    pattern_length = strnlen(pattern, SIZE_MAX);
    if (pattern_length == SIZE_MAX || pattern_length > SIZE_MAX - 2) {
        return -1;
    }

    anchored_length = pattern_length + 2;
    anchored_pattern = malloc(anchored_length);
    if (anchored_pattern == NULL) {
        return -1;
    }

    anchored_pattern[0] = '^';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(anchored_pattern + 1, pattern, pattern_length);
    anchored_pattern[pattern_length + 1] = '\0';

    result = regcomp(&regex, anchored_pattern, REG_EXTENDED | REG_NOSUB);
    free(anchored_pattern);

    if (result != 0) {
        return -1;
    }

    result = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (result == 0) {
        *matches = 1;
        return 0;
    }

    return result == REG_NOMATCH ? 0 : -1;
}

int main(int argc, char *argv[])
{
    int matches;
    /* Possible weaknesses found:
     *  The scope of the variable 'program' can be reduced. [variableScope]
     */
    const char *program;

    if (argc != 3 || argv == NULL) {
        program = argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program";
        fprintf(stderr, "Usage: %s <string> <regex>\n", program);
        return EXIT_FAILURE;
    }

    if (starts_with_regex(argv[1], argv[2], &matches) != 0) {
        fputs("Unable to evaluate the regular expression\n", stderr);
        return EXIT_FAILURE;
    }

    puts(matches ? "true" : "false");
    return EXIT_SUCCESS;
}