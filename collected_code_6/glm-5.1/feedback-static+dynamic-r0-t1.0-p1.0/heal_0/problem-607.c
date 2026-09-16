#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int search_string_regex(const char *pattern, const char *str, regmatch_t *match) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, str, 1, match, 0);
    regfree(&regex);

    if (ret != 0) {
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pattern> <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *pattern = argv[1];
    const char *str = argv[2];
    regmatch_t match;

    if (search_string_regex(pattern, str, &match) == 0) {
        printf("Pattern found at position %lld\n", (long long)match.rm_so);
        return EXIT_SUCCESS;
    } else {
        printf("Pattern not found\n");
        return EXIT_FAILURE;
    }
}