#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int search_string_regex(const char *haystack, const char *needle, size_t *location) {
    regex_t regex;
    int ret;
    regmatch_t match;

    if (haystack == NULL || needle == NULL || location == NULL) {
        return -1;
    }

    ret = regcomp(&regex, needle, REG_EXTENDED);
    if (ret != 0) {
        return -2;
    }

    ret = regexec(&regex, haystack, 1, &match, 0);
    if (ret == 0) {
        *location = (size_t)match.rm_so;
        regfree(&regex);
        return 1;
    } else if (ret == REG_NOMATCH) {
        regfree(&regex);
        return 0;
    } else {
        regfree(&regex);
        return -3;
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <pattern>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t loc = 0;
    int result = search_string_regex(argv[1], argv[2], &loc);

    if (result == 1) {
        printf("Pattern found at location: %zu\n", loc);
        return EXIT_SUCCESS;
    } else if (result == 0) {
        printf("Pattern not found.\n");
        return EXIT_SUCCESS;
    } else if (result == -2) {
        fprintf(stderr, "Invalid regex pattern.\n");
        return EXIT_FAILURE;
    } else {
        fprintf(stderr, "Regex execution error.\n");
        return EXIT_FAILURE;
    }
}