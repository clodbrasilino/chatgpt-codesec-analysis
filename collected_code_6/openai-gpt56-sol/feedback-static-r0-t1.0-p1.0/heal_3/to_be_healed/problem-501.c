#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned long long magnitude(long long value)
{
    if (value >= 0) {
        return (unsigned long long)value;
    }

    return (unsigned long long)(-(value + 1)) + 1ULL;
}

static unsigned long long greatest_common_divisor(long long first,
                                                  long long second)
{
    unsigned long long a = magnitude(first);
    unsigned long long b = magnitude(second);

    while (b != 0ULL) {
        unsigned long long remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int parse_long_long(const char *text, long long *value)
{
    char *end;
    long long parsed;

    if (text == NULL || value == NULL || *text == '\0') {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    long long first;
    long long second;
    unsigned long long divisor;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <first-number> <second-number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_long_long(argv[1], &first) ||
        !parse_long_long(argv[2], &second)) {
        fputs("Error: both arguments must be valid integers.\n", stderr);
        return EXIT_FAILURE;
    }

    if (first == 0 && second == 0) {
        fputs("Error: the greatest common divisor of 0 and 0 is undefined.\n",
              stderr);
        return EXIT_FAILURE;
    }

    divisor = greatest_common_divisor(first, second);

    if (printf("%llu\n", divisor) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}