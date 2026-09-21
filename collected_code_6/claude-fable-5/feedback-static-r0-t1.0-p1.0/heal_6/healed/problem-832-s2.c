#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <float.h>
#include <math.h>

#define NUMBER_BUFFER_SIZE 64

static int parse_number(const char *start, size_t len, double *value)
{
    char buffer[NUMBER_BUFFER_SIZE];
    char *endptr = NULL;
    double parsed;

    if (start == NULL || value == NULL) {
        return -1;
    }

    if (len == 0 || len >= sizeof(buffer)) {
        return -1;
    }

    memcpy(buffer, start, len);
    buffer[len] = '\0';

    errno = 0;
    parsed = strtod(buffer, &endptr);
    if (errno != 0 || endptr == buffer || *endptr != '\0' || !isfinite(parsed)) {
        return -1;
    }

    *value = parsed;
    return 0;
}

static int extract_max_number(const char *input, double *result)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    double max_value;
    int found;
    int ret;

    if (input == NULL || result == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "-?[0-9]+(\\.[0-9]+)?", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    cursor = input;
    found = 0;
    max_value = -DBL_MAX;

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (match.rm_so >= 0 && match.rm_eo > match.rm_so) {
            size_t len = (size_t)(match.rm_eo - match.rm_so);
            double value = 0.0;

            if (parse_number(cursor + match.rm_so, len, &value) == 0) {
                if (!found || value > max_value) {
                    max_value = value;
                    found = 1;
                }
            }
        }

        if (match.rm_eo <= 0) {
            break;
        }
        cursor += match.rm_eo;
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
    const char *test = "Values: 42, -17, 3.14, 1000.5, and 999";
    double max_value = 0.0;

    if (extract_max_number(test, &max_value) != 0) {
        if (fprintf(stderr, "No numeric value found\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Maximum value: %g\n", max_value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}