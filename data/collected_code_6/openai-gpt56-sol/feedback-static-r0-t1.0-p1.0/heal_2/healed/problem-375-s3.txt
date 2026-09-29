#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int round_to_nearest_multiple(long long number, long long multiple,
                                     long long *result)
{
    long long quotient;
    long long remainder;
    __int128 lower;
    __int128 upper;
    __int128 distance_to_lower;
    __int128 distance_to_upper;
    __int128 rounded;

    if (result == NULL || multiple <= 0) {
        return 0;
    }

    quotient = number / multiple;
    remainder = number % multiple;
    lower = (__int128)quotient * multiple;

    if (remainder < 0) {
        lower -= multiple;
    }

    upper = lower + multiple;
    distance_to_lower = (__int128)number - lower;
    distance_to_upper = upper - (__int128)number;

    if (distance_to_lower < distance_to_upper) {
        rounded = lower;
    } else if (distance_to_upper < distance_to_lower) {
        rounded = upper;
    } else {
        rounded = number >= 0 ? upper : lower;
    }

    if (rounded < (__int128)LLONG_MIN || rounded > (__int128)LLONG_MAX) {
        return 0;
    }

    *result = (long long)rounded;
    return 1;
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

int main(int argc, char *argv[])
{
    long long number;
    long long multiple;
    long long result;
    const char *program_name = argc > 0 && argv[0] != NULL
                                   ? argv[0]
                                   : "round";

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <positive-multiple>\n",
                program_name);
        return EXIT_FAILURE;
    }

    if (!parse_long_long(argv[1], &number) ||
        !parse_long_long(argv[2], &multiple) ||
        multiple <= 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!round_to_nearest_multiple(number, multiple, &result)) {
        fputs("Rounded result is outside the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}