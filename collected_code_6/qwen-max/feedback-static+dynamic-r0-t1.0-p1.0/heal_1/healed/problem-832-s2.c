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

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        return -1;
    }

    char *str = (char *)input;
    while (regexec(&regex, str, 1, matches, 0) == 0) {
        size_t match_len = matches[0].rm_eo - matches[0].rm_so;
        char *match = malloc(match_len + 1);
        if (match == NULL) {
            regfree(&regex);
            return -1;
        }
        memcpy(match, &str[matches[0].rm_so], match_len);
        match[match_len] = '\0';
        
        long current = atol(match);
        free(match);
        if (current > max && current <= INT_MAX) {
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