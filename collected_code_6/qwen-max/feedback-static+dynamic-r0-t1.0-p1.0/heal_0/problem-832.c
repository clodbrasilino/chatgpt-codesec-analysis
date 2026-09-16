#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int extract_max_number(const char *input) {
    regex_t regex;
    regmatch_t match[1];
    int max_value = INT_MIN;

    if (regcomp(&regex, "-?\\d+", REG_EXTENDED)) {
        return max_value;
    }

    const size_t input_len = strlen(input);
    for (size_t i = 0; i < input_len; ++i) {
        if (regexec(&regex, input + i, 1, match, 0) == 0) {
            char *endptr;
            long value = strtol(input + i + match[0].rm_so, &endptr, 10);
            if (value > max_value) {
                max_value = value;
            }
            i += match[0].rm_eo - 1;
        }
    }

    regfree(&regex);
    return max_value;
}

int main() {
    const char *input = "The values are 34, 567, and -89. But the maximum is 12345.";
    int max_value = extract_max_number(input);
    printf("Maximum value: %d\n", max_value);
    return 0;
}