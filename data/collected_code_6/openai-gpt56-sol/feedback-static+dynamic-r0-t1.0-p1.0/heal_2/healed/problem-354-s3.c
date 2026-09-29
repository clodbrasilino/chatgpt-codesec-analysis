#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int arithmetic_term(long long first, long long difference,
                           unsigned long long position, long long *result)
{
    long long offset;

    if (result == NULL || position == 0ULL ||
        position - 1ULL > (unsigned long long)LLONG_MAX) {
        return 0;
    }

    offset = (long long)(position - 1ULL);

    if ((difference > 0 && offset > (LLONG_MAX - first) / difference) ||
        (difference < 0 &&
         (difference == LLONG_MIN ||
          offset > (first - LLONG_MIN) / -difference))) {
        return 0;
    }

    *result = first + offset * difference;
    return 1;
}

static int parse_long_long(const char *text, long long *value)
{
    char *end;
    long long parsed;

    if (text == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtoll(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int parse_position(const char *text, unsigned long long *value)
{
    char *end;
    unsigned long long parsed;

    if (text == NULL || value == NULL || text[0] == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || parsed == 0ULL) {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(int argc, const char *const argv[])
{
    long long first;
    long long difference;
    long long term;
    unsigned long long position;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first-term> <common-difference> <position>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_long_long(argv[1], &first) ||
        !parse_long_long(argv[2], &difference) ||
        !parse_position(argv[3], &position)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!arithmetic_term(first, difference, position, &term)) {
        fputs("Result is outside the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", term) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}