#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <limits.h>
#include <stdlib.h>

int find_max_value(const char *input) {
    regex_t regex;
    regmatch_t matches[1];
    int max = INT_MIN;
    const char *pattern = R"(\d+)";

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE)) return -1;

    const char *str = input;
    while (regexec(&regex, str, 1, matches, 0) == 0) {
        size_t len = matches[0].rm_eo - matches[0].rm_so;
        char match[len + 1];
        strncpy(match, &str[matches[0].rm_so], len);
        match[len] = '\0';

        char *endptr;
        long current = strtol(match, &endptr, 10);
        if (*endptr != '\0' || endptr == match) {
            regfree(&regex);
            return -1;
        }
        if (current > INT_MAX) {
            regfree(&regex);
            return -1;
        }
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