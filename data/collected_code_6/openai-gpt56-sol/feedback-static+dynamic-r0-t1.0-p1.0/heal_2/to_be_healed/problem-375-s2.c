#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int round_to_nearest_multiple(long long number, long long multiple,
                                     long long *result)
{
    long long lower;
    long long remainder;
    unsigned long long distance_to_lower;
    unsigned long long distance_to_upper;
    unsigned long long step;

    if (result == NULL || multiple <= 0) {
        return -1;
    }

    remainder = number % multiple;
    lower = number - remainder;

    if (remainder < 0) {
        if (lower < LLONG_MIN + multiple) {
            return -1;
        }

        lower -= multiple;
        remainder += multiple;
    }

    distance_to_lower = (unsigned long long)remainder;
    step = (unsigned long long)multiple;
    distance_to_upper = step - distance_to_lower;

    if (distance_to_lower < distance_to_upper) {
        *result = lower;
        return 0;
    }

    if (lower > LLONG_MAX - multiple) {
        return -1;
    }

    *result = lower + multiple;
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
    end = NULL;
    parsed = strtoll(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return -1;
    }

    *value = parsed;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    long long number;
    long long multiple;
    long long result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <positive-multiple>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_long_long(argv[1], &number) != 0 ||
        parse_long_long(argv[2], &multiple) != 0 ||
        multiple <= 0) {
        fprintf(stderr, "Invalid arguments\n");
        return EXIT_FAILURE;
    }

    if (round_to_nearest_multiple(number, multiple, &result) != 0) {
        fprintf(stderr, "Result is outside the supported range\n");
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}