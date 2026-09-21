#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>

int find_max_value(const char *input) {
    regex_t regex;
    regmatch_t matches[1];
    int max = INT_MIN;
    const char *pattern = R"(\d+)";

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE)) {
        return -1;
    }

    const char *str = input;
    while (regexec(&regex, str, 1, matches, 0) == 0) {
        size_t match_len = matches[0].rm_eo - matches[0].rm_so;
        char *match = malloc(match_len + 1);
        if (match == NULL) {
            regfree(&regex);
            return -1;
        }
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(match, &str[matches[0].rm_so], match_len);
        match[match_len] = '\0';

        char *endptr;
        long current = strtol(match, &endptr, 10);
        if (*endptr != '\0' || errno == ERANGE || current > INT_MAX || (current < 0 && endptr - match > 1)) {
            free(match);
            regfree(&regex);
            return -1;
        }
        free(match);
        if (current > max) {
            max = (int)current;
        }
        str += matches[0].rm_eo;
    }

    regfree(&regex);
    return max == INT_MIN ? -1 : max;
}

int main() {
    const char *test_str = "The maximum value in this string is 12345, but it also contains 100, 200, and 999.";
    int result = find_max_value(test_str);
    printf("Maximum value: %d\n", result);
    return 0;
}