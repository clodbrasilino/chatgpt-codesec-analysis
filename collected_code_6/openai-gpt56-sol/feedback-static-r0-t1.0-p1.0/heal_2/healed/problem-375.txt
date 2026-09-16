#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int round_to_nearest_multiple(long long value, long long multiple,
                                     long long *result)
{
    long long quotient;
    long long remainder;

    if (result == NULL || multiple <= 0) {
        return -1;
    }

    quotient = value / multiple;
    remainder = value % multiple;

    if (remainder >= 0) {
        if (remainder >= multiple - remainder) {
            if (quotient == LLONG_MAX) {
                return -1;
            }
            ++quotient;
        }
    } else if (-remainder >= multiple + remainder) {
        if (quotient == LLONG_MIN) {
            return -1;
        }
        --quotient;
    }

    if (quotient > LLONG_MAX / multiple ||
        quotient < LLONG_MIN / multiple) {
        return -1;
    }

    *result = quotient * multiple;
    return 0;
}

static int parse_long_long(const char *text, long long *value)
{
    char *end;
    long long parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtoll(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return -1;
    }

    *value = parsed;
    return 0;
}

int main(int argc, char *const argv[])
{
    long long number;
    long long multiple;
    long long rounded;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <positive-multiple>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_long_long(argv[1], &number) != 0 ||
        parse_long_long(argv[2], &multiple) != 0) {
        fputs("Invalid integer input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (round_to_nearest_multiple(number, multiple, &rounded) != 0) {
        fputs("Unable to round: invalid multiple or arithmetic overflow.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", rounded) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}