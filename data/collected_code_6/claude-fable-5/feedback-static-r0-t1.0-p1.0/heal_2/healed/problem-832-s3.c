#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <limits.h>

int extract_max_number(const char *input, long *result)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    char buffer[64];
    long max_value = LONG_MIN;
    int found = 0;
    int rc;

    if (input == NULL || result == NULL) {
        return -1;
    }

    rc = regcomp(&regex, "-?[0-9]+", REG_EXTENDED);
    if (rc != 0) {
        return -1;
    }

    cursor = input;
    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t len;
        long value;
        char *endptr;

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            regfree(&regex);
            return -1;
        }

        len = (size_t)(match.rm_eo - match.rm_so);
        if (len == 0 || len > sizeof(buffer) - 1) {
            regfree(&regex);
            return -1;
        }

        memcpy(buffer, cursor + match.rm_so, len);
        buffer[len] = '\0';

        errno = 0;
        value = strtol(buffer, &endptr, 10);
        if (errno == ERANGE || endptr == buffer || *endptr != '\0') {
            regfree(&regex);
            return -1;
        }

        if (!found || value > max_value) {
            max_value = value;
            found = 1;
        }

        cursor += match.rm_eo;
        if (match.rm_eo == match.rm_so) {
            if (*cursor == '\0') {
                break;
            }
            cursor++;
        }
    }

    regfree(&regex);

    if (!found) {
        return -1;
    }

    *result = max_value;
    return 0;
}

int main(void)
{
    const char *test = "abc 42 def -17 ghi 1000 jkl 999";
    long max_value;

    if (extract_max_number(test, &max_value) != 0) {
        fprintf(stderr, "No numeric value found or error occurred\n");
        return EXIT_FAILURE;
    }

    printf("Maximum numeric value: %ld\n", max_value);
    return EXIT_SUCCESS;
}