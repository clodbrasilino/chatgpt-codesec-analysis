#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int starts_with_regex(const char *string, const char *pattern, int *matches)
{
    regex_t regex;
    regmatch_t match;
    size_t pattern_length;
    char *anchored_pattern;
    int result;

    if (string == NULL || pattern == NULL || matches == NULL) {
        return -1;
    }

    *matches = 0;
    pattern_length = strlen(pattern);

    if (pattern_length > SIZE_MAX - 2) {
        return -1;
    }

    anchored_pattern = malloc(pattern_length + 2);
    if (anchored_pattern == NULL) {
        return -1;
    }

    anchored_pattern[0] = '^';
    snprintf(anchored_pattern + 1, pattern_length + 1, "%s", pattern);

    result = regcomp(&regex, anchored_pattern, REG_EXTENDED);
    free(anchored_pattern);

    if (result != 0) {
        return -1;
    }

    result = regexec(&regex, string, 1, &match, 0);
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

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <string> <regex>\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    if (starts_with_regex(argv[1], argv[2], &matches) != 0) {
        fputs("Unable to evaluate the regular expression\n", stderr);
        return EXIT_FAILURE;
    }

    puts(matches ? "true" : "false");
    return EXIT_SUCCESS;
}