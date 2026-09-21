#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <limits.h>

int extract_max_numeric(const char *str, long *max_value) {
    regex_t regex;
    regmatch_t match[1];
    const char *p = str;
    int found = 0;
    int ret;

    if (str == NULL || max_value == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "-?[0-9]+", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    *max_value = 0;

    while (regexec(&regex, p, 1, match, 0) == 0) {
        char *endptr;
        size_t len = (size_t)(match[0].rm_eo - match[0].rm_so);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining = strlen(p);
        char *num_str;

        if (len > remaining) {
            regfree(&regex);
            return -1;
        }

        num_str = (char *)malloc(len + 1);
        if (num_str == NULL) {
            regfree(&regex);
            return -1;
        }

        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(num_str, p + match[0].rm_so, len);
        }
        num_str[len] = '\0';

        errno = 0;
        long current_value = strtol(num_str, &endptr, 10);

        if (errno == 0 && endptr != num_str && *endptr == '\0') {
            if (!found || current_value > *max_value) {
                *max_value = current_value;
                found = 1;
            }
        }

        free(num_str);

        if (match[0].rm_eo == match[0].rm_so) {
            p++;
        } else {
            p += match[0].rm_eo;
        }
    }

    regfree(&regex);

    if (!found) {
        return -1;
    }

    return 0;
}

int main(void) {
    const char *test_strings[] = {
        "abc123def456",
        "no numbers here",
        "-100 and 50 and 200",
        "42",
        "1a2b3c4d5e6f7g8h9i10",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        long max_val;
        int result = extract_max_numeric(test_strings[i], &max_val);

        printf("String: \"%s\"\n", test_strings[i]);
        if (result == 0) {
            printf("Maximum numeric value: %ld\n", max_val);
        } else {
            printf("No numeric values found or error occurred\n");
        }
        printf("\n");
    }

    return 0;
}