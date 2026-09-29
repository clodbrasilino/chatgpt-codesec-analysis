#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <limits.h>

long extract_max_value(const char *str) {
    regex_t regex;
    regmatch_t matches[1];
    int status;
    long max_val = LONG_MIN;
    long current_val;
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

        char num_buf[256];
        int len = matches[0].rm_eo - matches[0].rm_so;

        if (len >= (int)sizeof(num_buf)) {
            regfree(&regex);
            return LONG_MIN;
        }

        for (int i = 0; i < len; ++i) {
            num_buf[i] = cursor[matches[0].rm_so + i];
        }
        num_buf[len] = '\0';

        current_val = strtol(num_buf, &end_ptr, 10);
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

int main(int argc, char *argv[]) {
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