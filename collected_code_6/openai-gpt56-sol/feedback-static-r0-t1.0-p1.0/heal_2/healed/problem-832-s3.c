#include <errno.h>
#include <limits.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool extract_max_numeric_value(const char *input, long long *maximum)
{
    static const char pattern[] = "[+-]?[0-9]+";
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    long long max_value = 0;
    bool found = false;
    int status;

    if (input == NULL || maximum == NULL) {
        return false;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return false;
    }

    cursor = input;

    for (;;) {
        const char *start;
        char *end = NULL;
        long long value;

        status = regexec(&regex, cursor, 1, &match, 0);
        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return false;
        }

        start = cursor + match.rm_so;

        errno = 0;
        value = strtoll(start, &end, 10);

        if (end == start) {
            regfree(&regex);
            return false;
        }

        if (errno == ERANGE) {
            value = (*start == '-') ? LLONG_MIN : LLONG_MAX;
        } else if (errno != 0) {
            regfree(&regex);
            return false;
        }

        if (!found || value > max_value) {
            max_value = value;
            found = true;
        }

        cursor += match.rm_eo;
    }

    regfree(&regex);

    if (found) {
        *maximum = max_value;
    }

    return found;
}

int main(int argc, const char *const argv[])
{
    long long maximum;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"text\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!extract_max_numeric_value(argv[1], &maximum)) {
        fprintf(stderr, "No numeric value found or regex processing failed.\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", maximum);
    return EXIT_SUCCESS;
}