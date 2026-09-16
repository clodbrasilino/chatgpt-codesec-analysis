#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int arithmetic_term(long long first, long long difference,
                           unsigned long long position, long long *result)
{
    if (result == NULL || position == 0U || position - 1U > (unsigned long long)LLONG_MAX) {
        return 0;
    }

    long long offset = (long long)(position - 1U);

    if ((difference > 0 && offset > (LLONG_MAX - first) / difference) ||
        (difference < 0 && offset > (first - LLONG_MIN) / -difference)) {
        return 0;
    }

    *result = first + offset * difference;
    return 1;
}

static int parse_long_long(const char *text, long long *value)
{
    char *end = NULL;

    errno = 0;
    long long parsed = strtoll(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int parse_position(const char *text, unsigned long long *value)
{
    char *end = NULL;

    if (text[0] == '-') {
        return 0;
    }

    errno = 0;
    unsigned long long parsed = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || parsed == 0U) {
        return 0;
    }

    *value = parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    long long first;
    long long difference;
    long long term;
    unsigned long long position;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first-term> <common-difference> <position>\n", argv[0]);
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