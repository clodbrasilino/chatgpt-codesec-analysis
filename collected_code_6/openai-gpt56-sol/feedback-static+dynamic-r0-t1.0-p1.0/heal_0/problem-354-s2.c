#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int arithmetic_progression_term(long long first,
                                       long long difference,
                                       unsigned long long term_number,
                                       long long *result)
{
    if (result == NULL || term_number == 0 ||
        term_number - 1 > (unsigned long long)LLONG_MAX) {
        return -1;
    }

    long long multiplier = (long long)(term_number - 1);

    if (difference > 0 && multiplier > (LLONG_MAX - first) / difference) {
        return -1;
    }

    if (difference < 0 && multiplier > (first - LLONG_MIN) / -difference) {
        return -1;
    }

    *result = first + difference * multiplier;
    return 0;
}

static int parse_long_long(const char *text, long long *value)
{
    char *end = NULL;

    if (text == NULL || value == NULL || *text == '\0') {
        return -1;
    }

    errno = 0;
    long long parsed = strtoll(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return -1;
    }

    *value = parsed;
    return 0;
}

static int parse_unsigned_long_long(const char *text,
                                    unsigned long long *value)
{
    char *end = NULL;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    unsigned long long parsed = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || parsed == 0) {
        return -1;
    }

    *value = parsed;
    return 0;
}

int main(int argc, char *argv[])
{
    long long first = 0;
    long long difference = 0;
    long long result = 0;
    unsigned long long term_number = 0;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first-term> <difference> <term-number>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_long_long(argv[1], &first) != 0 ||
        parse_long_long(argv[2], &difference) != 0 ||
        parse_unsigned_long_long(argv[3], &term_number) != 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (arithmetic_progression_term(first, difference, term_number,
                                    &result) != 0) {
        fprintf(stderr, "Result is outside the supported range\n");
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}