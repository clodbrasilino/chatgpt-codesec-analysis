#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

static int starts_with_regex(const char *string, const char *pattern, int *matches)
{
    regex_t regex;
    regmatch_t match;
    char *anchored_pattern;
    size_t pattern_length;
    int result;

    if (string == NULL || pattern == NULL || matches == NULL) {
        return -1;
    }

    pattern_length = strlen(pattern);
    if (pattern_length > SIZE_MAX - 2) {
        return -1;
    }

    anchored_pattern = malloc(pattern_length + 2);
    if (anchored_pattern == NULL) {
        return -1;
    }

    anchored_pattern[0] = '^';
    memcpy(anchored_pattern + 1, pattern, pattern_length + 1);

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

    if (result == REG_NOMATCH) {
        *matches = 0;
        return 0;
    }

    return -1;
}

int main(int argc, char *argv[])
{
    int matches;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <regex>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (starts_with_regex(argv[1], argv[2], &matches) != 0) {
        fprintf(stderr, "Unable to evaluate the regular expression\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", matches ? "true" : "false");
    return EXIT_SUCCESS;
}