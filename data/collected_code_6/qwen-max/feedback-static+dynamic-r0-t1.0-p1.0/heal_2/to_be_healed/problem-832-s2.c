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
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(match, &str[matches[0].rm_so], match_len);
        match[match_len] = '\0';
        
        /* Possible weaknesses found:
         * Flawfinder atol: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
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