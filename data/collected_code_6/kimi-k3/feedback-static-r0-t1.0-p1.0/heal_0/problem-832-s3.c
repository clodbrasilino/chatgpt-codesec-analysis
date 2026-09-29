#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <limits.h>
#include <errno.h>

int extract_max_numeric(const char *str, long *max_value) {
    regex_t regex;
    regmatch_t match[1];
    const char *pattern = "[0-9]+";
    int ret;
    long max = LONG_MIN;
    int found = 0;
    const char *cursor = str;

    if (str == NULL || max_value == NULL) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    while (1) {
        ret = regexec(&regex, cursor, 1, match, 0);
        if (ret == REG_NOMATCH) {
            break;
        } else if (ret != 0) {
            regfree(&regex);
            return -1;
        }

        if (match[0].rm_so == -1) {
            break;
        }

        char *num_str = strndup(cursor + match[0].rm_so, match[0].rm_eo - match[0].rm_so);
        if (num_str == NULL) {
            regfree(&regex);
            return -1;
        }

        errno = 0;
        char *endptr;
        long num = strtol(num_str, &endptr, 10);
        
        if (errno == 0 && endptr != num_str && *endptr == '\0') {
            if (!found || num > max) {
                max = num;
                found = 1;
            }
        }

        free(num_str);
        cursor += match[0].rm_eo;
    }

    regfree(&regex);

    if (!found) {
        return -1;
    }

    *max_value = max;
    return 0;
}

int main(void) {
    const char *test_strings[] = {
        "The numbers are 42, 17, and 99",
        "No numbers here",
        "100 200 50 300 25",
        "Single 7 number",
        "Negative -50 and positive 150"
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        long max_value;
        if (extract_max_numeric(test_strings[i], &max_value) == 0) {
            printf("String: \"%s\"\n", test_strings[i]);
            printf("Maximum value: %ld\n\n", max_value);
        } else {
            printf("String: \"%s\"\n", test_strings[i]);
            printf("No numeric values found.\n\n");
        }
    }

    return 0;
}