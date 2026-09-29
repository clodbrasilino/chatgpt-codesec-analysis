#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <limits.h>
#include <string.h>

#define MAX_NUM_BUF 64

long extract_max_value(const char *str) {
    regex_t regex;
    regmatch_t matches[1];
    int status;
    long max_val = LONG_MIN;
    char *end_ptr;

    if (str == NULL) {
        return LONG_MIN;
    }

    status = regcomp(&regex, "[0-9]+", REG_EXTENDED);
    if (status != 0) {
        return LONG_MIN;
    }

    const char *cursor = str;

    while (1) {
        status = regexec(&regex, cursor, 1, matches, 0);
        if (status == REG_NOMATCH) {
            break;
        }
        if (status != 0) {
            regfree(&regex);
            return LONG_MIN;
        }

        if (matches[0].rm_so == -1) {
            break;
        }

        int len = matches[0].rm_eo - matches[0].rm_so;
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char num_buf[MAX_NUM_BUF];

        if (len >= MAX_NUM_BUF) {
            len = MAX_NUM_BUF - 1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(num_buf, cursor + matches[0].rm_so, len);
        num_buf[len] = '\0';

        long current_val = strtol(num_buf, &end_ptr, 10);
        if (end_ptr == num_buf) {
            regfree(&regex);
            return LONG_MIN;
        }

        if (current_val > max_val) {
            max_val = current_val;
        }

        cursor += matches[0].rm_eo;
    }

    regfree(&regex);

    return max_val;
}

int main(int argc, char const * const argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    long result = extract_max_value(argv[1]);

    if (result == LONG_MIN) {
        printf("No numbers found or error occurred.\n");
    } else {
        printf("%ld\n", result);
    }

    return EXIT_SUCCESS;
}